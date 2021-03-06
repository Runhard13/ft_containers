//
// Created by ruslan on 12.02.2022.
//

#ifndef FT_CONTAINERS_SRC_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_SRC_CONTAINERS_MAP_HPP

#include "utils.hpp"
#include "map_iterator.hpp"

namespace ft {
template<class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
  struct Node {
	ft::pair<const Key, T> val;
	Node *parent;
	Node *left;
	Node *right;
	int height;
  };

  //******************************MEMBER TYPES******************************

 public:

  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef typename Alloc::template
  rebind<Node>::other Node_allocator;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  typedef Map_iterator<Key, T, Compare, Node> iterator;
  typedef Map_const_iterator<Key, T, Compare, Node> const_iterator;
  typedef Map_const_reverse_iterator<Key, T, Compare, Node> const_reverse_iterator;
  typedef Map_reverse_iterator<Key, T, Compare, Node> reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

 private:

  Node *_root;
  Node *_last_inserted;
  size_type _size;
  key_compare _comp;
  allocator_type _alloc;

  //******************************MEMBER FUNCTIONS******************************

 public:

  explicit map(const key_compare &comp = key_compare(),
			   const allocator_type &alloc = allocator_type())
	  : _root(NULL), _last_inserted(NULL), _size(0), _comp(comp), _alloc(alloc) {}

  template<class InputIterator>
  map(InputIterator first, InputIterator last,
	  const key_compare &comp = key_compare(),
	  const allocator_type &alloc = allocator_type())
	  : _root(NULL), _last_inserted(NULL), _size(0), _comp(comp), _alloc(alloc) {
	while (first != last)
	  this->insert(*first++);
  }

  map(const map &x)
	  : _root(NULL), _last_inserted(NULL), _size(0), _comp(key_compare()), _alloc(allocator_type()) {
	const_iterator ite = x.end();
	for (const_iterator it = x.begin(); it != ite; it++)
	  this->insert(*it);
  }

  ~map() { clear(); }

  map &
  operator=(const map &x) {
	map tmp(x);
	this->swap(tmp);
	return (*this);
  }

//******************************ITERATORS******************************

  iterator
  begin() { return (iterator(this->tree_smallest(_root))); }

  const_iterator
  begin() const { return (const_iterator(this->tree_smallest(_root))); }

  iterator
  end() {
	if (this->empty())
	  return (iterator());
	return (iterator((this->tree_biggest(_root))->right,
					 this->tree_biggest(_root)));
  }
  const_iterator
  end() const {
	if (this->empty())
	  return (iterator());
	return (const_iterator((this->tree_biggest(_root))->right,
						   this->tree_biggest(_root)));
  }

  reverse_iterator
  rbegin() {
	return (reverse_iterator(this->tree_biggest(_root)));
  }

  const_reverse_iterator
  rbegin() const {
	return (const_reverse_iterator(this->tree_biggest(_root)));
  }

  reverse_iterator
  rend() {
	if (this->empty())
	  return (reverse_iterator(_root));
	return (reverse_iterator((this->tree_smallest(_root))->left,
							 this->tree_smallest(_root)));
  }
  const_reverse_iterator
  rend() const {
	if (this->empty())
	  return (const_reverse_iterator(_root));
	return (const_reverse_iterator((this->tree_smallest(_root))->left,
								   this->tree_smallest(_root)));
  }

  //******************************CAPACITY******************************

  bool
  empty() const { return (_size == 0); }

  size_type
  size() const { return (_size); }
  size_type
  max_size() const { return (Node_allocator(_alloc).max_size()); }

  //******************************ELEMENT ACCESS******************************

  mapped_type &operator[](const key_type &k) {
	_root = this->tree_insert(_root, NULL, ft::make_pair(k, mapped_type()));
	_root = tree_balance(_root);
	Node *element = _last_inserted;
	_last_inserted = NULL;
	return (element->val.second);
  }

  //******************************MODIFERS******************************

  pair<iterator, bool>
  insert(const value_type &val) {
	size_type size_before = this->size();
	_root = this->tree_insert(_root, NULL, val);
	Node *newnode = _last_inserted;
	_last_inserted = NULL;
	return (ft::pair<iterator, bool>(iterator(newnode),
									 (this->size() > size_before)));
  }

  iterator
  insert(iterator position, const value_type &val) {
	if (this->size() < 3)
	  return ((this->insert(val)).first);
	while (position->first > val.first && position != this->begin())
	  position--;

	iterator tmp(position);
	tmp++;
	while (position->first < val.first && tmp != this->end()) {
	  tmp++;
	  position++;
	}
	if (position->first == val.first)
	  return (position);
	Node *parent = position.getNode()->parent;
	if (!parent)
	  _root = this->tree_insert(_root, NULL, val);
	else {
	  tree_insert(position.getNode()->parent, NULL, val);
	  while (_root->parent != NULL)
		_root = _root->parent;
	  _root = this->tree_balance(_root);
	}
	Node *new_node = _last_inserted;
	_last_inserted = NULL;
	return (iterator(new_node));
  }

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
	while (first != last)
	  this->insert(*first++);
  }

  void
  erase(iterator position) {
	_root = this->tree_delete(_root, position->first);
  }

  size_type
  erase(const key_type &k) {
	size_type tmp = this->size();
	_root = this->tree_delete(_root, k);
	return ((this->size() == tmp) ? 0 : 1);
  }

  void
  erase(iterator first, iterator last) {
	map tmp(first, last);
	for (reverse_iterator it = tmp.rbegin(); it != tmp.rend(); ++it)
	  this->erase(it->first);
  }

  void
  swap(map &x) {
	swap(_root, x._root);
	swap(_size, x._size);
	swap(_comp, x._comp);
	swap(_alloc, x._alloc);
  }

  void
  clear() {
	_root = this->tree_clear(_root);
  }

//******************************OBSERVERS******************************

  key_compare
  key_comp() const { return (_comp); }

  class value_compare {
	// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
	friend class map;

   public:

	typedef bool result_type;
	typedef value_type first_argument_type;
	typedef value_type second_argument_type;

	bool
	operator()(const value_type &x, const value_type &y) const {
	  return comp(x.first, y.first);
	}

   protected:
	key_compare comp;
	value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
  };

  value_compare
  value_comp() const {
	return (value_compare(_comp));
  }

//******************************OPERATIONS******************************

  iterator
  find(const key_type &k) {
	Node *found = this->tree_search(_root, k);
	if (found)
	  return (iterator(found));
	return (this->end());
  }

  const_iterator
  find(const key_type &k) const {
	Node *found = this->tree_search(_root, k);

	if (found)
	  return (const_iterator(found));
	return (this->end());
  }

  size_type
  count(const key_type &k) const {
	Node *found = this->tree_search(_root, k);

	if (found)
	  return (1);
	return (0);
  }

  iterator
  lower_bound(const key_type &k) {
	iterator lower = this->begin();
	iterator end = this->end();
	while (lower != end && _comp(lower->first, k))
	  lower++;
	return (lower);
  }

  const_iterator
  lower_bound(const key_type &k) const {
	const_iterator lower = this->begin();
	const_iterator end = this->end();
	while (lower != end && _comp(lower->first, k))
	  lower++;
	return (lower);
  }

  iterator
  upper_bound(const key_type &k) {
	iterator upper = this->begin();
	iterator end = this->end();
	while (upper != end && !_comp(k, upper->first))
	  upper++;
	return (upper);
  }

  const_iterator
  upper_bound(const key_type &k) const {
	const_iterator upper = this->begin();
	const_iterator end = this->end();
	while (upper != end && !_comp(k, upper->first))
	  upper++;
	return (upper);
  }

  pair<const_iterator, const_iterator>
  equal_range(const key_type &k) const {
	pair<const_iterator, const_iterator> range;

	range.first = this->lower_bound(k);
	range.second = this->upper_bound(k);
	return (range);
  }

  pair<iterator, iterator>
  equal_range(const key_type &k) {
	pair<iterator, iterator> range;

	range.first = this->lower_bound(k);
	range.second = this->upper_bound(k);
	return (range);
  }

  //??????????????????

  allocator_type
  get_allocator() const {
	return (_alloc);
  }

 private:

  template<class U>
  void swap(U &u1, U &u2) {
	U tmp = u2;
	u2 = u1;
	u1 = tmp;
  }

  int tree_height(Node *node) const {
	if (node != NULL)
	  return (node->height);
	return (0);
  }

  int tree_getbalance(Node *node) const {
	if (node == NULL)
	  return (0);
	return (tree_height(node->left) - tree_height(node->right));
  }

  Node *tree_rr_rotate(Node *node) {
	Node *new_parent;

	new_parent = node->right;
	new_parent->parent = node->parent;
	node->parent = new_parent;
	node->right = new_parent->left;
	if (new_parent->left)
	  new_parent->left->parent = node;
	new_parent->left = node;
	node->height = ft::max(tree_height(node->left), tree_height(node->right)) + 1;
	new_parent->height = ft::max(tree_height(new_parent->left), tree_height(new_parent->right)) + 1;
	return (new_parent);
  }

  Node *tree_ll_rotate(Node *node) {
	Node *new_parent;

	new_parent = node->left;
	new_parent->parent = node->parent;
	node->parent = new_parent;
	node->left = new_parent->right;
	if (new_parent->right)
	  new_parent->right->parent = node;
	new_parent->right = node;
	node->height = ft::max(tree_height(node->left), tree_height(node->right)) + 1;
	new_parent->height = ft::max(tree_height(new_parent->left), tree_height(new_parent->right)) + 1;
	return (new_parent);
  }

  Node *tree_lr_rotate(Node *node) {
	node->left = this->tree_rr_rotate(node->left);
	return (this->tree_ll_rotate(node));
  }

  Node *tree_rl_rotate(Node *node) {
	node->right = this->tree_ll_rotate(node->right);
	return (this->tree_rr_rotate(node));
  }

  Node *tree_balance(Node *node) {
	int factor = tree_getbalance(node);

	if (factor > 1) {
	  if (tree_getbalance(node->left) > 0)
		return (this->tree_ll_rotate(node));
	  else
		return (this->tree_lr_rotate(node));
	} else if (factor < -1) {
	  if (tree_getbalance(node->right) < 0)
		return (this->tree_rr_rotate(node));
	  else
		return (this->tree_rl_rotate(node));
	}
	return (node);
  }

  Node *tree_create_node(const value_type &val, Node *parent) {
	Node *new_node = Node_allocator(_alloc).allocate(1);
	new_node->right = NULL;
	new_node->left = NULL;
	new_node->height = 1;
	new_node->parent = parent;
	_alloc.construct(&new_node->val, val);
	_size++;
	_last_inserted = new_node;
	return (new_node);
  }

  Node *tree_insert(Node *node, Node *parent, const value_type &val) {
	if (node == NULL)
	  return (tree_create_node(val, parent));
	if (_comp(val.first, node->val.first))
	  node->left = tree_insert(node->left, node, val);
	else if (_comp(node->val.first, val.first))
	  node->right = tree_insert(node->right, node, val);
	else
	  return (_last_inserted = node);
	node->height = 1 + ft::max(tree_height(node->left), tree_height(node->right));
	int factor = tree_getbalance(node);
	if (factor > 1) {
	  if (tree_getbalance(node->left) >= 0)
		return (tree_ll_rotate(node));
	  else
		return (tree_lr_rotate(node));
	} else if (factor < -1) {
	  if (tree_getbalance(node->right) <= 0)
		return (tree_rr_rotate(node));
	  else
		return (tree_rl_rotate(node));
	}
	return (node);
  }

  Node *tree_delete(Node *node, const key_type &key) {
	if (node == NULL)
	  return (NULL);
	if (_comp(key, node->val.first))
	  node->left = tree_delete(node->left, key);
	else if (_comp(node->val.first, key))
	  node->right = tree_delete(node->right, key);
	else {
	  if ((node->right == NULL) || (node->left == NULL)) {
		Node *tmp = node->right ? node->right : node->left;
		if (tmp == NULL)
		  swap(tmp, node);
		else {
		  _alloc.destroy(&node->val);
		  _alloc.construct(&node->val, tmp->val);
		  node->right = node->left = NULL;
		}
		_alloc.destroy(&tmp->val);
		Node_allocator(_alloc).deallocate(tmp, 1);
		_size--;
	  } else {
		Node *tmp = this->tree_smallest(node->right);
		_alloc.destroy(&node->val);
		_alloc.construct(&node->val, tmp->val);
		node->right = tree_delete(node->right, tmp->val.first);
	  }
	}
	if (node == NULL)
	  return (node);
	int factor = tree_getbalance(node);
	if (factor > 1) {
	  if (tree_getbalance(node->left) >= 0)
		return (tree_ll_rotate(node));
	  else
		return (tree_lr_rotate(node));
	} else if (factor < -1) {
	  if (tree_getbalance(node->right) <= 0)
		return (tree_rr_rotate(node));
	  else
		return (tree_rl_rotate(node));
	}
	return (node);
  }

  Node *tree_clear(Node *node) {
	if (!node)
	  return (NULL);
	if (node->left)
	  tree_clear(node->left);
	if (node->right)
	  tree_clear(node->right);
	_alloc.destroy(&node->val);
	Node_allocator(_alloc).deallocate(node, 1);
	_size--;
	return (NULL);
  }

  Node *tree_search(Node *node, const key_type &key) const {
	if (node == NULL)
	  return (NULL);
	if (!_comp(node->val.first, key) && !_comp(key, node->val.first))
	  return (node);
	if (_comp(key, node->val.first))
	  return (tree_search(node->left, key));
	else if (_comp(node->val.first, key))
	  return (tree_search(node->right, key));
	return (NULL);
  }

  Node *tree_smallest(Node *node) const {
	while (node && node->left != NULL)
	  node = node->left;
	return (node);
  }

  Node *tree_biggest(Node *node) const {
	while (node && node->right != NULL)
	  node = node->right;
	return (node);
  }
};

//******************************RELATION OPERATORS******************************

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs,
			   const map<Key, T, Compare, Alloc> &rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
									  rhs.begin(), rhs.end()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs,
				const map<Key, T, Compare, Alloc> &rhs) {
  if (lhs.size() != rhs.size())
	return (false);
  return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
				const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
				const map<Key, T, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs,
			   const map<Key, T, Compare, Alloc> &rhs) {
  return (rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
				const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template<class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
  x.swap(y);
}
} // ft

#endif //FT_CONTAINERS_SRC_CONTAINERS_MAP_HPP
