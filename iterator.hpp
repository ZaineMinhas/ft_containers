/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:39:36 by zminhas           #+#    #+#             */
/*   Updated: 2022/06/24 19:16:20 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "utils.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	/*-------------Random Access Iterator-------------*/

	template <class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;

			/*----- Constructors -----*/

			random_access_iterator() : _ptr(NULL) {}
			random_access_iterator(random_access_iterator const &src) : _ptr(src.base()) {}
			random_access_iterator(pointer ptr) : _ptr(ptr) {}

			/*----- Destructor -----*/

			~random_access_iterator() {}

			/*----- Assignation operator -----*/

			random_access_iterator	&operator=(random_access_iterator const &rhs)
			{
				_ptr = rhs.base();
				return (*this);
			}

			/*----- Base -----*/

			pointer	base(void) const { return (_ptr); }

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

	template <class Iterator>
	bool	operator==(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iterator> const &rhs)
	{ return (lhs.base() == rhs.base()); }
	template <class Iterator>
	bool	operator!=(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iterator> const &rhs)
	{ return (lhs.base() != rhs.base()); }
	template <class Iterator>
	bool	operator<=(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iterator> const &rhs)
	{ return (lhs.base() <= rhs.base()); }
	template <class Iterator>
	bool	operator>=(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iterator> const &rhs)
	{ return (lhs.base() >= rhs.base()); }
	template <class Iterator>
	bool	operator<(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iterator> const &rhs)
	{ return (lhs.base() < rhs.base()); }
	template <class Iterator>
	bool	operator>(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iterator> const &rhs)
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

	/*-------------Reverse Iterator-------------*/

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;

			/*----- Constructors -----*/

			reverse_iterator() : _it() {}
			reverse_iterator(iterator_type it) : _it(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &src) : _it(src.base()) {}

			/*----- Destructor -----*/

			~reverse_iterator();

			/*----- Base -----*/

			iterator_type	base(void) const { return (_it); }

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
				return (*this);
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
				return (*this);
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

	template <class Iterator>
	bool	operator==(ft::reverse_iterator<Iterator> const &lhs, ft::reverse_iterator<Iterator> const &rhs) { return (rhs.base() == lhs.base()); }
	template <class Iterator>
	bool	operator!=(ft::reverse_iterator<Iterator> const &lhs, ft::reverse_iterator<Iterator> const &rhs) { return (rhs.base() != lhs.base()); }
	template <class Iterator>
	bool	operator<=(ft::reverse_iterator<Iterator> const &lhs, ft::reverse_iterator<Iterator> const &rhs) { return (rhs.base() <= lhs.base()); }
	template <class Iterator>
	bool	operator>=(ft::reverse_iterator<Iterator> const &lhs, ft::reverse_iterator<Iterator> const &rhs) { return (rhs.base() >= lhs.base()); }
	template <class Iterator>
	bool	operator<(ft::reverse_iterator<Iterator> const &lhs, ft::reverse_iterator<Iterator> const &rhs) { return (rhs.base() < lhs.base()); }
	template <class Iterator>
	bool	operator>(ft::reverse_iterator<Iterator> const &lhs, ft::reverse_iterator<Iterator> const &rhs) { return (rhs.base() > lhs.base()); }

	/*----- Addition operator -----*/

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &x) { return (reverse_iterator<Iterator>(x.base() - n)); }

	/*----- Subtraction operator -----*/

	template<typename _Iterator>
	typename reverse_iterator<_Iterator>::difference_type	operator-(const reverse_iterator<_Iterator> &rhs, const reverse_iterator<_Iterator> &lhs) { return lhs.base() - rhs.base(); }

	template<typename _IteratorL, typename _IteratorR>
	typename reverse_iterator<_IteratorL>::difference_type	operator-(const reverse_iterator<_IteratorL> &rhs, const reverse_iterator<_IteratorR> &lhs) { return lhs.base() - rhs.base(); }
}

#endif
