/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbt_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:39:12 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/12 19:51:20 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.hpp"
# include "pair.hpp"
# define RED false
# define BLACK true

namespace ft
{
	/*----- NODE STRUCT -----*/

	template<class Key, class T>
	struct node
	{
		ft::pair<const Key, T>	data;
		node					*left;
		node					*right;
		node					*parent;
		bool					color;
	};

	/*----- RED BLACK TREE STRUCT -----*/

	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >, class Node_alloc = std::allocator<ft::node<const Key, T> >, class Node = ft::node<const Key, T> >
	class rb_tree
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const Key, T>							value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef Node_alloc										node_allocator_type;
			typedef Node											node_type;

			/*-------------------------- Constructor --------------------------*/

			rb_tree(const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type(), const node_allocator_type &nalloc = node_allocator_type())
			: _cmp(cmp), _alloc(alloc), _nalloc(nalloc)
			{
				_root = _nalloc.allocate(1);
				_alloc.construct(&_root->data, value_type());
				_root->parent = NULL;
				_root->left = NULL;
				_root->right = NULL;
				_root->color = BLACK;
				_leaf = _root;
			}

			rb_tree(const rb_tree &tree)
			: _cmp(tree.get_cmp()), _root(tree.get_root()), _alloc(tree.get_alloc()), _nalloc(tree.get_nalloc()) {}

			/*-------------------------- Destructor ---------------------------*/

			~rb_tree() {}			//a faire

			/*--------------------------- Getters -----------------------------*/

			key_compare				get_cmp(void) const { return (_cmp); }
			node_type				*get_root(void) const { return (_root); }
			allocator_type			*get_alloc(void) const { return (_alloc); }
			node_allocator_type		*get_nalloc(void) const { return (_nalloc); }

			/*-------------------------- Iterators ----------------------------*/

			// a faire

			/*-------------------------- Modifiers ----------------------------*/

			void	balance(void) {}

			void	insert(value_type val)
			{
				node_type	*finded = to_find(val.first);

				if (_root == _leaf)
					_root = new_node(val, BLACK, NULL);
				else if (_cmp(val.first, finded->data.first))
					finded->left = new_node(val, RED, finded);
				else
					finded->right = new_node(val, RED, finded);
				balance();
			}

			/*---------------------------- Utils -----------------------------*/

			node_type	*new_node(value_type val, bool color, node_type *parent)
			{
				node_type	*node;

				node = _nalloc.allocate(1);
				_alloc.construct(&node->data, val);
				node->parent = parent;
				node->color = color;
				node->left = NULL;
				node->right = NULL;
				return (node);
			}

			node_type	*to_find(const key_type &val) const
			{
				node_type	*to_find = _root;

				// std::cout << to_find << std::endl;
				// std::cout << val << " < " << to_find->data.first << " ?" << std::endl;
				// std::cout << "plus petit : ";
				// if (_cmp(val, to_find->data.first))
				// 	std::cout << "OUI" << std::endl;
				// else
				// 	std::cout << "NON" << std::endl;


				while (to_find)
				{
					if (_cmp(val, to_find->data.first))
					{
						if (to_find->left)
						{
							to_find = to_find->left;
							continue;
						}
						else
							return (to_find);
					}
					else
					{
						if (to_find->right)
						{
							to_find = to_find->right;
							continue;
						}
						else
							return (to_find);
					}
				}
				return (to_find);
			}

			void	rot_left(node_type *node)
			{
				node_type	*tmp_a = node;
				node_type	*tmp_b = node->right->left;

				node = node->right;
				node->left = tmp_a;
				tmp_a->right = tmp_b;
				node->parent = tmp_a->parent;
				tmp_a->parent = node;
				if (tmp_b)
					tmp_b->parent = tmp_a;
				if (node->parent && node->parent->left == tmp_a)
					node->parent->left = node;
				else if (node->parent && node->parent->right == tmp_a)
					node->parent->right = node;
			}

			void	rot_right(node_type *node)
			{
				node_type	*tmp_a = node;
				node_type	*tmp_b = node->left->right;

				node = node->left;
				node->right = tmp_a;
				tmp_a->left = tmp_b;
				node->parent = tmp_a->parent;
				tmp_a->parent = node;
				if (tmp_b)
					tmp_b->parent = tmp_a;
				if (node->parent && node->parent->left == tmp_a)
					node->parent->left = node;
				else if (node->parent && node->parent->right == tmp_a)
					node->parent->right = node;
			}

		private:
			node_type				*_root;
			node_type				*_leaf;
			key_compare				_cmp;
			allocator_type			_alloc;
			node_allocator_type		_nalloc;
	};
	
}
