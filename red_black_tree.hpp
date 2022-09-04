/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:39:12 by zminhas           #+#    #+#             */
/*   Updated: 2022/09/05 00:03:37 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "iterator.hpp"
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
		bool					double_black;
	};

	/*----- RED BLACK TREE STRUCT -----*/

	template <class Key, class T>
	class rb_tree
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const Key, T>							value_type;
			typedef ft::less<Key>									key_compare;
			typedef std::allocator<ft::pair<const Key, T> >			allocator_type;
			typedef std::allocator<ft::node<Key, T> >				node_allocator_type;
			typedef ft::node<Key, T>								node_type;

			/*-------------------------- Constructor --------------------------*/

			rb_tree(const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type(), const node_allocator_type &nalloc = node_allocator_type())
			: _leaf(NULL), _cmp(cmp), _alloc(alloc), _nalloc(nalloc), _size(0)
			{
				_leaf = new_node(ft::make_pair(_size, T()), BLACK, NULL);
				_root = _leaf;
			}

			/*-------------------------- Destructor ---------------------------*/

			~rb_tree(void)
			{
				destroyer(_root);
				destroy_node(_leaf);
			}

			/*--------------------------- Getters -----------------------------*/

			size_t					get_size(void) const { return (_size); }
			key_compare				get_cmp(void) const { return (_cmp); }
			node_type				*get_root(void) const { return (_root); }
			node_type				*get_leaf(void) const { return (_leaf); }
			allocator_type			get_alloc(void) const { return (_alloc); }
			node_allocator_type		get_nalloc(void) const { return (_nalloc); }

			/*-------------------------- Insert ----------------------------*/

			node_type	*insert(value_type val)
			{
				node_type	*finded = to_find(val.first);

				if (finded != _leaf && finded->data.first == val.first)
				{
					finded->double_black = true;
					return (finded);
				}
				_size++;
				update_leaf();
				if (_root == _leaf)
				{
					_root = new_node(val, BLACK, NULL);
					return (_root);
				}
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

			/*-------------------------- Delete ----------------------------*/

			bool	del_node(key_type val)
			{
				node_type	*to_del = to_find(val);
				if (to_del->data.first != val)
					return (false);
				_size--;
				update_leaf();
				if (to_del->left == _leaf && to_del->right == _leaf)
				{
					if (to_del->color == RED || to_del == _root)
						destroy_node(to_del);
					else
					{
						node_type	*db = new_node(value_type(), BLACK, to_del->parent);
						db->double_black = true;
						bool	l_or_r = to_del == to_del->parent->left ? true : false;
						destroy_node(to_del);
						l_or_r ? db->parent->left = db : db->parent->right = db;
						del_balance(db);
					}
				}
				else
				{
					node_type	*tmp = to_del->left != _leaf ? maximum(to_del->left) : minimum(to_del->right);
					if (tmp->left != _leaf || tmp->right != _leaf)
					{
						if (tmp->left != _leaf)
						{
							switch_color(tmp->left);
							tmp->left->parent = tmp->parent;
							tmp == tmp->parent->left ? tmp->parent->left = tmp->left : tmp->parent->right = tmp->left;
						}
						else
						{
							switch_color(tmp->right);
							tmp->right->parent = tmp->parent;
							tmp == tmp->parent->left ? tmp->parent->left = tmp->right : tmp->parent->right = tmp->right;
						}
						copy_node(to_del, tmp);
					}
					else
					{
						if (tmp->color == RED)
						{
							tmp == tmp->parent->left ? tmp->parent->left = _leaf : tmp->parent->right = _leaf;
							copy_node(to_del, tmp);
						}
						else
						{
							node_type	*db = new_node(value_type(), BLACK, tmp->parent);
							db->double_black = true;
							tmp == tmp->parent->left ? tmp->parent->left = db : tmp->parent->right = db;
							copy_node(to_del, tmp);
							del_balance(db);
						}
					}
				}
				return (true);
			}

			/*-------------------------- Utils ----------------------------*/

			void	aff_node(node_type *node) const
			{
				if (!node)
				{
					std::cout << "(null)" <<std::endl;
					return ;
				}
				std::string	color;
				node->color ? color = "black" : color = "red";
				std::cout << node->data.first << " | " << node->data.second << " | " << color << std::endl;
			}

			void	aff_tree(void) const
			{
				std::cout << "----------------------------------------------------" << std::endl;
				get_aff_tree(_root, 0);
				std::cout << "----------------------------------------------------" << std::endl;
			}

			node_type	*minimum(node_type* x) const
			{
				while (x != _leaf && x->left != _leaf)
					x = x->left;
				return (x);
			}

			node_type	*maximum(node_type* x) const
			{
				while (x != _leaf &&x->right != _leaf)
					x = x->right;
				return (x);
			}

			node_type	*to_find(const key_type &val) const
			{
				node_type	*to_find = _root;

				while (to_find != _leaf)
				{
					if (_cmp(val, to_find->data.first))
					{
						if (to_find->left == _leaf)
							return (to_find);
						to_find = to_find->left;
					}
					else if (_cmp(to_find->data.first, val))
					{
						if (to_find->right == _leaf)
							return (to_find);
						to_find = to_find->right;
					}
					else
						return (to_find);
				}
				return (to_find);
			}

			void	swap(rb_tree &tree)
			{
				node_type	*tmp_r = _root;
				node_type	*tmp_l = _leaf;
				size_t		tmp_s = _size;

				_root = tree.get_root();
				_leaf = tree.get_leaf();
				_size = tree.get_size();

				tree._root = tmp_r;
				tree._leaf = tmp_l;
				tree._size = tmp_s;
			}

			void	destroyer(node_type *to_del)
			{
				if (to_del != _leaf)
				{
					destroyer(to_del->left);
					destroyer(to_del->right);
					_alloc.destroy(&to_del->data);
					_nalloc.deallocate(to_del, 1);
					if (to_del == _root)
						_root = _leaf;
					to_del = _leaf;
				}
				_size = 0;
				update_leaf();
			}

		private:
			node_type				*_root;
			node_type				*_leaf;
			key_compare				_cmp;
			allocator_type			_alloc;
			node_allocator_type		_nalloc;
			size_t					_size;

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
				node->double_black = false;
				return (node);
			}

			void	destroy_node(node_type *node)
			{
				if (node == _root)
					_root = _leaf;
				else
				{
					if (node->parent != _leaf && node == node->parent->left)
						node->parent->left = _leaf;
					else if (node->parent != _leaf && node == node->parent->right)
						node->parent->right = _leaf;
				}
				_alloc.destroy(&node->data);
				_nalloc.deallocate(node, 1);
			}

			void	rot_left(node_type *node)
			{
				node_type	*tmp_a = node;
				node_type	*tmp_b = node->right->left;

				node = node->right;
				node->left = tmp_a;
				tmp_a->right = tmp_b;
				node->parent = tmp_a->parent;
				if (tmp_b)
					tmp_b->parent = tmp_a;
				if (node->parent)
				{
					if (tmp_a == tmp_a->parent->right)
						node->parent->right = node;
					else
						node->parent->left = node;
				}
				else
					_root = node;
				tmp_a->parent = node;
			}

			void	rot_right(node_type *node)
			{
				node_type	*tmp_a = node;
				node_type	*tmp_b = node->left->right;

				node = node->left;
				node->right = tmp_a;
				tmp_a->left = tmp_b;
				node->parent = tmp_a->parent;
				if (tmp_b)
					tmp_b->parent = tmp_a;
				if (node->parent)
				{
					if (tmp_a == tmp_a->parent->right)
						node->parent->right = node;
					else
						node->parent->left = node;
				}
				else
					_root = node;
				tmp_a->parent = node;
			}

			void	switch_color(node_type *node)
			{
				if (!node || node == _leaf)
					return ;
				if (node->color == BLACK)
					node->color = RED;
				else
					node->color = BLACK;
			}

			void	update_leaf(void)
			{
				_alloc.destroy(&_leaf->data);
				_alloc.construct(&_leaf->data, ft::make_pair(_size, T()));
			}

			/*--------------------------- Balance ----------------------------*/

			node_type	*balance(node_type *node)
			{
				if (node == _root || node->parent->color == BLACK)
					return (node);
				node_type	*uncle = get_uncle(node);
				if (uncle != _leaf && uncle->color == RED)
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

			void	del_balance(node_type *db)
			{
				if (db == _root)
				{
					db->color = BLACK;
					return ;
				}
				node_type	*sibling = get_sibling(db);
				if (sibling->color == RED)
				{
					sibling->color = db->parent->color;
					db->parent->color = RED;
					db == db->parent->left ? rot_left(db->parent) : rot_right(db->parent);
					del_balance(db);
				}
				else
				{
					node_type	*far_schild = get_far_schild(db);
					if (far_schild != _leaf && far_schild->color == RED)
					{
						sibling->color = db->parent->color;
						db->parent->color = BLACK;
						db == db->parent->left ? rot_left(db->parent) : rot_right(db->parent);
						if (db->double_black)
							destroy_node(db);
						far_schild->color = BLACK;
					}
					else
					{
						node_type	*near_schild = get_near_schild(db);
						if (near_schild != _leaf && near_schild->color == RED)
						{
							near_schild->color = sibling->color;
							sibling->color = RED;
							db == db->parent->left ? rot_right(sibling) : rot_left(sibling);
							del_balance(db);
						}
						else
						{
							if (db->double_black)
								destroy_node(db);
							sibling->color = RED;
							if (db->parent->color == BLACK)
								del_balance(db->parent);
							else
								db->parent->color = BLACK;
						}
					}
				}
			}

			/*---------------------------- Utils -----------------------------*/

			node_type	*get_uncle(node_type *node) const
			{
				if (node == _root || node->parent == _root || node == _leaf)
					return (_leaf);
				if (node->parent == node->parent->parent->left)
					return (node->parent->parent->right);
				else
					return (node->parent->parent->left);
			}

			node_type	*get_sibling(node_type *node) const
			{
				if (node == node->parent->right)
					return (node->parent->left);
				return (node->parent->right);
			}

			node_type	*get_far_schild(node_type *node) const
			{
				if (node == node->parent->right)
					return (node->parent->left->left);
				return (node->parent->right->right);
			}

			node_type	*get_near_schild(node_type *node) const
			{
				if (node == node->parent->right)
					return (node->parent->left->right);
				return (node->parent->right->left);
			}

			void	copy_node(node_type *a, node_type *b)
			{
				if (a != _root)
					a == a->parent->left ? a->parent->left = b : a->parent->right = b;
				else
					_root = b;
				b->parent = a->parent;
				b->left = a->left;
				b->right = a->right;
				if (b->left != _leaf)
					b->left->parent = b;
				if (b->right != _leaf)
					b->right->parent = b;
				b->color = a->color;
				_alloc.destroy(&a->data);
				_nalloc.deallocate(a, 1);
				a = _leaf;
			}

			bool	joestar_legacy(node_type *Jotaro, node_type *Joseph, node_type *Jonathan) const
			{
				if ((Jonathan->left == Joseph && Joseph->left == Jotaro) || (Jonathan->right == Joseph && Joseph->right == Jotaro))
					return (true);
				return (false);
			}

			void	get_aff_tree(node_type *node, int space) const
			{
				int	i;
				if(node != _leaf)
				{
					space += 10;
					get_aff_tree(node->right, space);
					std::cout << std::endl;
					for (i = 10; i < space; i++)
						std::cout << " ";
					aff_node(node);
					std::cout << std::endl;
					get_aff_tree(node->left, space);
				}
			}
	};
}

#endif
