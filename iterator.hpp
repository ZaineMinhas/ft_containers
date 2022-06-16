/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:39:36 by zminhas           #+#    #+#             */
/*   Updated: 2022/06/16 19:48:18 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <iterator>
# include <memory>
# include <deque>

namespace ft {
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

	template <class T>
	class RandomAccessIterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;

			RandomAccessIterator() : _ptr(NULL) {}
			RandomAccessIterator(RandomAccessIterator &src) : _ptr(src.base()) {}
			RandomAccessIterator(pointer ptr) : _ptr(ptr) {}
			~RandomAccessIterator();

			RandomAccessIterator	operator=(RandomAccessIterator const &rhs)
			{
				_ptr = rhs.base();
				return (*this);
			}

			pointer	base(void) const { return (_ptr); }


			reference	operator*(void) const { return (*_ptr); }
			pointer		operator->(void) const { return (_ptr); }

			RandomAccessIterator	&operator++(void)
			{
				++_ptr;
				return (*this);
			}

			RandomAccessIterator	operator++(int)
			{
				RandomAccessIterator	tmp(*this);
				++_ptr;
				return (tmp);
			}

			RandomAccessIterator	&operator--(void)
			{
				--_ptr;
				return (*this);
			}

			RandomAccessIterator	operator--(int)
			{
				RandomAccessIterator	tmp(*this);
				--_ptr;
				return (tmp);
			}

			const RandomAccessIterator	operator+(difference_type n) const { return (_ptr + n); }
			const RandomAccessIterator	operator-(difference_type n) const { return (_ptr - n); }

			const RandomAccessIterator	&operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}

			const RandomAccessIterator	&operator-=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}

			const reference	operator[](difference_type n) const { return (_ptr[n]); }

		private:
			pointer _ptr;
	};

	template <class Iterator>
	bool	operator==(ft::RandomAccessIterator<Iterator> const &lhs, ft::RandomAccessIterator<Iterator> const &rhs) { return (lhs.base() == rhs.base()); }
	template <class Iterator>
	bool	operator!=(ft::RandomAccessIterator<Iterator> const &lhs, ft::RandomAccessIterator<Iterator> const &rhs) { return (lhs.base() != rhs.base()); }
	template <class Iterator>
	bool	operator<=(ft::RandomAccessIterator<Iterator> const &lhs, ft::RandomAccessIterator<Iterator> const &rhs) { return (lhs.base() <= rhs.base()); }
	template <class Iterator>
	bool	operator>=(ft::RandomAccessIterator<Iterator> const &lhs, ft::RandomAccessIterator<Iterator> const &rhs) { return (lhs.base() >= rhs.base()); }
	template <class Iterator>
	bool	operator<(ft::RandomAccessIterator<Iterator> const &lhs, ft::RandomAccessIterator<Iterator> const &rhs) { return (lhs.base() < rhs.base()); }
	template <class Iterator>
	bool	operator>(ft::RandomAccessIterator<Iterator> const &lhs, ft::RandomAccessIterator<Iterator> const &rhs) { return (lhs.base() > rhs.base()); }
}

#endif
