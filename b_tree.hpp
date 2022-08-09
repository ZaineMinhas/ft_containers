/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_tree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 01:08:39 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/09 17:33:21 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_TREE_HPP
# define B_TREE_HPP

# include <iostream>
# include <iterator>
# include <memory>
# include <deque>

template<typename T>
struct node
{
	T		data;
	node	*left;
	node	*right;
	node	*parent;

	node() : data(0), left(NULL), right(NULL), parent(NULL) {}
	node(node *parent) : data(NULL), left(NULL), right(NULL), parent(parent) {}
	node(T val, node *parent) : data(val), left(NULL), right(NULL), parent(parent) {}
	~node()
	{
		if (right)
			delete right;
		if (left)
			delete left;
	}
};

template<typename T>
struct tree
{
	tree() { n = new node<T>(); }
	tree(T val) { n = new node<T>(val, NULL); }
	~tree() { delete n; }

	node<T>	*n;

	void	insert(T val)
	{
		if (val < n->data)
		{
			if (!n->left)
				n->left = new node<T>(val, n);
			else
			{
				n = n->left;
				insert(val);
			}
		}
		else if (val > n->data)
		{
			if (!n->right)
				n->right = new node<T>(val, n);
			else
			{
				n = n->right;
				insert(val);
			}
		}
		go_root();
	}

	void	search(T val)
	{
		if (val < n->data)
		{
			if (!n->left)
			{
				std::cout << "c'est loose" << std::endl;
				return ;
			}
			std::cout << "left > ";
			n = n->left;
			search(val);
			return ;
		}
		if (val > n->data)
		{
			if (!n->right)
			{
				std::cout << "c'est loose" << std::endl;
				return ;
			}
			std::cout << "right > ";
			n = n->right;
			search(val);
			return ;
		}
		if (val == n->data)
			std::cout << "c'est win" << std::endl;
	}

	void	go_root()
	{
		while (n->parent)
			n = n->parent;
	}
};

#endif
