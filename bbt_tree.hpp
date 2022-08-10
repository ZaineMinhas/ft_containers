/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:39:12 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/10 18:50:34 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.hpp"

namespace ft
{
	template<class Key, class T, class Alloc = std::allocator<ft::pair<const Key,T> >>
	struct node
	{
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef Alloc											pair_allocator_type;
		typedef std::allocator<ft::node<const Key, T>			node_allocator_type;

		pair_allocator_type		palloc;
		node_allocator_type		nalloc;
		ft::pair<const Key, T>	data;
		node					*left;
		node					*right;
		node					*parent;
		std::bool				color;

		node() : left(NULL), right(NULL), parent(NULL), color(true) { data = palloc.allocator(1); }

		node(node *parent) : data(NULL), left(NULL), right(NULL), parent(parent) { data = palloc.allocator(1); }

		node(T val, node *parent) : data(val), left(NULL), right(NULL), parent(parent)
		{
			data = palloc.allocator(1);
			data.second = val;
		}

		~node() {}
	};

	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >, class Node_alloc = std::allocator<ft::node<const Key, T> >, class Node = ft::node<const Key, T>>
	class rb_tree
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef Node											node_type;
			typedef Node_alloc										node_allocator_type;

			rb_tree()
			{
				_alloc.allocate()
			}
			~rb_tree();

		private:
			node_allocator_type		_nalloc;
			allocator_type			_alloc;
			node_type				*_root;
	};
	
}
