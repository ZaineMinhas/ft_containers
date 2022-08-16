/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbt_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:39:12 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/16 14:58:48 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.hpp"
# include "pair.hpp"
# define BLACK true
# define RED false

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
			: _cmp(tree.get_cmp()), _root(tree.get_root()), _leaf(tree.get_leaf()), _alloc(tree.get_alloc()), _nalloc(tree.get_nalloc()) {}

			/*-------------------------- Destructor ---------------------------*/

			~rb_tree() {}			//a faire

			/*--------------------------- Getters -----------------------------*/

			key_compare				get_cmp(void) const { return (_cmp); }
			node_type				*get_root(void) const { return (_root); }
			node_type				*get_leaf(void) const { return (_leaf); }
			allocator_type			*get_alloc(void) const { return (_alloc); }
			node_allocator_type		*get_nalloc(void) const { return (_nalloc); }

			/*-------------------------- Iterators ----------------------------*/

			// a faire

			/*-------------------------- Modifiers ----------------------------*/

			node_type	*new_node(value_type val, bool color, node_type *parent)
			{
				node_type	*node;

				node = _nalloc.allocate(1);
				_alloc.construct(&node->data, val);
				node->parent = parent;
				node->color = color;
				node->left = _leaf;
				node->right = _leaf;
				return (node);
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

			void	switch_color(node_type *node)
			{
				if (!node)
					return ;
				if (node->color == BLACK)
					node->color = RED;
				else
					node->color = BLACK;
			}

			node_type	*balance(node_type *node)
			{
				if (node == _root || node->parent->color == BLACK)
					return (node);
				if (node->parent->color == BLACK)
					return (node);
				node_type	*uncle = get_uncle(node);
				if (uncle && uncle->color == RED)
				{
					switch_color(uncle);
					switch_color(node->parent);
					if (node->parent->parent != _root)
						switch_color(node->parent->parent);
					balance(node->parent->parent);
				}
				else
				{
					node_type	*parent = node->parent;
					node_type	*grandpa = parent->parent;
					if (!joestar_legacy(node, parent, grandpa))
					{
						if (parent->left == node)
							rot_right(node->parent);
						else
							rot_left(node->parent);
					}
					if (grandpa->left == parent || grandpa->left == node)
					{
						switch_color(grandpa);
						switch_color(grandpa->left);
						rot_right(grandpa);
					}
					else
					{
						switch_color(grandpa);
						switch_color(grandpa->right);
						rot_left(grandpa);
					}
				}
				return (node);
			}

			node_type	*insert(value_type val)
			{
				node_type	*finded = to_find(val.first);

				if (_root == _leaf)
					_root = new_node(val, BLACK, NULL);
				else if (_cmp(val.first, finded->data.first))
				{
					finded->left = new_node(val, RED, finded);
					return (balance(finded->left));
				}
				else if (_cmp(finded->data.first, val.first))
				{
					finded->right = new_node(val, RED, finded);
					return (balance(finded->right));
				}
				return (finded);
			}

			/*---------------------------- Utils -----------------------------*/

			node_type	*to_find(const key_type &val) const
			{
				node_type	*to_find = _root;

				while (to_find != _leaf)
				{
					if (_cmp(val, to_find->data.first))
					{
						if (to_find->left != _leaf)
							to_find = to_find->left;
						else
							return (to_find);
					}
					else if (_cmp(to_find->data.first, val))
					{
						if (to_find->right != _leaf)
							to_find = to_find->right;
						else
							return (to_find);
					}
					else
						return (to_find);
				}
				return (to_find);
			}

			node_type	*get_uncle(node_type *node) const
			{
				if (node == _root || node->parent == _root || node == NULL || node == _leaf)
					return (NULL);
				if (node->parent == node->parent->parent->left)
					return (node->parent->parent->right);
				else
					return (node->parent->parent->left);
			}

			bool	joestar_legacy(node_type *Jotaro, node_type *Joseph, node_type *Jonathan) const
			{
				if ((Jonathan->left == Joseph && Joseph->left == Jotaro) || (Jonathan->right == Joseph && Joseph->right == Jotaro))
					return (true);
				return (false);
			}

			void	aff_node(Node *node) const
			{
				std::string	color;
				node->color ? color = "black" : color = "red";
				std::cout << node->data.first << " | " << node->data.second << " | " << color << std::endl;
			}

			void	aff_tree(Node *node, int space) const
			{
				int i;
				if(node != _leaf)
				{
					space = space + 10;
					aff_tree(node->right, space);
					std::cout << std::endl;
					for (i = 10; i < space; i++)
						std::cout << " ";
					aff_node(node);
					std::cout << std::endl;
					aff_tree(node->left, space);
				}
			}

		private:
			node_type				*_root;
			node_type				*_leaf;
			key_compare				_cmp;
			allocator_type			_alloc;
			node_allocator_type		_nalloc;
	};
	
}
