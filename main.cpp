/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:01:41 by zminhas           #+#    #+#             */
/*   Updated: 2022/09/02 19:01:41 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

int	main(void)
{
	ft::map<int, char> map;

	std::cout << "INSERT :" << std::endl;
	std::cout << "MAX SIZE : " << map.max_size() << std::endl;	// MAX_SIZE
	std::cout << "SIZE : " << map.size() << std::endl;	// SIZE
	for (size_t i = 0; i < 10; i++)
		map.insert(ft::make_pair(i, 'A' + i));		// INSERT

	ft::map<int, char>::iterator	it(map.begin());	// ITERATOR
	ft::map<int, char>::iterator	ite(map.end());

	for (; it != ite; it++)
		std::cout << "[" << it->first << "|" << it->second << "] ";	// PAIR
	std::cout << std::endl;
	std::cout << "SIZE : " << map.size() << std::endl;

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// COPY CONSTRUCT
		ft::map<int, char> map2(map);

		std::cout << "COPY CONSTRUCT :" << std::endl;
		std::cout << "MAX SIZE : " << map2.max_size() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;

		ft::map<int, char>::reverse_iterator	it2(map2.rbegin());	// REVERSE ITERATOR
		ft::map<int, char>::reverse_iterator	ite2(map2.rend());

		std::cout << "PRINT WITH REVERSE ITERATOR :" << std::endl;
		for (; it2 != ite2; it2++)
			std::cout << "[" << it2->first << "|" << it2->second << "] ";
		std::cout << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// ASSIGNEMENT OPERATOR
		ft::map<int, char> map2 = map;

		std::cout << "ASSIGNEMENT OPERATOR :" << std::endl;
		std::cout << "MAX SIZE : " << map2.max_size() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;

		ft::map<int, char>::iterator	it2(map.begin());
		ft::map<int, char>::iterator	ite2(map.end());

		for (; it2 != ite2; it2++)
			std::cout << "[" << it2->first << "|" << it2->second << "] ";
		std::cout << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	return (0);
}

// clear && c++ main.cpp && ./a.out
