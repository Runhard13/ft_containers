//
// Created by ruslan on 11.02.2022.
//

#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include <iterator>

namespace ft
{

//Базовый класс для итераторов. Не обязательно все тайпдефы должны быть во всех итераторах
template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
class iterator
{
public:
	typedef T           value_type;
	typedef Distance    difference_type;
	typedef Pointer     pointer;
	typedef Reference   reference;
	typedef Category    iterator_category;
};

//Пустые классы для идентификации типа итератора
struct input_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

//Базовый шаблон класса для определения характеристик итераторов
template<class Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

//Специализация iterator_traits для  обычного random_access_iterator в векторе
template<class T>
struct iterator_traits<T *>
{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef random_access_iterator_tag iterator_category;
};

//Специализация iterator_traits для константного random_access_iterator в векоре
template<class T>
struct iterator_traits<const T *>
{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T *pointer;
	typedef const T &reference;
	typedef random_access_iterator_tag iterator_category;
};

//Возвращает тип итератора
template<class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(Iterator I)
{
	return typename iterator_traits<Iterator>::iterator_category();
}

//Distance - разница между последним и первым элементом
template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last)
{
	typename iterator_traits<Iterator>::difference_type dist = 0;
	while (first != last)
	{
		first++;
		dist++;
	}
	return dist;
}

// Специализации для всех видов итераторов. Царский рандом аксесс умеет вычитать, для всех остальных distance
// должна считаться через инкремент
template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, input_iterator_tag)
{
	return ft::distance(first, last);
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, forward_iterator_tag)
{
	return ft::distance(first, last);
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, bidirectional_iterator_tag)
{
	return ft::distance(first, last);
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, random_access_iterator_tag)
{
	return last - first;
}

//Тоже самое, но для итераторов из стандартной библиотеки
template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, std::input_iterator_tag)
{
	return ft::distance(first, last);
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, std::forward_iterator_tag)
{
	return ft::distance(first, last);
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, std::bidirectional_iterator_tag)
{
	return ft::distance(first, last);
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last, std::random_access_iterator_tag)
{
	return last - first;
}

template<typename T>
class vector_iterator
{
private:
	T *_pointer;
public:
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef value_type *pointer;
	typedef value_type &reference;
	typedef random_access_iterator_tag iterator_category;

	vector_iterator() { _pointer = NULL; }
	vector_iterator(T *ptr) : _pointer(ptr) {}
	vector_iterator(const vector_iterator &copy) : _pointer(copy._pointer) {}
	~vector_iterator() {}

	vector_iterator &
	operator=(const vector_iterator &other)
	{
		if (this != &other)
			_pointer = other._pointer;
		return (*this);
	}

	//Эквивалентность
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
	virtual vector_iterator
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
	virtual vector_iterator
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
		return (_pointer <= other.m_ptr);
	}
	bool
	operator>=(const vector_iterator &other) const
	{
		return (_pointer >= other._pointer);
	}
}; //итератор

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

	vector_iterator_reverse(pointer ptr = NULL)
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
	vector_iterator_reverse
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
	vector_iterator_reverse
	operator--(int)
	{
		vector_iterator_reverse tmp(*this);
		--(*this);
		return (tmp);
	}
};

}

#endif //FT_CONTAINERS_ITERATORS_HPP
