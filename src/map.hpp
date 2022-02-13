//
// Created by ruslan on 12.02.2022.
//

#ifndef FT_CONTAINERS_SRC_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_SRC_CONTAINERS_MAP_HPP

#include "utils/utils.hpp"

namespace ft
{
template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	struct Node
		{
			ft::pair<const Key, T>	val;
			Node*					parent;
			Node*					left;
			Node*					right;
			int						height;
		};

	//******************************MEMBER TYPES******************************

public:

	typedef Key												key_type;
	typedef T												mapped_type;
	typedef ft::pair<const key_type, mapped_type>			value_type;
	typedef Compare											key_compare;
	typedef Alloc											allocator_type;
	typedef typename Alloc::template
		rebind<Node>::other									Node_allocator;
	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef Map_iterator<Key, T, Compare, Node>				iterator;
	typedef Map_const_iterator<Key, T, Compare, Node>		const_iterator;
	typedef Map_const_reverse_iterator<Key, T, Compare, Node>	const_reverse_iterator;
	typedef Map_reverse_iterator<Key, T, Compare, Node>		reverse_iterator;
	typedef ptrdiff_t										difference_type;
	typedef size_t											size_type;

	private:

	Node*			_root;
	Node*			_lastinsert;
	size_type		_size;
	key_compare		_comp;
	allocator_type	_alloc;

	//******************************MEMBER FUNCTIONS******************************
	
	public:

	explicit map(const key_compare& comp = key_compare(),
	const allocator_type& alloc = allocator_type())
	: _root(NULL), _lastinsert(NULL), _size(0), _comp(comp), _alloc(alloc) {}


	map(const map& x)
	: _root(NULL), _lastinsert(NULL), _size(0), _comp(key_compare()), _alloc(allocator_type())
	{
		const_iterator ite = x.end();
		for (const_iterator it = x.begin(); it != ite; it++)
		this->insert(*it);
	}

	~map() { clear(); }

	map& operator=(const map& x)
	{
		map tmp(x);
		this->swap(tmp);
		return (*this);
	}

//******************************ITERATORS******************************

	iterator begin() { return (iterator(this->tree_smallest(_root))); }

	const_iterator begin() const { return (const_iterator(this->tree_smallest(_root))); }
	
	iterator end()
	{
		if (this->empty())
		return (iterator());
		return (iterator((this->tree_biggest(_root))->right,
		this->tree_biggest(_root)));
	}
	const_iterator end() const
	{
		if (this->empty())
		return (iterator());
		return (const_iterator((this->tree_biggest(_root))->right,
		this->tree_biggest(_root)));
	}
	
	reverse_iterator rbegin()
	{
		return (reverse_iterator(this->tree_biggest(_root)));
	}

	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(this->tree_biggest(_root)));
	}
	
	reverse_iterator rend()
	{
		if (this->empty())
		return (reverse_iterator(_root));
		return (reverse_iterator((this->tree_smallest(_root))->left,
		this->tree_smallest(_root)));
	}
	const_reverse_iterator rend() const
	{
		if (this->empty())
		return (const_reverse_iterator(_root));
		return (const_reverse_iterator((this->tree_smallest(_root))->left,
		this->tree_smallest(_root)));
	}

	//******************************CAPACITY******************************
	
	bool empty() const { return (_size == 0); }
	
	size_type size() const { return (_size); }
	size_type max_size() const { return (Node_allocator(_alloc).max_size()); }

	//******************************MODIFERS******************************

	pair<iterator,bool> insert(const value_type& val)
	{
		size_type size_before = this->size();
		_root = this->tree_insert(_root, NULL, val);
		Node* newnode = _lastinsert;
		_lastinsert = NULL;
		return (ft::pair<iterator, bool>(iterator(newnode),
				(this->size() > size_before)));
	}

	iterator insert(iterator position, const value_type& val)
	{
		if (this->size() < 3)
			return ((this->insert(val)).first);
		while (position->first > val.first && position != this->begin())
			position--;

	iterator	tmp(position);
		tmp++;
				while (position->first < val.first && tmp != this->end())
				{
					tmp++;
					position++;
				}
				if (position->first == val.first)
					return (position);
				Node* parent = position.getNode()->parent;
				if (!parent)
					_root = this->tree_insert(_root, NULL, val);
				else
				{
					tree_insert(position.getNode()->parent, NULL, val);
					while (_root->parent != NULL)
						_root = _root->parent;
					_root = this->tree_balance(_root);
				}
				Node*	new_node = _lastinsert;
				_lastinsert = NULL;
				return (iterator(new_node));
			}

			template <class InputIterator>
			void insert(typename ft::enable_if<!std::numeric_limits<InputIterator>
				::is_integer, InputIterator>::type first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);
			}

			void erase(iterator position)
			{
				_root = this->tree_delete(_root, position->first);
			}

	
			size_type erase(const key_type& k)
			{
				size_type tmp = this->size();
				_root = this->tree_delete(_root, k);
				return ((this->size() == tmp) ? 0 : 1);
			}


			void erase(iterator first, iterator last)
			{
				map tmp(first, last);
				for (reverse_iterator it = tmp.rbegin(); it != tmp.rend(); ++it)
					this->erase(it->first);
			}


			void swap(map& x)
			{
				swap(_root, x._root);
				swap(_size, x._size);
				swap(_comp, x._comp);
				swap(_alloc, x._alloc);
			}

			void clear()
			{
				_root = this->tree_clear(_root);
			}

//******************************OBSERVERS******************************

key_compare key_comp() const { return (_comp); }

class value_compare
{
	// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
	friend class map;

	public:

	typedef bool		result_type;
	typedef value_type	first_argument_type;
	typedef value_type	second_argument_type;

	bool operator()(const value_type &x, const value_type &y) const
	{
	return comp(x.first, y.first);
	}

	protected:

	key_compare		comp;

	value_compare(Compare c) : comp(c) {}
};

value_compare value_comp() const { return (value_compare(_comp));
			}

//******************************OPERATIONS******************************

iterator find(const key_type& k)
{
	Node* found = this->tree_search(_root, k);
	if (found)
		return (iterator(found));
	return (this->end());
}

			const_iterator find(const key_type& k) const
			{
				Node* found = this->tree_search(_root, k);

				if (found)
					return (const_iterator(found));
				return (this->end());
			}


			size_type count(const key_type& k) const
			{
				Node* found = this->tree_search(_root, k);

				if (found)
					return (1);
				return (0);
			}


			iterator lower_bound(const key_type& k)
			{
				iterator lower = this->begin();
				iterator end = this->end();
				while (lower != end && _comp(lower->first, k))
					lower++;
				return (lower);
			}


			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator lower = this->begin();
				const_iterator end = this->end();
				while (lower != end && _comp(lower->first, k))
					lower++;
				return (lower);
			}


			iterator upper_bound(const key_type& k)
			{
				iterator upper = this->begin();
				iterator end = this->end();
				while (upper != end && !_comp(k, upper->first))
					upper++;
				return (upper);
			}


			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator upper = this->begin();
				const_iterator end = this->end();
				while (upper != end && !_comp(k, upper->first))
					upper++;
				return (upper);
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				pair<const_iterator, const_iterator> range;

				range.first = this->lower_bound(k);
				range.second = this->upper_bound(k);
				return (range);
			}


			pair<iterator,iterator> equal_range(const key_type& k)
			{
				pair<iterator, iterator> range;

				range.first = this->lower_bound(k);
				range.second = this->upper_bound(k);
				return (range);
			}

			//аллокатор

						allocator_type get_allocator() const
			{
				return (_alloc);
			}

};
}

#endif //FT_CONTAINERS_SRC_CONTAINERS_MAP_HPP
