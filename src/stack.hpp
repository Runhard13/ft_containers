#ifndef FT_CONTAINERS_SRC_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_SRC_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft
{
template<class T, class Container = vector<T> >
class stack
{
  //******************************MEMBER TYPES******************************

public:
  typedef T value_type;
  typedef size_t size_type;
  typedef Container container_type;

protected:
  Container c;

public:
  explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}
  stack(const stack &x) : c(x.c) {}
  ~stack() {}

  stack &
  operator=(const stack &x)
  {
	stack tmp(x);
	swap(c, tmp.c);
	return *this;
  }

  //*****************************MEMBER FUNCTIONS******************************

  bool
  empty() const { return (c.empty()); }

  size_type
  size() const { return (c.size()); }

  //Ссылка на верхний элемент в стэке. Так как стэк работает по принципу "last-in first-out", верхним элементом
  //будет последний
  value_type &
  top() { return (c.back()); }

  const value_type &
  top() const { return (c.back()); }

  void
  push(const value_type &val) { c.push_back(val); }

  void
  pop() { c.pop_back(); }

  friend bool
  operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
  {
	return (lhs.c == rhs.c);
  }

  friend bool
  operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
  {
	return (lhs.c < rhs.c);
  }
};

//***************************** NON-MEMBER FUNCTIONS******************************

template<class T, class Container>
bool
operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
  return (!(lhs == rhs));
}

template<class T, class Container>
bool
operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
  return (!(rhs < lhs));
}

template<class T, class Container>
bool
operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
  return (rhs < lhs);
}

template<class T, class Container>
bool
operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
  return (!(lhs < rhs));
}

}

#endif //FT_CONTAINERS_SRC_CONTAINERS_STACK_HPP