/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:15:35 by zminhas           #+#    #+#             */
/*   Updated: 2022/06/15 21:26:16 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef allocator_type::reference			reference;
			typedef allocator_type::const_reference		const_reference;
			typedef allocator_type::pointer				pointer;
			typedef allocator_type::const_pointer		const_pointer;
			typedef std::ptrdiff_t						difference_type;
			typedef std::size_t							size_type;

			/*-------------------------- Constructor --------------------------*/

			explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc) {
				_vector = _alloc.allocate(0);
			}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
			{
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_vector + i, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0) _alloc(alloc)
			{
				while (first < last)
				{
					_size++
					first++;
				}
				_capacity = _size;
				_vector = alloc.allocate(_capacity);
				first -= _size;
				for (size_type i = 0; first < last; i++)
				{
					_alloc.construct(_vector + i, *first);
					first++;
				}
			}

			vector(const vector &x) : _size(x.size()), _capacity(x.capacity()), _alloc(get_allocator())
			{
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_vector + i, x[i]);
			}

			/*-------------------------- Destructor ---------------------------*/

			~vector()
			{
				while (_size)
					_alloc.destroy(&_vector[--_size]);
				_alloc.deallocate(_vector, _capacity);
			}

			/*-------------------------- Operator= ----------------------------*/

			vector	&operator=(const vector &x)
			{
				_alloc = x.get_allocator();
				_capacity = x.capacity();
				_size = x.size();
				for (size_type i = 0; i < _size; i++)
					&_vector[i] = x[i];
			}

			/*-------------------------- Iterators ----------------------------*/

			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

			/*-------------------------- Capacity -----------------------------*/

			size_type	size() const { return (_size); }

			size_type	max_size() const { return (allocator_type::max_size()); }

			void		resize(size_type n, value_type val = value_type())
			{
				if (n == _size)
					return ;
				else if (n < _size)
				{
					while (_size > n)
					{
						_alloc.destroy(&_vector[_size]);
						_size--;
					}
				}
				else
				{
					if (n > _capacity)
					{
						reserve(n);
						while (_size < n)
							_alloc.construct(&_vector[_size++], val);
					}
					else
						while (_size < n)
							_alloc.construct(&_vector[_size++], val);
				}
			}

			size_type	capacity() const { return (_capacity); }

			bool		empty() const { return (!_size); }

			void		reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				vector	tmp(*this);
				~vector();
				_capacity = n;
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < tmp.size(); i++)
					_alloc.construct(&_vector[i], tmp[i]);
			}

			/*------------------------- Element acces -------------------------*/

			reference		operator[](size_type n) { return (_vector[n]); }

			const_reference	operator[](size_type n) const { return (_vector[n]); }

			reference		at(size_type n)
			{
				if (n >= _size || n < 0)
					throw (std::out_of_range());
				return (_vector[n]);
			}

			const_reference	at(size_type n) const
			{
				if (n >= _size || n < 0)
					throw (std::out_of_range());
				return (_vector[n]);
			}

			reference		front() { return (_vector[0]); }

			const_reference	front() const { return (_vector[0]); }

			reference		back() { return (_vector[_size - 1]); }

			const_reference	back() const { return (_vector[_size - 1]); }

			/*-------------------------- Modifiers ----------------------------*/

			template <class InputIterator>
  			void		assign(InputIterator first, InputIterator last);
			void		assign(size_type n, const value_type& val);
	
			void		push_back(const value_type &val)
			{
				if (_size + 1 >= _capacity)
					reserve((_capacity + 1) * 2);
				&_vector[_size++] = val;
			}

			void		pop_back()
			{
				if (!_size)
					return ;
				_alloc.destroy(&_vector[--_size]);
			}

			iterator	insert(iterator position, const value_type& val);
			void		insert(iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last);
			iterator	erase(iterator position);
			iterator	erase(iterator first, iterator last);

			void		swap(vector& x)
			{
				vector	tmp(*this);
				*this = x;
				x = tmp;
			}

			void		clear()
			{
				while (_size)
					_alloc.destroy(&_vector[--_size]);
			}

			/*-------------------------- Allocator ----------------------------*/

			allocator_type	get_allocator() const { return (_alloc); }

			/*-------------------- Template specializations -------------------*/

			template < class T, class Alloc = allocator<T> > class vector;
			template <class Alloc> class vector<bool,Alloc>;

		private:
			allocator_type	_alloc;
			value_type		*_vector;
			size_type		_size;
			size_type		_capacity;

	};
}
#endif
