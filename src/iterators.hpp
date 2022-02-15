//
// Created by ruslan on 11.02.2022.
//

#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include <iterator>
#include "utils.hpp"

namespace ft
{
	//******************************ITERATOR UTILS******************************


//Структуры для идентификации типа итератора
struct input_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

//Базовый шаблон для определения характеристик итераторов
template<class Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type 			value_type;
	typedef typename Iterator::pointer 				pointer;
	typedef typename Iterator::reference 			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

//Специализация iterator_traits по умолчанию для обычного объекта
template<class T>
struct iterator_traits<T*>
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

//Специализация iterator_traits по умолчанию для константного объекта
template<class T>
struct iterator_traits<const T *>
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

/*
//Возвращает тип итератора
template<class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(Iterator I)
{
	return typename iterator_traits<Iterator>::iterator_category();
}
*/

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



//******************************RANDOM ACCESS ITERATOR******************************

template<typename T>
class vector_iterator
{

public:
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef value_type*					pointer;
	typedef value_type&					reference;
	typedef random_access_iterator_tag	iterator_category;

private:
	pointer	_pointer;

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

	pointer
	get_pointer() const { return (this->_pointer); }

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
		return (_pointer <= other.m_ptr);
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

//Перегрузки операторов для сравнения iterator и const_iterator

template<typename T_L, typename T_R>
typename ft::vector_iterator<T_L>::difference_type
operator==(const ft::vector_iterator<T_L> lhs,
		   const ft::vector_iterator<T_R> rhs)
{
	return (lhs.get_pointer() == rhs.get_pointer());
}

template<typename T_L, typename T_R>
typename ft::vector_iterator<T_L>::difference_type
operator!=(const ft::vector_iterator<T_L> lhs,
		   const ft::vector_iterator<T_R> rhs)
{
	return (lhs.get_pointer() != rhs.get_pointer());
}

template<typename T_L, typename T_R>
typename ft::vector_iterator<T_L>::difference_type
operator<=(const ft::vector_iterator<T_L> lhs,
		   const ft::vector_iterator<T_R> rhs)
{
	return (lhs.get_pointer() <= rhs.get_pointer());
}

template<typename T_L, typename T_R>
typename ft::vector_iterator<T_L>::difference_type
operator<(const ft::vector_iterator<T_L> lhs,
		  const ft::vector_iterator<T_R> rhs)
{
	return (lhs.get_pointer() < rhs.get_pointer());
}

template<typename T_L, typename T_R>
typename ft::vector_iterator<T_L>::difference_type
operator>=(const ft::vector_iterator<T_L> lhs,
		   const ft::vector_iterator<T_R> rhs)
{
	return (lhs.get_pointer() >= rhs.get_pointer());
}

template<typename T_L, typename T_R>
typename ft::vector_iterator<T_L>::difference_type
operator>(const ft::vector_iterator<T_L> lhs,
		  const ft::vector_iterator<T_R> rhs)
{
	return (lhs.get_pointer() > rhs.get_pointer());
}

template<class Key, class T, class Compare, typename Node> class Map_const_iterator;
template<class Key, class T, class Compare, typename Node>
class Map_iterator
{
public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef Compare									key_compare;
	typedef ft::pair<const key_type, mapped_type>	value_type;
	typedef ptrdiff_t								difference_type;
	typedef std::bidirectional_iterator_tag			iterator_category;
	typedef value_type*								pointer;
	typedef value_type&								reference;
	typedef Node*									NodePtr;

protected:

	NodePtr	m_node;
	NodePtr	m_endnode;

private:

	Map_iterator(const Map_const_iterator<Key,T,Compare,Node>& ) {}

public:

	Map_iterator(NodePtr node = NULL) : m_node(node), m_endnode(node)
	{
		if (m_endnode != NULL)
		{
			while (m_endnode->parent != NULL)
				m_endnode = m_endnode->parent;
			while (m_endnode->right != NULL)
				m_endnode = m_endnode->right;
		}
	}
	Map_iterator(NodePtr node, NodePtr endnode)
		: m_node(node), m_endnode(endnode) {}
	Map_iterator(const Map_iterator& from)
		: m_node(from.m_node), m_endnode(from.m_endnode) {}
	~Map_iterator() {}

	NodePtr	getNode() const { return m_node; }
	Map_iterator& operator=(const Map_iterator& it)
	{
		if (this != &it)
		{
			m_node = it.m_node;
			m_endnode = it.m_endnode;
		}
		return (*this);
	}

	bool operator==(const Map_iterator& it) const
	{
		return (m_node == it.m_node);
	}
	bool operator!=(const Map_iterator& it) const
	{
		return (m_node != it.m_node);
	}
	reference operator*() const { return (m_node->val); }
	pointer operator->() const { return (&(m_node->val)); }
	Map_iterator& operator++()
	{
		if (m_node == NULL)
		{
			m_node = m_endnode;
			return (*this);
		}
		else if (m_node->right != NULL)
		{
			m_node = m_node->right;
			while (m_node->left != NULL)
				m_node = m_node->left;
		}
		else
		{
			Node* origin = m_node;
			m_node = m_node->parent;
			while (m_node && m_node->right == origin)
			{
				origin = m_node;
				m_node = m_node->parent;
			}
		}
		return (*this);
	}
	Map_iterator operator++(int)
	{
		Map_iterator tmp(*this);
		++(*this);
		return (tmp);
	}
	Map_iterator& operator--()
	{
		if (m_node == NULL)
		{
			m_node = m_endnode;
			return (*this);
		}
		else if (m_node->left != NULL)
		{
			m_node = m_node->left;
			while (m_node->right != NULL)
				m_node = m_node->right;
		}
		else
		{
			Node* origin = m_node;
			m_node = m_node->parent;
			while (m_node && m_node->left == origin)
			{
				origin = m_node;
				m_node = m_node->parent;
			}
		}
		return (*this);
	}
	Map_iterator operator--(int)
	{
		Map_iterator tmp(*this);
		--(*this);
		return (tmp);
	}
};

template<class Key, class T, class Compare, typename Node>
class Map_const_iterator : public Map_iterator<Key,T,Compare,Node>
{
public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef Compare									key_compare;
	typedef ft::pair<const key_type, mapped_type>	value_type;
	typedef value_type const &						const_reference;
	typedef value_type const *						const_pointer;
	typedef Node*									NodePtr;

	Map_const_iterator(NodePtr node = NULL)
	{
		this->m_node = node;
		this->m_endnode = node;
		if (this->m_endnode != NULL)
		{
			while (this->m_endnode->parent != NULL)
				this->m_endnode = this->m_endnode->parent;
			while (this->m_endnode->right != NULL)
				this->m_endnode = this->m_endnode->right;
		}
	}
	Map_const_iterator(NodePtr node, NodePtr endnode)
	{
		this->m_node = node;
		this->m_endnode = endnode;
	}
	Map_const_iterator(const Map_iterator<Key,T,Compare,Node>& from)
	{
		this->m_node = from.getNode();
	}

	Map_const_iterator& operator=(const Map_const_iterator& it)
	{
		if (this != &it)
			this->m_node = it.m_node;
		return (*this);
	}
	const_reference operator*() const { return (this->m_node->val); }
	const_pointer operator->() const { return (&(this->m_node->val)); }
};

template<class Key, class T, class Compare, typename Node> class Map_const_reverse_iterator;

template<class Key, class T, class Compare, typename Node>
class Map_reverse_iterator
{
public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef Compare									key_compare;
	typedef ft::pair<const key_type, mapped_type>	value_type;
	typedef ptrdiff_t								difference_type;
	typedef std::bidirectional_iterator_tag			iterator_category;
	typedef value_type*								pointer;
	typedef value_type&								reference;
	typedef Node*									NodePtr;

protected:

	Map_iterator<Key,T,Compare,Node>		m_base;

private:

	Map_reverse_iterator(const Map_const_reverse_iterator<Key,T,Compare,Node>& ) {}

public:

	Map_reverse_iterator(NodePtr node = NULL)
		: m_base(Map_iterator<Key,T,Compare,Node>(node)) {}
	Map_reverse_iterator(NodePtr node, NodePtr endnode)
		: m_base(Map_iterator<Key,T,Compare,Node>(node, endnode)) {}
	explicit Map_reverse_iterator(Map_iterator<Key,T,Compare,Node> from)
		: m_base(from) {}
	Map_reverse_iterator(const Map_reverse_iterator<Key,T,Compare,Node>& rev_it)
		: m_base(rev_it.m_base) {}

	NodePtr	getNode() const { return (this->m_base.getNode()); }
	Map_iterator<Key,T,Compare,Node> base() const
	{
		return (this->m_base);
	}
	Map_reverse_iterator& operator=(const Map_reverse_iterator& it)
	{
		if (this != &it)
		{
			m_base = it.m_base;
			m_base.operator++();
		}
		return (*this);
	}
	bool operator==(const Map_reverse_iterator& it) const
	{
		return (m_base == it.m_base);
	}
	bool operator!=(const Map_reverse_iterator& it) const
	{
		return (m_base != it.m_base);
	}
	reference operator*() const
	{
		return (*(Map_iterator<Key,T,Compare,Node>(this->m_base)));
	}
	pointer operator->() const
	{
		return (&this->operator*());
	}
	Map_reverse_iterator& operator++()
	{
		this->m_base.operator--();
		return (*this);
	}
	Map_reverse_iterator operator++(int)
	{
		Map_reverse_iterator tmp(*this);
		++(*this);
		return (tmp);
	}
	Map_reverse_iterator& operator--()
	{
		this->m_base.operator++();
		return (*this);
	}
	Map_reverse_iterator operator--(int)
	{
		Map_reverse_iterator tmp(*this);
		--(*this);
		return (tmp);
	}
};

template<class Key, class T, class Compare, typename Node>
class Map_const_reverse_iterator : public Map_reverse_iterator<Key,T,Compare,Node>
{
public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef Compare									key_compare;
	typedef ft::pair<const key_type, mapped_type>	value_type;
	typedef value_type const &						const_reference;
	typedef value_type const *						const_pointer;
	typedef Node*									NodePtr;

	explicit Map_const_reverse_iterator(Map_iterator<Key,T,Compare,Node> from)
	{
		this->m_base = from.getNode();
		this->m_base.operator--();
	}
	Map_const_reverse_iterator(NodePtr node = NULL)
	{
		this->m_base = Map_iterator<Key,T,Compare,Node>(node);
	}
	Map_const_reverse_iterator(NodePtr node, NodePtr endnode)
	{
		this->m_base = Map_iterator<Key,T,Compare,Node>(node, endnode);
	}
	Map_const_reverse_iterator(Map_const_iterator<Key,T,Compare,Node> from)
	{
		this->m_base = from.getNode();
		this->m_base.operator--();
	}
	Map_const_reverse_iterator(const Map_reverse_iterator<Key,T,Compare,Node>& from)
	{
		this->m_base = from.getNode();
	}

	Map_const_reverse_iterator& operator=(const Map_const_reverse_iterator& it)
	{
		if (this != &it)
			this->m_base = it.m_base;
		return (*this);
	}
	bool operator==(const Map_const_reverse_iterator& it) const
	{
		return (this->m_base == it.m_base);
	}
	bool operator!=(const Map_const_reverse_iterator& it) const
	{
		return (this->m_base != it.m_base);
	}
	const_reference operator*() const
	{
		return (*(Map_iterator<Key,T,Compare,Node>(this->m_base)));
	}
	const_pointer operator->() const { return (&this->operator*()); }
};
}

#endif //FT_CONTAINERS_ITERATORS_HPP
