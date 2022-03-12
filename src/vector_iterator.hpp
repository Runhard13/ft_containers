//
// Created by ruslan on 11.02.2022.
//

#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include <iterator>
#include "utils.hpp"

namespace ft
{



//******************************RANDOM ACCESS ITERATOR******************************

template<typename T>
class vector_iterator
{

public:
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef value_type *pointer;
  typedef value_type &reference;
  typedef random_access_iterator_tag iterator_category;

private:
  pointer _pointer;

public:
  vector_iterator() { _pointer = NULL; }
  explicit vector_iterator(T *ptr) : _pointer(ptr) {}
  vector_iterator(const vector_iterator &copy) : _pointer(copy._pointer) {}
  ~vector_iterator() {}

  vector_iterator &
  operator=(const vector_iterator &other)
  {
	if (this != &other)
	  _pointer = other._pointer;
	return (*this);
  }

  bool
  operator==(const vector_iterator &it) const
  {
	return (_pointer == it._pointer);
  }

  bool
  operator!=(const vector_iterator &it) const
  {
	return (_pointer != it._pointer);
  }

  //Разыменование
  reference
  operator*() const { return (*_pointer); }
  pointer
  operator->() const { return (_pointer); }
  reference
  operator[](size_t n) { return _pointer[n]; }

  virtual //Инкремент, декремент с префиксом и постфиксом
  vector_iterator &
  operator++()
  {
	_pointer++;
	return (*this);
  }
  virtual const vector_iterator
  operator++(int)
  {
	vector_iterator tmp(*this);
	++(*this);
	return (tmp);
  }
  virtual vector_iterator &
  operator--()
  {
	_pointer--;
	return (*this);
  }
  virtual const vector_iterator
  operator--(int)
  {
	vector_iterator tmp(*this);
	--(*this);
	return (tmp);
  }

  // Плюс, минус
  vector_iterator
  operator+(difference_type n) const
  {
	return (vector_iterator(_pointer + n));
  }
  vector_iterator
  operator-(difference_type n) const
  {
	return (vector_iterator(_pointer - n));
  }
  difference_type
  operator-(const vector_iterator &other) const
  {
	return (_pointer - other._pointer);
  }
  difference_type
  operator+(const vector_iterator &other) const
  {
	return (_pointer + other._pointer);
  }
  vector_iterator &
  operator+=(int n)
  {
	_pointer += n;
	return (*this);
  }
  vector_iterator &
  operator-=(int n)
  {
	_pointer -= n;
	return (*this);
  }

  //Неравенства
  bool
  operator<(const vector_iterator &other) const
  {
	return (_pointer < other._pointer);
  }
  bool
  operator>(const vector_iterator &other) const
  {
	return (_pointer > other._pointer);
  }
  bool
  operator<=(const vector_iterator &other) const
  {
	return (_pointer <= other._pointer);
  }
  bool
  operator>=(const vector_iterator &other) const
  {
	return (_pointer >= other._pointer);
  }

}; //вектор_итератор

template<class T>
class vector_iterator_reverse
{
public:
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef value_type *pointer;
  typedef value_type &reference;
  typedef random_access_iterator_tag iterator_category;
protected:
  vector_iterator<T> _base;

public:

  explicit vector_iterator_reverse(pointer ptr = NULL)
	  : _base(vector_iterator<T>(ptr)) {}
  explicit vector_iterator_reverse(vector_iterator<T> from)
	  : _base(--from) {}

  vector_iterator<T>
  base() const
  {
	vector_iterator<T> tmp(_base);
	return (++tmp);
  }

  vector_iterator_reverse &
  operator=(const vector_iterator_reverse &it)
  {
	if (this != &it)
	  _base = it._base;
	return (*this);
  }

  bool
  operator==(const vector_iterator_reverse &rhs) const
  {
	return this->_base.operator==(rhs._base);
  }

  bool
  operator!=(const vector_iterator_reverse &rhs) const
  {
	return this->_base.operator!=(rhs._base);
  }

  bool
  operator<(const vector_iterator_reverse &rhs) const
  {
	return this->_base.operator>(rhs._base);
  }

  bool
  operator<=(const vector_iterator_reverse &rhs) const
  {
	return this->_base.operator>=(rhs._base);
  }

  bool
  operator>(const vector_iterator_reverse &rhs) const
  {
	return this->_base.operator<(rhs._base);
  }

  bool
  operator>=(const vector_iterator_reverse &rhs) const
  {
	return this->_base.operator<=(rhs._base);
  }

  reference
  operator[](size_t n) { return this->_base.operator[](n); }
  reference

  operator*() const
  {
	return (*(vector_iterator<T>(this->_base)));
  }

  pointer
  operator->() const
  {
	return (&this->operator*());
  }

  vector_iterator_reverse
  operator+(difference_type n) const
  {
	vector_iterator_reverse tmp(*this);
	tmp._base.operator-=(n);
	return (tmp);
  }
  vector_iterator_reverse
  operator-(difference_type n) const
  {
	vector_iterator_reverse tmp(*this);
	tmp._base.operator+=(n);
	return (tmp);
  }
  difference_type
  operator-(const vector_iterator_reverse &other)
  {
	return (other.base().operator-(this->_base));
  }
  difference_type
  operator+(const vector_iterator_reverse &other)
  {
	return (other.base().operator+(this->_base));
  }
  vector_iterator_reverse &
  operator+=(int n)
  {
	this->_base.operator-=(n);
	return (*this);
  }
  vector_iterator_reverse &
  operator-=(int n)
  {
	this->_base.operator+=(n);
	return (*this);
  }
  vector_iterator_reverse &
  operator++()
  {
	this->_base.operator--();
	return (*this);
  }
  const vector_iterator_reverse
  operator++(int)
  {
	vector_iterator_reverse tmp(*this);
	++(*this);
	return (tmp);
  }
  vector_iterator_reverse &
  operator--()
  {
	this->_base.operator++();
	return (*this);
  }
  const vector_iterator_reverse
  operator--(int)
  {
	vector_iterator_reverse tmp(*this);
	--(*this);
	return (tmp);
  }

}; //вектор итератор реверс

}

#endif //FT_CONTAINERS_ITERATORS_HPP
