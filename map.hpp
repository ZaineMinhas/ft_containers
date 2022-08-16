/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:50:39 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/16 15:16:38 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.hpp"
# include "iterator.hpp"
# include "red_black_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >>
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef allocator_type::reference						reference;
			typedef allocator_type::const_allocator					const_allocator;
			typedef allocator_type::pointer							pointer;
			typedef allocator_type::const_pointer					const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/*-------------------------- Constructor --------------------------*/

			map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type& alloc = allocator_type());
			map (const map &x);

			/*-------------------------- Destructor ---------------------------*/

			~map() {}

			/*-------------------------- Operator= ----------------------------*/

			map	&operator=(const map &x);

			/*-------------------------- Iterators ----------------------------*/

			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			reverse_iterator rend();
			const_reverse_iterator rend() const;

			/*-------------------------- Capacity -----------------------------*/

			bool	empty() const;
			size_type	size() const;
			size_type	max_size() const;

			/*------------------------ Element acces --------------------------*/

			mapped_type	&operator[](const key_type &k);

			/*-------------------------- Modifiers ----------------------------*/

			pair<iterator,bool>	insert(const value_type &val);
			iterator	insert(iterator position, const value_type &val);
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last);

			void		erase(iterator position);
			size_type	erase(const key_type &k);
			void		erase(iterator first, iterator last);

			void	swap(map &x);

			void	clear();

			/*-------------------------- Observers ----------------------------*/

			key_compare	key_comp() const;
			value_compare value_comp() const;

			/*-------------------------- Operations ---------------------------*/

			iterator find(const key_type &k);
			const_iterator find(const key_type &k) const;

			size_type count(const key_type &k) const;

			iterator lower_bound(const key_type &k);
			const_iterator lower_bound(const key_type &k) const;

			iterator upper_bound(const key_type &k);
			const_iterator upper_bound(const key_type &k) const;

			pair<const_iterator,const_iterator> equal_range(const key_type &k) const;
			pair<iterator,iterator>             equal_range(const key_type &k);

			/*-------------------------- Allocator ----------------------------*/

			allocator_type	get_allocator() const;

		private:
	};
}
