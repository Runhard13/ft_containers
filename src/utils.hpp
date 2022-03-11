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
  operator()(const T &x, const T &y) const
  { return (x < y); }
};

// Класс, который создает пару из значений с разными типами
template<class T1, class T2>
struct pair
{
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first;
  second_type second;

  pair()
	  : first(), second()
  {}

  // Создает pair-объект из переданного в конструктор pair-объекта
  template<class U, class V>
  pair(const pair<U, V> &pr)
	  : first(pr.first), second(pr.second)
  {}

  pair(const first_type &a, const second_type &b)
	  : first(a), second(b)
  {}

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

template<bool Cond, class T = void>
struct enable_if
{
};
template<class T>
struct enable_if<true, T>
{
  typedef T type;
};

template<bool is_integer, typename T>
struct is_integer_res
{
  typedef T type;
  static const bool value = is_integer;
};

template<typename>
struct is_integer_type : public is_integer_res<false, bool>
{
};

template<>
struct is_integer_type<bool> : public is_integer_res<true, bool>
{
};

template<>
struct is_integer_type<char> : public is_integer_res<true, char>
{
};

template<>
struct is_integer_type<signed char> : public is_integer_res<true, signed char>
{
};

template<>
struct is_integer_type<short int> : public is_integer_res<true, short int>
{
};

template<>
struct is_integer_type<int> : public is_integer_res<true, int>
{
};

template<>
struct is_integer_type<long int> : public is_integer_res<true, long int>
{
};

template<>
struct is_integer_type<long long int> : public is_integer_res<true, long long int>
{
};

template<>
struct is_integer_type<unsigned char> : public is_integer_res<true, unsigned char>
{
};

template<>
struct is_integer_type<unsigned short int> : public is_integer_res<true, unsigned short int>
{
};

template<>
struct is_integer_type<unsigned int> : public is_integer_res<true, unsigned int>
{
};

template<>
struct is_integer_type<unsigned long int> : public is_integer_res<true, unsigned long int>
{
};

template<>
struct is_integer_type<unsigned long long int> : public is_integer_res<true, unsigned long long int>
{
};

template<typename T>
struct is_integer : public is_integer_type<T>
{
};

template<class InputIterator1, class InputIterator2>
bool
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
						InputIterator2 first2, InputIterator2 last2)
{
  while (first1 != last1)
  {
	if (first2 == last2 || *first2 < *first1)
	  return false;
	else if (*first1 < *first2)
	  return true;
	++first1;
	++first2;
  }
  return (first2 != last2);
}
}

#endif //FT_CONTAINERS_SRC_CONTAINERS_UTILS_UTILS_HPP
