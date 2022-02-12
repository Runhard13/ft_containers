#include <memory>
#include <stdexcept>
#include <cstddef>
#include "./utils/iterators.hpp"

namespace ft
{
template<class T, class Alloc = std::allocator<T> >
class vector
{
	//******************************MEMBER TYPES******************************

public:
	typedef T											value_type;
	typedef Alloc 										allocator_type;
	typedef typename allocator_type::reference 			reference;
	typedef typename allocator_type::const_reference 	const_reference;
	typedef typename allocator_type::pointer 			pointer;
	typedef typename allocator_type::const_pointer 		const_pointer;

	typedef vector_iterator<value_type>					iterator;
	typedef vector_iterator<const value_type> 			const_iterator;
	typedef vector_iterator_reverse<value_type>			reverse_iterator;
	typedef vector_iterator_reverse<const value_type>	const_reverse_iterator;

	typedef ptrdiff_t 	difference_type;
	typedef size_t 		size_type;

private:
	size_type 	_size;
	size_type 	_capacity;
	pointer 	_head;
	Alloc 		_alloc;

public:
	//дефолтный конструктор. Создает пустой контейнер без элементов
	explicit vector(const allocator_type &alloc = allocator_type())
		: _head(NULL), _size(0), _alloc(alloc), _capacity(0) {};

	//fill constructor. Создает контейнер из n элементов. Каждый элемент это копия val
	explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _size(n), _capacity(n)
	{
		_head = _alloc.allocate(_capacity);
		size_type i = 0;
		while (i++ < _size)
			_alloc.construct(&_head[i], val);
	}

	//range constructor. Создает [first, last] элементов. Значение
	// каждого элемента равно тому же, что и в [first, last]
	template<class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
		:_alloc(alloc), _capacity(0), _size(0)
	{
		assign(first, last);
	}

	//copy constructor. Создает контейнер с копиями каждого элемента Х
	vector(const vector &x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
	{
		_head = _alloc.allocate(_capacity);
		size_type i = 0;
		while (i++ < _size)
			_alloc.construct(&_head[i], x._head[i]);
	}

	//деструктор
	~vector()
	{
		size_type i = 0;
		while (i++ < _size)
			_alloc.destroy(&_head[i]);
		_alloc.deallocate(_head, _capacity);
	}
	//Оператор присваивания. копирует все элементы из Х в контейнер
	vector &
	operator=(const vector &x)
	{
		vector copy(x);
		swap(copy);
		return (*this);
	}

	//******************************ITERATORS******************************

	iterator
	begin() { return (iterator(_head)); }

	const_iterator
	begin() const { return (iterator(_head)); }

	iterator
	end() { return (iterator(_head + _size)); }

	const_iterator
	end() const { return (iterator(_head + _size)); }

	reverse_iterator
	rbegin() { return (reverse_iterator(_head + _size)); }

	const_reverse_iterator
	rbegin() const { return (reverse_iterator(_head + _size)); }

	reverse_iterator
	rend() { return (reverse_iterator(_head + _size - 1)); }

	const_reverse_iterator
	rend()  const { return (reverse_iterator(_head + _size - 1)); }

	//******************************CAPACITY******************************

	size_type
	size() const { return _size; }

	//Потенциально максимально возможный размер контейнера. Зависит от ограничений системы или
	//реализации. Аллоцирование такого объема памяти не гарантированно, мы просто обещаем попытаться.
	size_type
	max_size() { return _alloc.max_size(); }

	void
	resize(size_type n, value_type val = value_type())
	{
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
	reserve(size_type n)
	{
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
	at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("out-of-range");
		return (_head[n]);
	}

	const_reference
	at(size_type n) const
	{
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
	assign(InputIterator first, InputIterator last)
	{
		// сначала ищем n, затем создаем контейнер с нужным количеством памяти, чтобы при каждом push_back по
		// новой не аллоцировать память и не копировать туда данные
		difference_type n = 0;
		InputIterator count(first);
		while (count != last)
		{
			++count;
			++n;
		}
		clear();
		reserve(n);
		while (first != last)
		{
			push_back(*first);
			first++;
		}
	}

	//assign fill - создает n элементов со значением val
	void
	assign(size_type n, const value_type &val)
	{
		this->clear();
		this->reserve(n);
		size_type i = 0;
		while (i++ < n)
			this->push_back(val);
	}

	void
	push_back(const value_type &val)
	{
		if (_size >= _capacity)
			reallocate(capacity_extension(_size + 1));
		_alloc.construct(&_head[_size++], val);
	}

	void
	pop_back() { _alloc.destroy(&_head[--_size]); }

	//single element insert - Вставляем элемент перед элементом на указанной позиции. Реаллокация должна
	// происходить только в том случае, если новый размер контейнера превышает капасити.
	iterator
	insert(iterator position, const value_type &val)
	{
		if (_size + 1 > _capacity)
			reallocate(capacity_extension(_size + 1));
		difference_type shift = (position - this->begin());
		if (_size + 1 > _capacity)
			reallocate(capacity_extension(_size + 1));
		this->insert(iterator(this->begin() + shift), 1, val);
		return (iterator(this->begin() + shift));
	}

	// fill insert - тоже самое что и single insert, но вставляем не один, а n элементов
	void
	insert(iterator position, size_type n, const value_type &val)
	{
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
		while (tmp_end != position)
		{
			--end;
			--tmp_end;
			*end = *tmp_end;
		}
		while (n--)
			*position++ = val;
	}

	//range insert
	template <class InputIterator>
	void
	insert (iterator position, InputIterator first, InputIterator last)
	{
		difference_type shift = (position - this->begin());
		size_type n = 0;
		InputIterator tmp(first);
		while (tmp != last)
		{
			++tmp;
			++n;
		}
		if ((_size + n) > _capacity)
			reallocate(_size + n);
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
	erase(iterator position) { return (erase(position, position + 1));}

	//range erase. Удаление элементов с середины - неэффективная операция, потому что требует реаллокации всего массива,
	//поэтому сначала удаляемые элементы нужно закинуть в конец, а затем, с конца уже удалить. В этом случае реаллоцирование не потребуется
	iterator
	erase(iterator first, iterator last)
	{
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

	void swap(vector& x)
	{
		swap(_size, x._size);
		swap(_capacity, x._capacity);
		swap(_alloc, x._alloc);
		swap(_head, x._head);
	}

	void
	clear()
	{
		size_type i = 0;
		while (i++ < _size)
			_alloc.destroy(&_head[i]);
		_size = 0;
	}

	//******************************ALLOCATOR******************************
	allocator_type
	get_allocator() const { return _alloc; }

private:
	size_type
	capacity_extension(size_type new_size)
	{
		size_type multiplier = 2;

		size_type new_capacity = (_capacity > 0 ? _capacity : 1);
		while (new_capacity < new_size)
			new_capacity *= multiplier;
		return (new_capacity);
	}

	void
	reallocate(size_type new_capacity)
	{
		pointer new_vector = _alloc.allocate(new_capacity);
		size_type i = 0;
		while (i++ < _size)
		{
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
	swap(U& u1, U& u2)
	{
		U tmp = u2;
		u2 = u1;
		u1 = tmp;
	}

}; // vector

//******************************RELATION OPERATORS******************************

template <class T, class Alloc>
bool
operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	typename ft::vector<T>::const_iterator lhs_begin = lhs.begin();
	typename ft::vector<T>::const_iterator lhs_end = lhs.end();
	typename ft::vector<T>::const_iterator rhs_begin = rhs.begin();
	typename ft::vector<T>::const_iterator rhs_end = rhs.end();

	if (lhs.size() != rhs.size())
		return false;

	while ((lhs_begin != lhs_end) && (rhs_begin != rhs_end))
	{
		if (*lhs_begin != *rhs_begin)
			return (false);
		++lhs_begin;
		++rhs_begin;
	}
	return (true);
}

template <class T, class Alloc>
bool
operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool
operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	typename ft::vector<T>::const_iterator lhs_begin = lhs.begin();
	typename ft::vector<T>::const_iterator lhs_end = lhs.end();
	typename ft::vector<T>::const_iterator rhs_begin = rhs.begin();
	typename ft::vector<T>::const_iterator rhs_end = rhs.end();

	while (lhs_begin != lhs_end)
	{
		if (rhs_begin == lhs_end || *rhs_begin < *lhs_begin)
			return (false);
		else if (*lhs_begin < *rhs_begin)
			return (true);
		++lhs_begin;
		++rhs_begin;
	}
	return (rhs_begin != rhs_end);
}

template <class T, class Alloc>
bool
operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool
operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool
operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template <class T, class Alloc>
void
swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);
}
} // ft