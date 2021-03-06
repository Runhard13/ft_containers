#ifndef FT_CONTAINERS_SRC_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_SRC_CONTAINERS_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <cstddef>
#include <limits>
#include "vector_iterator.hpp"

namespace ft {
template<class T, class Alloc = std::allocator<T> >
class vector {
  //******************************MEMBER TYPES******************************

 public:
  typedef T value_type;
  typedef Alloc allocator_type;

  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  typedef vector_iterator<value_type> iterator;
  typedef vector_iterator<const value_type> const_iterator;
  typedef vector_iterator_reverse<value_type> reverse_iterator;
  typedef vector_iterator_reverse<const value_type> const_reverse_iterator;

  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

 private:
  size_type _size;
  size_type _capacity;
  Alloc _alloc;
  pointer _head;

 public:
  //default constructor
  vector() : _size(0), _capacity(0), _head(NULL) {};

  //fill constructor
  vector(size_type n, const_reference val = value_type()) : _size(n), _capacity(n), _head(NULL) {
	_head = _alloc.allocate(_capacity);
	for (size_type i = 0; i < _size; i++)
	  _alloc.construct(&_head[i], val);
  }

  //range constructor
  template<class InputIterator>
  vector(InputIterator first, InputIterator last,
		 typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type * = NULL)
	  : _size(0), _capacity(0) {
	assign(first, last);
  }

  //copy constructor
  vector(vector const &x)
	  : _size(x._size), _capacity(x._capacity), _alloc(x._alloc) {
	_head = _alloc.allocate(_capacity);
	for (size_type i = 0; i < _size; i++)
	  _alloc.construct(&_head[i], x._head[i]);
  }

  //деструктор
  ~vector() {
	this->clear();
	_alloc.deallocate(_head, this->capacity());
  }

  vector &
  operator=(const vector &x) {
	vector copy(x);
	swap(copy);
	return (*this);
  }

  //******************************ITERATORS******************************

  iterator
  begin() {
	return (iterator(this->_head));
  }
  const_iterator
  begin() const {
	return (const_iterator(this->_head));
  }
  reverse_iterator
  rbegin() {
	return (reverse_iterator(this->end()));
  }
  const_reverse_iterator
  rbegin() const {
	return (const_reverse_iterator(this->end()));
  }
  iterator
  end() {
	return (iterator(&(this->_head[this->_size])));
  }
  const_iterator
  end() const {
	return (const_iterator(&(this->_head[this->_size])));
  }
  reverse_iterator
  rend() {
	return (reverse_iterator(this->begin()));
  }
  const_reverse_iterator
  rend() const {
	return (const_reverse_iterator(this->begin()));
  }

  //******************************CAPACITY******************************

  size_type
  size() const { return _size; }

  //Потенциально максимально возможный размер контейнера. Зависит от ограничений системы или
  //реализации. Аллоцирование такого объема памяти не гарантированно, мы просто обещаем попытаться.
  size_type
  max_size() { return _alloc.max_size(); }

  void
  resize(size_type n, value_type val = value_type()) {
	if (n > _capacity)
	  reallocate(n);
	while (n > _size)
	  push_back(val);
	while (n < _size)
	  pop_back();
  }

  size_type
  capacity() const { return _capacity; }

  //Проверка пустой ли контейнер или нет?
  bool
  empty() const { return _size == 0; }

  //Запрос на изменение капасити. Если запрашивается капасити больше, чем есть сейчас, то происходит реаллокация
  //во всех остальных случаях не происходит ничего
  void
  reserve(size_type n) {
	if (n > this->max_size())
	  throw std::length_error("n > max_size");
	if (n > _capacity)
	  reallocate(n);
  }

  //******************************CAPACITY******************************

  reference
  operator[](size_type n) { return _head[n]; } // вызвать эту функцию с n вне границ контейнера - УБ

  const_reference
  operator[](size_type n) const { return _head[n]; }

  //тоже самое, но бросает эксепшн в случае, если n находится вне границ контейнера
  reference
  at(size_type n) {
	if (n >= _size)
	  throw std::out_of_range("out-of-range");
	return (_head[n]);
  }

  const_reference
  at(size_type n) const {
	if (n >= _size)
	  throw std::out_of_range("out-of-range");
	return (_head[n]);
  }

  //******************************MODIFERS******************************

  reference
  front() { return _head[0]; }

  const_reference
  front() const { return _head[0]; }

  reference
  back() { return _head[_size - 1]; }

  const_reference
  back() const { return _head[_size - 1]; }

  //assign range - элементы контейнера создаются из диапазона [first, last]
  template<class InputIterator>
  void
  assign(InputIterator first, InputIterator last,
		 typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type * = NULL) {

	difference_type n = ft::distance(first, last);
	clear();
	reserve(n);
	while (first != last) {
	  push_back(*first);
	  first++;
	}
  }

  //assign fill - создает n элементов со значением val
  void
  assign(size_type n, const value_type &val) {
	this->clear();
	this->reserve(n);
	size_type i = 0;
	while (i++ < n)
	  this->push_back(val);
  }

  void
  push_back(const value_type &val) {
	if (_size >= _capacity)
	  reallocate(capacity_extension(_size + 1));
	_alloc.construct(&_head[_size++], val);
  }

  void
  pop_back() { _alloc.destroy(&_head[--_size]); }

  //single element insert - Вставляем элемент перед элементом на указанной позиции. Реаллокация должна
  // происходить только в том случае, если новый размер контейнера превышает капасити.
  iterator
  insert(iterator position, const value_type &val) {
	difference_type shift = (position - this->begin());
	if (_size + 1 > _capacity)
	  reallocate(capacity_extension(_size + 1));
	this->insert(iterator(this->begin() + shift), 1, val);
	return (iterator(this->begin() + shift));
  }

  // fill insert - тоже самое что и single insert, но вставляем не один, а n элементов
  void
  insert(iterator position, size_type n, const value_type &val) {
	if (n == 0)
	  return;
	if (_size + n > _capacity)
	  reallocate(capacity_extension(_size + n));
	difference_type shift = position - this->begin();
	difference_type tmp = this->end() - this->begin();

	this->resize(this->_size + n);
	iterator end = this->end();
	position = this->begin() + shift;
	iterator tmp_end = this->begin() + tmp;
	while (tmp_end != position) {
	  --end;
	  --tmp_end;
	  *end = *tmp_end;
	}
	while (n--)
	  *position++ = val;
  }

  //range insert
  template<class InputIterator>
  void
  insert(iterator position,
		 typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type first,
		 InputIterator last) {
	difference_type shift = (position - this->begin());
	size_type n = 0;
	InputIterator tmp(first);
	while (tmp != last) {
	  ++tmp;
	  ++n;
	}
	if ((_size + n) > _capacity) {
	  size_type i = _capacity;
	  while ((_size + n) > i)
		i = i * 2;
	  reallocate(i);
	}
	_size += n;
	iterator it(&_head[_size - n]);
	iterator insert_pos(&_head[shift]);
	iterator it_end = this->end();
	while (it >= insert_pos)
	  *--it_end = *--it;
	while (first != last)
	  _alloc.construct(&(*insert_pos++), *first++);
  }

  //single erase
  iterator
  erase(iterator position) { return (erase(position, position + 1)); }

  //range erase
  iterator
  erase(iterator first, iterator last) {
	if (this->empty())
	  return (last);
	size_type n = last - first;
	iterator ret(first);

	while (last != this->end())
	  *(first++) = *(last++);
	while (n--)
	  _alloc.destroy(&_head[--_size]);
	return (ret);
  }

  void
  swap(vector &x) {
	swap(_size, x._size);
	swap(_capacity, x._capacity);
	swap(_alloc, x._alloc);
	swap(_head, x._head);
  }

  void
  clear() {
	for (size_type i = 0; i < this->_size; i++)
	  this->_head[i].value_type::~value_type();
	this->_size = 0;

  }

  //******************************ALLOCATOR******************************
  allocator_type
  get_allocator() const { return _alloc; }

 private:
  size_type
  capacity_extension(size_type new_size) {
	size_type multiplier = 2;

	size_type new_capacity = (_capacity > 0 ? _capacity : 1);
	while (new_capacity < new_size)
	  new_capacity *= multiplier;
	return (new_capacity);
  }

  void
  reallocate(size_type new_capacity) {
	pointer new_vector = _alloc.allocate(new_capacity);
	size_type i = 0;
	while (i++ < _size) {
	  _alloc.construct(&new_vector[i], _head[i]);
	  _alloc.destroy(&_head[i]);
	}
	if (_capacity)
	  _alloc.deallocate(_head, _capacity);
	_head = new_vector;
	_capacity = new_capacity;
  }

  template<class U>
  void
  swap(U &u1, U &u2) {
	U tmp = u2;
	u2 = u1;
	u1 = tmp;
  }

}; // vector

//******************************RELATION OPERATORS******************************

template<typename T>
bool
operator==(ft::vector<T> const &lhs, ft::vector<T> const &rhs) {
  if (lhs.size() != rhs.size())
	return (false);
  for (size_t i = 0; i < lhs.size(); i++)
	if (lhs[i] != rhs[i])
	  return (false);
  return (true);
}

template<typename T>
bool
operator!=(ft::vector<T> const &lhs, ft::vector<T> const &rhs) {
  return (!(lhs == rhs));
}

template<typename T>
bool
operator<(ft::vector<T> const &lhs, ft::vector<T> const &rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<typename T>
bool
operator<=(ft::vector<T> const &lhs, ft::vector<T> const &rhs) {
  return (!(rhs < lhs));
}

template<typename T>
bool
operator>(ft::vector<T> const &lhs, ft::vector<T> const &rhs) {
  return (rhs < lhs);
}

template<typename T>
bool
operator>=(ft::vector<T> const &lhs, ft::vector<T> const &rhs) {
  return (!(lhs < rhs));
}

template<typename T>
void
swap(ft::vector<T> &x, ft::vector<T> &y) {
  x.swap(y);
}

} //  namespace ft

#endif //FT_CONTAINERS_SRC_CONTAINERS_VECTOR_HPP