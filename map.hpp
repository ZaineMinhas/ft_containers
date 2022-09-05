/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:50:39 by zminhas           #+#    #+#             */
/*   Updated: 2022/09/05 16:01:07 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.hpp"
# include "iterator.hpp"
# include "red_black_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef size_t													size_type;
			typedef ft::rb_tree<key_type, mapped_type, key_compare>						tree_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::tree_iterator<value_type, node<Key, T> >			iterator;
			typedef ft::tree_iterator<const value_type, node<Key, T> >		const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			/*---------- VALUE COMPARE ----------*/
		private:
			class value_compare : std::binary_function <value_type, value_type, bool>
			{
				friend class map;

				protected:
					Compare _cmp;
					value_compare(Compare c) : _cmp(c) {}

				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool	operator()(const value_type& x, const value_type& y) const
					{ return _cmp(x.first, y.first); }
			};

		public:
			/*-------------------------- Constructor --------------------------*/

			map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _cmp(comp), _alloc(alloc), _tree(rb_tree<key_type, mapped_type, key_compare>()) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: _cmp(comp), _alloc(alloc), _tree(rb_tree<key_type, mapped_type, key_compare>())
			{ insert(first, last); }

			map(const map &x)
			: _cmp(x.key_comp()), _alloc(x.get_allocator()), _tree(rb_tree<key_type, mapped_type, key_compare>())
			{
				const_iterator	it(x.begin());
				const_iterator	ite(x.end());
				while (it != ite)
					_tree.insert(*it++);
			}

			/*-------------------------- Destructor ---------------------------*/

			~map(void) {}

			/*-------------------------- Operator= ----------------------------*/

			map	&operator=(const map &x)
			{
				_cmp = x.key_comp();
				_alloc = x.get_allocator();
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}

			/*-------------------------- Iterators ----------------------------*/

			iterator begin(void) { return (iterator(_tree.minimum(_tree.get_root()), _tree.get_leaf())); }
			const_iterator begin(void) const { return (const_iterator(_tree.minimum(_tree.get_root()), _tree.get_leaf())); }

			iterator end(void) { return (iterator(_tree.get_leaf(), _tree.get_leaf())); }
			const_iterator end(void) const { return (const_iterator(_tree.get_leaf(), _tree.get_leaf())); }

			reverse_iterator rbegin(void) { return (end()); }
			const_reverse_iterator rbegin(void) const { return (end()); }

			reverse_iterator rend(void) { return (begin()); }
			const_reverse_iterator rend(void) const { return (begin()); }

			/*-------------------------- Capacity -----------------------------*/

			bool		empty(void) const { return (!size()); }
			size_type	size(void) const { return (_tree.get_size()); }
			size_type	max_size(void) const { return (_tree.get_nalloc().max_size()); }

			/*------------------------ Element acces --------------------------*/

			mapped_type	&operator[](const key_type &k)
			{ return (insert(ft::make_pair(k, mapped_type())).first->second); }

			/*-------------------------- Modifiers ----------------------------*/

			pair<iterator, bool>	insert(const value_type &val)
			{
				iterator	it(_tree.insert(val), _tree.get_leaf());
				if (it.get_node()->double_black)
				{
					it.get_node()->double_black = false;
					return (ft::make_pair(it, false));
				}
				return (ft::make_pair(it, true));
			}

			iterator	insert(iterator position, const value_type &val)
			{
				static_cast<void>(position);
				pair<iterator, bool>	p = insert(val);
				if (p.second == false)
					return (p.first);
				return (p.first);
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}

			void	erase(iterator position)
			{
				erase(position->first);
			}

			size_type	erase(const key_type &k)
			{
				if (empty() || !_tree.del_node(k))
					return (0);
				return (1);
			}

			void		erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			void	swap(map &x) { _tree.swap(x._tree); }

			void	clear(void) { _tree.destroyer(_tree.get_root()); }

			/*-------------------------- Observers ----------------------------*/

			key_compare	key_comp(void) const { return (_cmp); }
			value_compare value_comp(void) const { return (value_compare(_cmp)); }

			/*-------------------------- Operations ---------------------------*/

			iterator find(const key_type &k)
			{
				iterator	finded(_tree.to_find(k), _tree.get_leaf());
				if (finded.get_node()->data.first == k)
					return (finded);
				return (end());
			}

			const_iterator find(const key_type &k) const
			{
				const_iterator	finded(_tree.to_find(k), _tree.get_leaf());
				if (finded.get_node()->data.first == k)
					return (finded);
				return (end());
			}

			size_type count(const key_type &k) const
			{
				iterator	finded(_tree.to_find(k), _tree.get_leaf());
				if (finded.get_node()->data.first == k)
					return (1);
				return (0);
			}

			iterator lower_bound(const key_type &k)
			{
				if (count(k))
					return (find(k));
				if (_cmp(k, _tree.minimum(_tree.get_root())->data.first))
					return (iterator(_tree.minimum(_tree.get_root()), _tree.get_leaf()));
				else if (_cmp(_tree.maximum(_tree.get_root())->data.first, k))
					return (end());
				else
				{
					iterator	it(_tree.to_find(k), _tree.get_leaf());
					return (_cmp(k, it->first) ? it : ++it);
				}
			}

			const_iterator lower_bound(const key_type &k) const
			{
				if (count(k))
					return (find(k));
				if (_cmp(k, _tree.minimum(_tree.get_root())->data.first))
					return (iterator(_tree.minimum(_tree.get_root()), _tree.get_leaf()));
				else if (_cmp(_tree.maximum(_tree.get_root())->data.first, k))
					return (end());
				else
				{
					const_iterator	it(_tree.to_find(k), _tree.get_leaf());
					return (_cmp(k, it->first) ? it : ++it);
				}
			}

			iterator upper_bound(const key_type &k)
			{
				if (count(k))
					return (++find(k));
				if (_cmp(k, _tree.minimum(_tree.get_root())->data.first))
					return (iterator(_tree.minimum(_tree.get_root()), _tree.get_leaf()));
				else if (_cmp(_tree.maximum(_tree.get_root())->data.first, k))
					return (end());
				else
				{
					iterator	it(_tree.to_find(k), _tree.get_leaf());
					return (_cmp(k, it->first) ? it : ++it);
				}
			}

			const_iterator upper_bound(const key_type &k) const
			{
				if (count(k))
					return (++find(k));
				if (_cmp(k, _tree.minimum(_tree.get_root())->data.first))
					return (iterator(_tree.minimum(_tree.get_root()), _tree.get_leaf()));
				else if (_cmp(_tree.maximum(_tree.get_root())->data.first, k))
					return (end());
				else
				{
					const_iterator	it(_tree.to_find(k), _tree.get_leaf());
					return (_cmp(k, it->first) ? it : ++it);
				}
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
			{
				if (count(k))
					return (ft::make_pair(find(k), ++find(k)));
				return (ft::make_pair(upper_bound(k), upper_bound(k)));
			}

			pair<iterator, iterator>				equal_range(const key_type &k)
			{
				if (count(k))
					return (ft::make_pair(find(k), ++find(k)));
				return (ft::make_pair(upper_bound(k), upper_bound(k)));
			}

			/*-------------------------- Allocator ----------------------------*/

			allocator_type	get_allocator(void) const { return (_alloc); }

			/*---------------------------- Utils ------------------------------*/

			// void	aff_tree(void) const { _tree.aff_tree(); }
			// void	aff_node(iterator it) const { _tree.aff_node(it.get_node()); }

		private:
			key_compare		_cmp;
			allocator_type	_alloc;
			tree_type		_tree;

			
	};

	/*--------------------- NON MEMBER FONCTION -----------------------*/
	/*--------------------- relational operators ----------------------*/

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename map<Key, T>::const_iterator	lhs_b(lhs.begin());
		typename map<Key, T>::const_iterator	rhs_b(rhs.begin());
		typename map<Key, T>::const_iterator	ite(lhs.end());

		while (lhs_b != ite)
		{
			if (lhs_b->first != rhs_b->first)
				return (false);
			lhs_b++;
			rhs_b++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (!(lhs == rhs)); }

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (!(rhs < lhs)); }

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (rhs < lhs); }

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (!(lhs < rhs)); }

	/*---------------------------- swap -------------------------------*/

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{ x.swap(y); }

}
