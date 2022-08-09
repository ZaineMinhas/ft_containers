/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:40:10 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/09 17:47:20 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_tree.hpp"

int	main()
{
	tree<int>	t(10);

	// std::cout << t.n->data << std::endl;

	t.insert(8);
	t.insert(9);
	t.insert(1000);
	t.insert(1002);
	t.insert(11);
	t.insert(-2);
	t.insert(1001);

	t.search(1001);
	//std::cout << t.n->parent << std::endl;
	//std::cout << t.n->right->data << std::endl;

	return (0);
}
