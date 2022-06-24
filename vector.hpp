/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:15:35 by zminhas           #+#    #+#             */
/*   Updated: 2022/06/24 18:41:49 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef const T											const_value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef std::ptrdiff_t									difference_type;
			typedef std::size_t										size_type;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef const reverse_iterator							const_reverse_iterator;
			typedef ft::random_access_iterator<const_value_type>	const_iterator;

			/*-------------------------- Constructor --------------------------*/

			explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _capacity(0), _size(0) {
				_vector = _alloc.allocate(0);
			}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(n), _size(n)
			{
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_vector[i], val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc),  _capacity(0), _size(0)
			{
				_size = first;
				_capacity = _size;
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; first++ < last; i++)
					_alloc.construct(&_vector[i], last);
			}

			vector(const vector &x) : _alloc(get_allocator()), _capacity(x.capacity()), _size(x.size())
			{
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_vector[i], x[i]);
			}

			/*-------------------------- Destructor ---------------------------*/

			~vector()
			{
				clear();
				_alloc.deallocate(_vector, _capacity);
			}

			/*-------------------------- Operator= ----------------------------*/

			vector	&operator=(const vector &x)
			{
				_alloc = x.get_allocator();
				_capacity = x.capacity();
				_size = x.size();
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_vector + i, x[i]);
				return (*this);
			}

			/*-------------------------- Iterators ----------------------------*/

			iterator				begin() { return (_vector); }
			const_iterator			begin() const { return (_vector); }
			iterator				end() { return (&_vector[_size]); }
			const_iterator			end() const { return (&_vector[_size]); }
			reverse_iterator		rbegin() { return (&_vector[_size - 1]); }
			const_reverse_iterator	rbegin() const { return (&_vector[_size - 1]); }
			reverse_iterator		rend() { return (_vector - 1); }
			const_reverse_iterator	rend() const { return (_vector - 1); }

			/*-------------------------- Capacity -----------------------------*/

			size_type	size() const { return (_size); }

			size_type	max_size() const { return (_alloc.max_size()); }

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
				this->~vector();
				_capacity = n;
				_size = tmp.size();
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
					throw (std::out_of_range("index out of range"));
				return (_vector[n]);
			}

			const_reference	at(size_type n) const
			{
				if (n >= _size || n < 0)
					throw (std::out_of_range("index out of range"));
				return (_vector[n]);
			}

			reference		front() { return (_vector[0]); }

			const_reference	front() const { return (_vector[0]); }

			reference		back() { return (_vector[_size - 1]); }

			const_reference	back() const { return (_vector[_size - 1]); }

			/*-------------------------- Modifiers ----------------------------*/

			template <class InputIterator>
  			void		assign(InputIterator first, InputIterator last)
			{
				while (first < last)
				{
					push_back(*first);
					first++;
				}
			}

			void		assign(size_type n, const value_type &val)
			{
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}
	
			void		push_back(const value_type &val)
			{
				if (_size + 1 >= _capacity)
					reserve((_capacity + 1) * 2);
				_vector[_size++] = val;
			}

			void		pop_back()
			{
				if (!_size)
					return ;
				_alloc.destroy(&_vector[--_size]);
			}

			iterator	insert(iterator position, const value_type &val)
			{
				size_type	pos = 0;
				for (; pos <= _size; pos++)
					if (_vector + pos == &*position)
						break ;
				if (pos > _size)
					throw (std::out_of_range("index out of range"));
				reserve(++_size);
				for (size_type i = 0; i < _size - 1 - pos; i++)
					_vector[_size - i] = _vector[_size - i - 1];
				_vector[pos] = val;
				return (_vector + pos);
			}

			void		insert(iterator position, size_type n, const value_type &val)
			{
				size_type	pos = 0;
				for (; pos <= _size; pos++)
					if (_vector + pos == &*position)
						break ;
				if (pos > _size)
					throw (std::out_of_range("index out of range"));
				_size += n;
				reserve(_size + n);
				for (size_type i = 0; i < _size - n - pos + 1; i++)
					_vector[_size - i] = _vector[_size - i - 1];
				for (size_type i = 0; i < n; i++)
					_vector[pos + i] = val;
			}

			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type	pos = 0;
				size_type	n = last - first;
				for (; pos <= _size; pos++)
					if (_vector + pos == &*position)
						break ;
				if (pos > _size)
					throw (std::out_of_range("index out of range"));
				_size += n;
				reserve(_size + n);
				for (size_type i = 0; i < _size - n - pos + 1; i++)
					_vector[_size - i] = _vector[_size - i - 1];
				for (size_type i = 0; i < n; i++)
				{
					_vector[pos + i] = *first;
					first++;
				}
			}

			iterator	erase(iterator position)
			{
				size_type	pos = 0;
				for (; pos <= _size; pos++)
					if (_vector + pos == &*position)
						break ;
				if (pos > _size)
					throw (std::out_of_range("index out of range"));
				_alloc.destroy(&_vector[pos]);
				for (size_type i = pos; i < _size; i++)
					_vector[i] = _vector[i + 1];
				_size--;
				return (_vector + pos + 1);
			}

			iterator	erase(iterator first, iterator last)
			{
				size_type	pos = 0;
				for (; pos <= _size; pos++)
					if (_vector + pos == &*first)
						break ;
				if (pos > _size)
					throw (std::out_of_range("index out of range"));
				size_type	n = last - first;
				for (size_type i = 0; i < n; i++)
					_alloc.destroy(&_vector[pos + i]);
				for (size_type i = 0; i < _size - pos - n; i++)
					_vector[pos + i] = _vector[pos + i + n];
				_size -= n;
				return (_vector + pos + n);
			}

			void		swap(vector &x)
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

		private:
			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;
			value_type		*_vector;

	};

	/*--------------------- NON MEMBER FONCTION -----------------------*/
	/*--------------------- relational operators ----------------------*/

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (typename vector<T,Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
			return (false);
		for (typename vector<T,Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] == rhs[i])
				return (false);
		return (true);
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		for (typename vector<T,Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++)
		{
			if (lhs[i] < rhs[i])
				return (true);
			else if (lhs[i] > rhs[i])
				return (false);
		}
		if (lhs.size() < rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		for (typename vector<T,Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++)
		{
			if (lhs[i] <= rhs[i])
				return (true);
			else if (lhs[i] > rhs[i])
				return (false);
		}
		if (lhs.size() <= rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		for (typename vector<T,Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++)
		{
			if (lhs[i] > rhs[i])
				return (true);
			else if (lhs[i] < rhs[i])
				return (false);
		}
		if (lhs.size() > rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		for (typename vector<T,Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++)
		{
			if (lhs[i] >= rhs[i])
				return (true);
			else if (lhs[i] < rhs[i])
				return (false);
		}
		if (lhs.size() >= rhs.size())
			return (true);
		return (false);
	}

	/*----------------------------- Swap ------------------------------*/

	template <class T, class Alloc>
	void	swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
	{
		vector<T,Alloc>	tmp(x);
		x = y;
		y = tmp;
	}
}
#endif
