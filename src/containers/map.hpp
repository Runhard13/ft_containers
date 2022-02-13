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

};
}

#endif //FT_CONTAINERS_SRC_CONTAINERS_MAP_HPP
