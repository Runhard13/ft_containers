//
// Created by ruslan on 11.02.2022.
//

#ifndef FT_CONTAINERS_ITERATORS_H
#define FT_CONTAINERS_ITERATORS_H

#include <iterator>

namespace ft
{
	//Пустые классы для идентификации типа итератора
	struct	input_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};


	//Базовый шаблон класса для определения характеристик итераторов
	template <class Iterator>
	struct	iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	//Специализация iterator_traits для  обычного random_access_iterator в векторе
	template <class T>
	struct	iterator_traits<T*> {
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef random_access_iterator_tag				iterator_category;
	};

	//Специализация iterator_traits для константного random_access_iterator в векоре
	template <class T>
	struct	iterator_traits<const T*> {
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef random_access_iterator_tag				iterator_category;
	};

	//Возвращает тип итератора
	template <class Iterator>
	typename iterator_traits<Iterator>::iterator_category	iterator_category(Iterator I) {
		return typename iterator_traits<Iterator>::iterator_category();
	}

	//Distance - разница между последним и первым элементом
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last)
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
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, input_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, forward_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, bidirectional_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, random_access_iterator_tag) {
		return last - first;
	}


	//Тоже самое, но для итераторов из стандартной библиотеки
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::input_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::forward_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::bidirectional_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::random_access_iterator_tag) {
		return last - first;
	}

	template <typename T>
	class vector_iterator
	{
	private:
		T* _pointer;
	public:
		typedef T         value_type;
		typedef ptrdiff_t difference_type;
		typedef value_type*  pointer;
		typedef value_type& reference;
		typedef random_access_iterator_tag  iterator_category;

		vector_iterator() {_pointer = NULL;}
		vector_iterator(T* ptr) : _pointer(ptr) {}
		vector_iterator(const vector_iterator& copy) : _pointer(copy._pointer) {}
		~vector_iterator() {}


		vector_iterator& operator=(const vector_iterator& other)
		{
			if (this != &other)
				_pointer = other._pointer;
			return (*this);
		}

		//Эквивалентность
		bool operator==(const vector_iterator& it) const
		{
			return (_pointer == it._pointer);
		}
		bool operator!=(const vector_iterator& it) const
		{
			return (_pointer != it._pointer);
		}

		//Разыменование
		reference operator*() const { return (*_pointer); }
		pointer operator->() const { return (_pointer); }
		reference operator[](size_t n) { return _pointer[n]; }

		//Инкремент, декремент с префиксом и постфиксом
		vector_iterator& operator++()
		{
			_pointer++;
			return (*this);
		}
		vector_iterator operator++(int)
		{
			vector_iterator tmp(*this);
			++(*this);
			return (tmp);
		}
		vector_iterator& operator--()
		{
			_pointer--;
			return (*this);
		}
		vector_iterator operator--(int)
		{
			vector_iterator tmp(*this);
			--(*this);
			return (tmp);
		}

		// Плюс, минус
		vector_iterator operator+(difference_type n) const
		{
			return (Vector_iterator(_pointer + n));
		}
		vector_iterator operator-(difference_type n) const
		{
			return (Vector_iterator(_pointer - n));
		}
		difference_type operator-(const vector_iterator& other) const
		{
			return (_pointer - other._pointer);
		}
		difference_type operator+(const vector_iterator& other) const
		{
			return (_pointer + other._pointer);
		}
		vector_iterator& operator+=(int n)
		{
			_pointer += n;
			return (*this);
		}
		vector_iterator& operator-=(int n)
		{
			_pointer -= n;
			return (*this);
		}

		//Неравенства
		bool operator<(const vector_iterator& other) const
		{
			return (_pointer < other._pointer);
		}
		bool operator>(const vector_iterator& other) const
		{
			return (_pointer > other._pointer);
		}
		bool operator<=(const vector_iterator& other) const
		{
			return (_pointer <= other.m_ptr);
		}
		bool operator>=(const vector_iterator& other) const
		{
			return (_pointer >= other._pointer);
		}
	};

}

#endif //FT_CONTAINERS_ITERATORS_H
