//
// Created by ruslan on 13.02.2022.
//

#ifndef FT_CONTAINERS_SRC_CONTAINERS_UTILS_UTILS_HPP
#define FT_CONTAINERS_SRC_CONTAINERS_UTILS_UTILS_HPP

namespace ft
{

template<class Arg1, class Arg2, class Result>
struct binary_function
{
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};

template<class T>
struct less : binary_function<T, T, bool>
{
	bool
	operator()(const T &x, const T &y) const { return (x < y); }
};

// Класс, который создает пару из значений с разными типами
template<class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;

	pair() : first(), second() {}

	// Создает pair-объект из переданного в конструктор pair-объекта
	template<class U, class V>
	pair(const pair<U, V> &pr)
		: first(pr.first), second(pr.second) {}

	pair(const first_type &a, const second_type &b)
		: first(a), second(b) {}

	pair &
	operator=(const pair &pr)
	{
		if (*this == pr)
			return (*this);
		this->first = pr.first;
		this->second = pr.second;
		return (*this);
	}
};

//******************************Сравнение 2 pair-объектор******************************

template<class T1, class T2>
bool
operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template<class T1, class T2>
bool
operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return !(lhs == rhs);
}

template<class T1, class T2>
bool
operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template<class T1, class T2>
bool
operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return !(rhs < lhs);
}

template<class T1, class T2>
bool
operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (rhs < lhs);
}

template<class T1, class T2>
bool
operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return !(lhs < rhs);
}

//Тоже самое, что и ft::pair, но не нужно передавать типы
template<class T1, class T2>
ft::pair<T1, T2>
make_pair(T1 x, T2 y)
{
	return (ft::pair<T1, T2>(x, y));
}

}

#endif //FT_CONTAINERS_SRC_CONTAINERS_UTILS_UTILS_HPP
