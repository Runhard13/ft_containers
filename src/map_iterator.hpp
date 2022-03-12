//
// Created by Carletta Drennan on 3/12/22.
//

#ifndef FT_CONTAINERS_SRC_MAP_ITERATOR_HPP
#define FT_CONTAINERS_SRC_MAP_ITERATOR_HPP

namespace ft
{

template<class Key, class T, class Compare, typename Node> class Map_const_iterator;
template<class Key, class T, class Compare, typename Node>
class Map_iterator
{
public:

  typedef Key key_type;
  typedef T mapped_type;
  typedef Compare key_compare;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef value_type *pointer;
  typedef value_type &reference;
  typedef Node *NodePtr;

protected:

  NodePtr m_node;
  NodePtr m_endnode;

private:

  Map_iterator(const Map_const_iterator<Key, T, Compare, Node> &) {}

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
  Map_iterator(const Map_iterator &from)
	  : m_node(from.m_node), m_endnode(from.m_endnode) {}
  ~Map_iterator() {}

  NodePtr getNode() const { return m_node; }
  Map_iterator &operator=(const Map_iterator &it)
  {
	if (this != &it)
	{
	  m_node = it.m_node;
	  m_endnode = it.m_endnode;
	}
	return (*this);
  }

  bool operator==(const Map_iterator &it) const
  {
	return (m_node == it.m_node);
  }
  bool operator!=(const Map_iterator &it) const
  {
	return (m_node != it.m_node);
  }
  reference operator*() const { return (m_node->val); }
  pointer operator->() const { return (&(m_node->val)); }
  Map_iterator &operator++()
  {
	if (m_node == NULL)
	{
	  m_node = m_endnode;
	  return (*this);
	} else if (m_node->right != NULL)
	{
	  m_node = m_node->right;
	  while (m_node->left != NULL)
		m_node = m_node->left;
	} else
	{
	  Node *origin = m_node;
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
  Map_iterator &operator--()
  {
	if (m_node == NULL)
	{
	  m_node = m_endnode;
	  return (*this);
	} else if (m_node->left != NULL)
	{
	  m_node = m_node->left;
	  while (m_node->right != NULL)
		m_node = m_node->right;
	} else
	{
	  Node *origin = m_node;
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
class Map_const_iterator : public Map_iterator<Key, T, Compare, Node>
{
public:

  typedef Key key_type;
  typedef T mapped_type;
  typedef Compare key_compare;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef value_type const &const_reference;
  typedef value_type const *const_pointer;
  typedef Node *NodePtr;

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
  Map_const_iterator(const Map_iterator<Key, T, Compare, Node> &from)
  {
	this->m_node = from.getNode();
  }

  Map_const_iterator &operator=(const Map_const_iterator &it)
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

  typedef Key key_type;
  typedef T mapped_type;
  typedef Compare key_compare;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef value_type *pointer;
  typedef value_type &reference;
  typedef Node *NodePtr;

protected:

  Map_iterator<Key, T, Compare, Node> m_base;

private:

  Map_reverse_iterator(const Map_const_reverse_iterator<Key, T, Compare, Node> &) {}

public:

  Map_reverse_iterator(NodePtr node = NULL)
	  : m_base(Map_iterator<Key, T, Compare, Node>(node)) {}
  Map_reverse_iterator(NodePtr node, NodePtr endnode)
	  : m_base(Map_iterator<Key, T, Compare, Node>(node, endnode)) {}
  explicit Map_reverse_iterator(Map_iterator<Key, T, Compare, Node> from)
	  : m_base(from) {}
  Map_reverse_iterator(const Map_reverse_iterator<Key, T, Compare, Node> &rev_it)
	  : m_base(rev_it.m_base) {}

  NodePtr getNode() const { return (this->m_base.getNode()); }
  Map_iterator<Key, T, Compare, Node> base() const
  {
	return (this->m_base);
  }
  Map_reverse_iterator &operator=(const Map_reverse_iterator &it)
  {
	if (this != &it)
	{
	  m_base = it.m_base;
	  m_base.operator++();
	}
	return (*this);
  }
  bool operator==(const Map_reverse_iterator &it) const
  {
	return (m_base == it.m_base);
  }
  bool operator!=(const Map_reverse_iterator &it) const
  {
	return (m_base != it.m_base);
  }
  reference operator*() const
  {
	return (*(Map_iterator<Key, T, Compare, Node>(this->m_base)));
  }
  pointer operator->() const
  {
	return (&this->operator*());
  }
  Map_reverse_iterator &operator++()
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
  Map_reverse_iterator &operator--()
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
class Map_const_reverse_iterator : public Map_reverse_iterator<Key, T, Compare, Node>
{
public:

  typedef Key key_type;
  typedef T mapped_type;
  typedef Compare key_compare;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef value_type const &const_reference;
  typedef value_type const *const_pointer;
  typedef Node *NodePtr;

  explicit Map_const_reverse_iterator(Map_iterator<Key, T, Compare, Node> from)
  {
	this->m_base = from.getNode();
	this->m_base.operator--();
  }
  Map_const_reverse_iterator(NodePtr node = NULL)
  {
	this->m_base = Map_iterator<Key, T, Compare, Node>(node);
  }
  Map_const_reverse_iterator(NodePtr node, NodePtr endnode)
  {
	this->m_base = Map_iterator<Key, T, Compare, Node>(node, endnode);
  }
  Map_const_reverse_iterator(Map_const_iterator<Key, T, Compare, Node> from)
  {
	this->m_base = from.getNode();
	this->m_base.operator--();
  }
  Map_const_reverse_iterator(const Map_reverse_iterator<Key, T, Compare, Node> &from)
  {
	this->m_base = from.getNode();
  }

  Map_const_reverse_iterator &operator=(const Map_const_reverse_iterator &it)
  {
	if (this != &it)
	  this->m_base = it.m_base;
	return (*this);
  }
  bool operator==(const Map_const_reverse_iterator &it) const
  {
	return (this->m_base == it.m_base);
  }
  bool operator!=(const Map_const_reverse_iterator &it) const
  {
	return (this->m_base != it.m_base);
  }
  const_reference operator*() const
  {
	return (*(Map_iterator<Key, T, Compare, Node>(this->m_base)));
  }
  const_pointer operator->() const { return (&this->operator*()); }
};
}

#endif //FT_CONTAINERS_SRC_MAP_ITERATOR_HPP
