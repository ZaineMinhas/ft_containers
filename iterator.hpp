/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:39:36 by zminhas           #+#    #+#             */
/*   Updated: 2022/09/05 16:39:05 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "red_black_tree.hpp"
# include "utils.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class Iterator> class iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference				reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};

	template <class T> class iterator_traits<T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T> class iterator_traits<const T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	/*-------------RANDOM ACCESS ITERATOR-------------*/

	template <class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef	typename std::iterator_traits<T*>::value_type			value_type;
			typedef	typename std::iterator_traits<T*>::difference_type		difference_type;
			typedef	typename std::iterator_traits<T*>::pointer				pointer;
			typedef	typename std::iterator_traits<T*>::reference			reference;
			typedef	typename std::iterator_traits<T*>::iterator_category	iterator_category;

			/*----- Constructors -----*/

			random_access_iterator(void) : _ptr(NULL) {}
			random_access_iterator(random_access_iterator const &src) : _ptr(src.base()) {}
			random_access_iterator(pointer ptr) : _ptr(ptr) {}

			/*----- Destructor -----*/

			~random_access_iterator(void) {}

			/*----- Assignation operator -----*/

			random_access_iterator	&operator=(random_access_iterator const &rhs)
			{
				_ptr = rhs.base();
				return (*this);
			}

			/*----- Base -----*/

			pointer	base(void) const { return (_ptr); }

			/*----- Const operator -----*/

			operator	random_access_iterator<const T>(void) const { return (_ptr); }

			/*----- Dereferenced value -----*/

			reference	operator*(void) const { return (*_ptr); }
			pointer		operator->(void) const { return (_ptr); }

			/*----- Pre increment operator -----*/

			random_access_iterator	&operator++(void)
			{
				++_ptr;
				return (*this);
			}

			/*----- Post increment operator -----*/

			random_access_iterator	operator++(int)
			{
				random_access_iterator	tmp(*this);
				++_ptr;
				return (tmp);
			}

			/*----- Pre decrement operator -----*/

			random_access_iterator	&operator--(void)
			{
				--_ptr;
				return (*this);
			}

			/*----- Post decrement operator -----*/

			random_access_iterator	operator--(int)
			{
				random_access_iterator	tmp(*this);
				--_ptr;
				return (tmp);
			}

			/*----- Arithmetic + operators -----*/

			const random_access_iterator	operator+(difference_type n) const { return (_ptr + n); }

			/*----- Arithmetic + operators -----*/

			const random_access_iterator	operator-(difference_type n) const { return (_ptr - n); }

			/*----- Operator += -----*/

			const random_access_iterator	&operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}

			/*----- Operator -= -----*/

			const random_access_iterator	&operator-=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}

			/*----- Offset dereference operator -----*/

			const reference	operator[](difference_type n) const { return (_ptr[n]); }

		private:
			pointer _ptr;
	};

	/*----- Relationals operators -----*/

	template <class L_T, class R_T>
	bool	operator==(ft::random_access_iterator<L_T> const &lhs, ft::random_access_iterator<R_T> const &rhs)
	{ return (lhs.base() == rhs.base()); }
	template <class L_T, class R_T>
	bool	operator!=(ft::random_access_iterator<L_T> const &lhs, ft::random_access_iterator<R_T> const &rhs)
	{ return (lhs.base() != rhs.base()); }
	template <class L_T, class R_T>
	bool	operator<=(ft::random_access_iterator<L_T> const &lhs, ft::random_access_iterator<R_T> const &rhs)
	{ return (lhs.base() <= rhs.base()); }
	template <class L_T, class R_T>
	bool	operator>=(ft::random_access_iterator<L_T> const &lhs, ft::random_access_iterator<R_T> const &rhs)
	{ return (lhs.base() >= rhs.base()); }
	template <class L_T, class R_T>
	bool	operator<(ft::random_access_iterator<L_T> const &lhs, ft::random_access_iterator<R_T> const &rhs)
	{ return (lhs.base() < rhs.base()); }
	template <class L_T, class R_T>
	bool	operator>(ft::random_access_iterator<L_T> const &lhs, ft::random_access_iterator<R_T> const &rhs)
	{ return (lhs.base() > rhs.base()); }

	/*----- Subtraction operator -----*/

	template <class L_T, class R_T>
	typename random_access_iterator<L_T>::difference_type	operator-(random_access_iterator<L_T> const &lhs, random_access_iterator<R_T> const &rhs)
	{ return lhs.base() - rhs.base(); }

	template <class Iterator>
	random_access_iterator<Iterator>	operator-(typename random_access_iterator<Iterator>::difference_type n, random_access_iterator<Iterator> const &x)
	{ return (random_access_iterator<Iterator>(x.base() - n)); }

	/*----- Addition operator -----*/

	template <class Iterator>
	random_access_iterator<Iterator>	operator+(typename random_access_iterator<Iterator>::difference_type n, random_access_iterator<Iterator> const &x)
	{ return (random_access_iterator<Iterator>(x.base() + n)); }

	/*-------------REVERSE ITERATOR-------------*/

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;

			/*----- Constructors -----*/

			reverse_iterator(void) : _it() {}
			reverse_iterator(iterator_type it) : _it(it) {}
			reverse_iterator(pointer it) : _it(iterator_type(it)) {}
			template <class Iter>
			reverse_iterator(reverse_iterator<Iter> const &src) : _it(src.base()) {}

			/*----- Destructor -----*/

			~reverse_iterator(void) {}

			/*----- Base -----*/

			iterator_type	base(void) const { return (_it); }

			/*----- Const operator -----*/

			operator	reverse_iterator<const iterator_type>() const { return (_it); }

			/*----- Dereference operator -----*/

			reference	operator*() const
			{
				iterator_type	tmp = _it;
				return (*--tmp);
			}

			/*----- Pointer to the value -----*/

			pointer	operator->() const { return (&(operator*())); }

			/*----- Arithmetic + operator -----*/

			reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_it - n)); }

			/*----- Pre increment operator -----*/

			reverse_iterator	&operator++()
			{
				--_it;
				return (*this);
			}

			/*----- Post increment operator -----*/

			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);
				--_it;
				return (tmp);
			}

			/*----- Arithmetic += operator -----*/

			reverse_iterator	&operator+=(difference_type n)
			{
				_it -= n;
				return (*this);
			}

			/*----- Arithmetic - operator -----*/

			reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_it + n)); }

			/*----- Pre decrement operator -----*/

			reverse_iterator	&operator--()
			{
				++_it;
				return (*this);
			}

			/*----- Post decrement operator -----*/

			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);
				++_it;
				return (tmp);
			}

			/*----- Arithmetic -= operator -----*/

			reverse_iterator	&operator-=(difference_type n)
			{
				_it += n;
				return (*this);
			}

			/*----- Dereference [] operator -----*/

			reference	operator[](difference_type n) const { return (*(*this + n)); }

		private:
			iterator_type	_it;
	};

	/*----- Relational operator -----*/

	template <class L_I, class R_I>
	bool	operator==(ft::reverse_iterator<L_I> const &lhs, ft::reverse_iterator<R_I> const &rhs) { return (rhs.base() == lhs.base()); }
	template <class L_I, class R_I>
	bool	operator!=(ft::reverse_iterator<L_I> const &lhs, ft::reverse_iterator<R_I> const &rhs) { return (rhs.base() != lhs.base()); }
	template <class L_I, class R_I>
	bool	operator<=(ft::reverse_iterator<L_I> const &lhs, ft::reverse_iterator<R_I> const &rhs) { return (rhs.base() <= lhs.base()); }
	template <class L_I, class R_I>
	bool	operator>=(ft::reverse_iterator<L_I> const &lhs, ft::reverse_iterator<R_I> const &rhs) { return (rhs.base() >= lhs.base()); }
	template <class L_I, class R_I>
	bool	operator<(ft::reverse_iterator<L_I> const &lhs, ft::reverse_iterator<R_I> const &rhs) { return (rhs.base() < lhs.base()); }
	template <class L_I, class R_I>
	bool	operator>(ft::reverse_iterator<L_I> const &lhs, ft::reverse_iterator<R_I> const &rhs) { return (rhs.base() > lhs.base()); }

	/*----- Addition operator -----*/

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &x) { return (reverse_iterator<Iterator>(x.base() - n)); }

	/*----- Subtraction operator -----*/

	template<typename _Iterator>
	typename reverse_iterator<_Iterator>::difference_type	operator-(const reverse_iterator<_Iterator> &rhs, const reverse_iterator<_Iterator> &lhs) { return lhs.base() - rhs.base(); }

	template<typename _IteratorL, typename _IteratorR>
	typename reverse_iterator<_IteratorL>::difference_type	operator-(const reverse_iterator<_IteratorL> &rhs, const reverse_iterator<_IteratorR> &lhs) { return lhs.base() - rhs.base(); }

	/*-------------TREE ITERATOR-------------*/

	template<class T, class node>
	class tree_iterator
	{
		public:
			typedef T				value_type;
			typedef	node			node_type;
			typedef value_type*		pointer;
			typedef	value_type&		reference;
			typedef std::ptrdiff_t	difference_type;

		/*----- Constructors -----*/

			tree_iterator(void) : _node(NULL), _leaf(NULL) {}
			tree_iterator(node_type *nod, node_type *leaf) : _node(nod), _leaf(leaf) {}
			tree_iterator(const tree_iterator<value_type, node_type> &it) : _node(it.get_node()), _leaf(it.get_leaf()) {}

			/*----- Destructor -----*/

			~tree_iterator(void) {}

			/*----- Assignation operator -----*/

			tree_iterator	&operator=(const tree_iterator &it)
			{
				_node = it.get_node();
				_leaf = it.get_leaf();
				return (*this);
			}

			/*----- Const operator -----*/

			operator	tree_iterator<const value_type, node>(void) const
			{ return (tree_iterator<const value_type, node>(_node, _leaf)); }

			/*----- Getters -----*/

			node_type	*get_node(void) const { return (_node); }
			node_type	*get_leaf(void) const { return (_leaf); }

			/*----- Dereferenced value -----*/

			value_type	&operator*(void) const { return (_node->data); }
			value_type	*operator->(void) const { return (&_node->data); }

			/*----- Pre increment operator -----*/

			tree_iterator	&operator++(void)
			{
				_node = next(_node);
				return (*this);
			}

			/*----- Post increment operator -----*/

			tree_iterator	operator++(int)
			{
				node_type	*tmp = _node;
				_node = next(_node);
				return (tree_iterator(tmp, _leaf));
			}

			/*----- Pre decrement operator -----*/

			tree_iterator	&operator--(void)
			{
				_node = prev(_node);
				return (*this);
			}
			
			/*----- Post decrement operator -----*/

			tree_iterator	operator--(int)
			{
				node_type	*tmp = _node;
				_node = prev(_node);
				return (tree_iterator(tmp, _leaf));
			}

			/*----- Utils -----*/

			void	aff_node(node_type *nod) const
				{
					if (!nod)
					{
						std::cout << "(null)" <<std::endl;
						return ;
					}
					std::string	color;
					nod->color ? color = "black" : color = "red";
					std::cout << nod->data.first << " | " << nod->data.second << " | " << color << std::endl;
				}

			node_type	*next(node_type *nod)
			{
				node_type	*tmp = nod;
				while (tmp->parent)
					tmp = tmp->parent;
				if (nod == _leaf)
					return (maximum(tmp));

				if (nod->right == _leaf)
				{
					tmp = nod;
					while (tmp->parent && tmp == tmp->parent->right)
						tmp = tmp->parent;
					tmp = tmp->parent;
					return (!tmp ? _leaf : tmp);
				}
				tmp = nod->right;
				while (tmp->left != _leaf)
					tmp = tmp->left;
				return (!tmp ? _leaf : tmp);
			}

			node_type	*prev(node_type *nod)
			{
				node_type	*tmp = nod;
				while (tmp->parent)
					tmp = tmp->parent;
				if (nod == _leaf)
					return (maximum(tmp));

				if (nod->left == _leaf)
				{
					tmp = nod;
					while (tmp->parent && tmp == tmp->parent->left)
						tmp = tmp->parent;
					tmp = tmp->parent;
					return (tmp);
				}
				tmp = nod->left;
				while (tmp->right != _leaf)
					tmp = tmp->right;
				return (tmp);
			}

		private:
			node_type	*_node;
			node_type	*_leaf;

			/*----- Utils -----*/

			node_type	*minimum(node_type* x) const
			{
				while (x->left != _leaf)
					x = x->left;
				return (x);
			}

			node_type	*maximum(node_type* x) const
			{
				while (x->right != _leaf)
					x = x->right;
				return (x);
			}
	};

	/*----- Relational operator -----*/

	template<class L_T, class R_T, class L_node, class R_node>
	bool	operator==(ft::tree_iterator<L_T, L_node> const &lhs, ft::tree_iterator<R_T, R_node> const &rhs)
	{ return (lhs.get_node() == rhs.get_node()); }

	template<class L_T, class R_T, class L_node, class R_node>
	bool	operator!=(ft::tree_iterator<L_T, L_node> const &lhs, ft::tree_iterator<R_T, R_node> const &rhs)
	{ return (!(lhs == rhs)); }

}

#endif
