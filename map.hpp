/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:50:39 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/18 20:13:27 by zminhas          ###   ########.fr       */
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
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef size_t											size_type;
			typedef ft::rb_tree<key_type, mapped_type>				tree_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/*-------------------------- Constructor --------------------------*/

			map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _cmp(comp), _alloc(alloc), _tree(rb_tree<key_type, mapped_type>()), _size(0) {}
			// template <class InputIterator>
			// map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type& alloc = allocator_type());
			// map (const map &x);

			/*-------------------------- Destructor ---------------------------*/

			~map(void) {}

			/*-------------------------- Operator= ----------------------------*/

			map	&operator=(const map &x)
			{
				_cmp = x.get_cmp();
				_alloc = x.get_allocator();
				_tree = x.get_tree();
				_size = x.get_size();
				return (*this);
			}

			/*-------------------------- Iterators ----------------------------*/

			// iterator begin(void);
			// const_iterator begin(void) const;

			// iterator end(void);
			// const_iterator end(void) const;

			// reverse_iterator rbegin(void);
			// const_reverse_iterator rbegin(void) const;

			// reverse_iterator rend(void);
			// const_reverse_iterator rend(void) const;

			/*-------------------------- Capacity -----------------------------*/

			bool	empty(void) const { return (!_size); }
			size_type	size(void) const { return (_size); }
			size_type	max_size(void) const { return (_alloc.max_size()); }

			/*------------------------ Element acces --------------------------*/

			// mapped_type	&operator[](const key_type &k);

			/*-------------------------- Modifiers ----------------------------*/

			// pair<iterator, bool>	insert(const value_type &val)
			// {
			// 	if (!_tree.insert(val))
			// 		return (make_pair(/*iterator*/, false));
			// 	_size++;
			// 	return (make_pair(/*iterator*/, true));
			// }

			// iterator	insert(iterator position, const value_type &val);
			// template <class InputIterator>
			// void	insert(InputIterator first, InputIterator last);

			// void		erase(iterator position);
			size_type	erase(const key_type &k);
			// void		erase(iterator first, iterator last);

			// void	swap(map &x);

			void	clear(void)
			{
				_tree.~rb_tree();
				_size = 0;
			}

			/*-------------------------- Observers ----------------------------*/

			// key_compare	key_comp(void) const;
			// value_compare value_comp(void) const;

			/*-------------------------- Operations ---------------------------*/

			// iterator find(const key_type &k);
			// const_iterator find(const key_type &k) const;

			// size_type count(const key_type &k) const;

			// iterator lower_bound(const key_type &k);
			// const_iterator lower_bound(const key_type &k) const;

			// iterator upper_bound(const key_type &k);
			// const_iterator upper_bound(const key_type &k) const;

			// pair<const_iterator,const_iterator>	equal_range(const key_type &k) const;
			// pair<iterator,iterator>				equal_range(const key_type &k);

			/*-------------------------- Allocator ----------------------------*/

			allocator_type	get_allocator(void) const { return (_alloc); }

			/*--------------------------- Getters -----------------------------*/

			size_type		get_size(void) const { return (_size); }
			tree_type		get_tree(void) const { return (_tree); }
			key_compare		get_cmp(void) const { return (_cmp); }

		private:
			key_compare		_cmp;
			allocator_type	_alloc;
			size_type		_size;
			tree_type		_tree;
	};
}
