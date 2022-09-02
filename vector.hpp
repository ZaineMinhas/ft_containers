/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:15:35 by zminhas           #+#    #+#             */
/*   Updated: 2022/09/02 17:38:14 by zminhas          ###   ########.fr       */
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
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef std::ptrdiff_t									difference_type;
			typedef std::size_t										size_type;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/*-------------------------- Constructor --------------------------*/

			explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(0), _size(0)
			{ _vector = _alloc.allocate(0); }

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(n), _size(n)
			{
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_vector[i], val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: _alloc(alloc),  _capacity(0), _size(0)
			{
				InputIterator tmp = first;
				while (tmp++ != last)
					_size++;
				_capacity = _size;
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; first != last; i++)
					_alloc.construct(&_vector[i], *first++);
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

			iterator				begin() { return (iterator(_vector)); }
			const_iterator			begin() const { return (const_iterator(_vector)); }

			iterator				end() { return (iterator(_vector + _size)); }
			const_iterator			end() const { return (const_iterator(_vector + _size)); }

			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }

			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }

			/*-------------------------- Capacity -----------------------------*/

			size_type	size() const { return (_size); }

			size_type	max_size() const { return (_alloc.max_size()); }

			void		resize(size_type n, value_type val = value_type())
			{
				if (n == _size)
					return ;
				else if (n < _size)
					while (_size > n)
						_alloc.destroy(&_vector[_size--]);
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
				if (n > this->max_size())
					throw (std::out_of_range("vector: out of range"));
				if (n <= this->_capacity)
					return ;

				pointer old_vector = this->_vector;
				this->_vector = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(&this->_vector[i], old_vector[i]);
				for	(size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(&old_vector[i]);
				this->_alloc.deallocate(old_vector, this->_capacity);
				this->_capacity = n;

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
  			void		assign(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				clear();
				InputIterator tmp = first;
				while (tmp++ != last)
					_size++;
				if (_size > _capacity)
					reserve(_size);
				for (size_type i = 0; first != last; i++)
					_alloc.construct(&_vector[i], *first++);
			}

			void		assign(size_type n, const value_type &val)
			{
				clear();
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
				for (size_type i = 0; i < _size - pos; i++)
					_vector[_size - i - 1] = _vector[_size - i - 2];
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
				reserve(_size);
				for (size_type i = 0; i < _size - n - pos; i++)
					_vector[_size - i - 1] = _vector[_size - i - n - 1];
				for (size_type i = 0; i < n; i++)
					_vector[pos + i] = val;
			}

			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type	pos = 0;
				size_type	n = 0;
				InputIterator tmp = first;
				while (tmp++ != last)
					n++;
				for (; pos <= _size; pos++)
					if (_vector + pos == &*position)
						break ;
				if (pos > _size)
					throw (std::out_of_range("index out of range"));
				_size += n;
				reserve(_size);
				for (size_type i = 0; i < _size - n - pos + 1; i++)
					_vector[_size - i - 1] = _vector[_size - i - n - 1];
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
				if (pos == _size)
					_alloc.destroy(&_vector[_size]);
				else
				{
					_alloc.destroy(&_vector[pos]);
					for (size_type i = pos; i < _size; i++)
						if (i < _size - 1)
							_vector[i] = _vector[i + 1];
				}
				_size--;
				return (_vector + pos);
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
				return (_vector + pos);
			}

			void		swap(vector &x)
			{
				allocator_type	alloc = x.get_allocator();
				size_type		capacity = x.capacity();
				size_type		size = x.size();
				pointer			vector = x._vector;

				x._alloc = _alloc;
				x._capacity = _capacity;
				x._size = _size;
				x._vector = _vector;

				_alloc = alloc;
				_capacity = capacity;
				_size = size;
				_vector = vector;
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
			pointer			_vector;

	};

	/*--------------------- NON MEMBER FONCTION -----------------------*/
	/*--------------------- relational operators ----------------------*/

	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{ return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++)
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
	bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{ return (rhs < lhs); }

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{ return (!(lhs < rhs)); }

	/*----------------------------- Swap ------------------------------*/

	template <class T, class Alloc>
	void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{ x.swap(y); }
}
#endif
