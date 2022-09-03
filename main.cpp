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
#include <map>
#define NAMESPACE ft

int	main(void)
{
	std::cout << "DEFAULT CONSTRUCTOR :" << std::endl;	// DEFAULT CONSTRUCTOR
	NAMESPACE::map<int, char> map;
	std::cout << "EMPTY : " << map.empty() << std::endl;	// EMPTY
	std::cout << "SIZE : " << map.size() << std::endl;	// SIZE
	std::cout << "MAX SIZE : " << map.max_size() << std::endl;	// MAX_SIZE

	std::cout << "-----------------------------------------------------------" << std::endl;

	std::cout << "INSERT :" << std::endl;
	for (size_t i = 0; i < 10; i++)
		map.insert(NAMESPACE::make_pair(i, 'A' + i));		// INSERT

	std::cout << "EMPTY : " << map.empty() << std::endl;
	std::cout << "SIZE : " << map.size() << std::endl;
	std::cout << "MAX SIZE : " << map.max_size() << std::endl;

	NAMESPACE::map<int, char>::iterator	it(map.begin());	// ITERATOR
	NAMESPACE::map<int, char>::iterator	ite(map.end());

	for (; it != ite; it++)
		std::cout << "[" << it->first << "|" << it->second << "] ";	// PAIR
	std::cout << std::endl;

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// COPY CONSTRUCT
		std::cout << "COPY CONSTRUCT :" << std::endl;
		NAMESPACE::map<int, char> map2(map);	// COPY CONSTRUCT
		std::cout << "EMPTY : " << map2.empty() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;
		std::cout << "MAX SIZE : " << map2.max_size() << std::endl;

		NAMESPACE::map<int, char>::reverse_iterator	it2(map2.rbegin());	// REVERSE ITERATOR
		NAMESPACE::map<int, char>::reverse_iterator	ite2(map2.rend());

		std::cout << "SALUT " << it2->second << std::endl;
		std::cout << "PRINT WITH REVERSE ITERATOR :" << std::endl;
		for (; it2 != ite2; it2++)
			std::cout << "[" << it2->first << "|" << it2->second << "] ";
		std::cout << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// ITERATOR RANGE CONSTRUCTOR
		std::cout << "ITERATOR RANGE CONSTRUCTOR :" << std::endl;
		NAMESPACE::map<int, char> map2(map.begin(), map.end());	// ITERATOR RANGE CONSTRUCTOR
		std::cout << "EMPTY : " << map2.empty() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;
		std::cout << "MAX SIZE : " << map2.max_size() << std::endl;

		NAMESPACE::map<int, char>::iterator	it2(map2.begin());
		NAMESPACE::map<int, char>::iterator	ite2(map2.end());

		for (; it2 != ite2; it2++)
			std::cout << "[" << it2->first << "|" << it2->second << "] ";
		std::cout << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// OPERATOR =
		std::cout << "ASSIGNEMENT OPERATOR :" << std::endl;
		NAMESPACE::map<int, char> map2 = map;	// ASSIGNEMENT OPERATOR
		std::cout << "EMPTY : " << map2.empty() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;
		std::cout << "MAX SIZE : " << map2.max_size() << std::endl;

		NAMESPACE::map<int, char>::iterator	it2(map.begin());
		NAMESPACE::map<int, char>::iterator	ite2(map.end());

		for (; it2 != ite2; it2++)
			std::cout << "[" << it2->first << "|" << it2->second << "] ";
		std::cout << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// OPERATOR []
		NAMESPACE::map<int, char> map2;
		std::cout << "INSERT WITH OPERATOR [] :" << std::endl;
		for (size_t i = 0; i < 26; i++)
			map2[i] = 'A' + i;	// INSERT WITH OPERATOR []

		std::cout << "PRINT WITH OPERATOR [] :" << std::endl;
		for (size_t i = 0; i < 26; i++)
		{
			if (!(i % 9) && i)
				std::cout << std::endl;
			std::cout << "[" << i << "|" << map2[i] << "] ";	// PRINT WITH OPERATOR []
		}
		std::cout << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// ERASE
		NAMESPACE::map<int, char> map2(map);
		std::cout << "EMPTY : " << map2.empty() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;
		std::cout << "ERASE KEY 9 : " << map2.erase(9) << std::endl;	// ERASE INDEX
		std::cout << "ERASE KEY 9 : " << map2.erase(9) << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl << std::endl;

		std::cout << "ERASE WITH ITERATOR : " << std::endl;
		map2.erase(--(--map2.end()));	// ERASE ITERATOR
		std::cout << "SIZE : " << map2.size() << std::endl;

		std::cout << std::endl << "ERASE ALL WITH ITERATOR RANGE : " << std::endl;
		map2.erase(map2.begin(), map2.end());	// ERASE ITERATOR RANGE
		std::cout << "SIZE : " << map2.size() << std::endl;
		std::cout << "EMPTY : " << map2.empty() << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// CLEAR
		NAMESPACE::map<int, char> map2(map);
		std::cout << "EMPTY : " << map2.empty() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;
		std::cout << std::endl << "--- CLEAR ---" << std::endl << std::endl;
		map2.clear();	// CLEAR
		std::cout << "EMPTY : " << map2.empty() << std::endl;
		std::cout << "SIZE : " << map2.size() << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// SWAP
		NAMESPACE::map<int, char> map2;
		NAMESPACE::map<int, char> map3;

		for (size_t i = 0; i < 10; i++)
			map2[i] = 'A' + i;
		for (size_t i = 10; i < 15; i++)
			map3[i] = 'A' + i;

		std::cout << "MAP2 SIZE : " << map2.size() << std::endl;
		{
			NAMESPACE::map<int, char>::iterator	it2(map2.begin());
			NAMESPACE::map<int, char>::iterator	ite2(map2.end());
			for (; it2 != ite2; it2++)
				std::cout << "[" << it2->first << "|" << it2->second << "] ";
			std::cout << std::endl;
		}

		std::cout << "MAP3 SIZE : " << map3.size() << std::endl;
		{
			NAMESPACE::map<int, char>::iterator	it3(map3.begin());
			NAMESPACE::map<int, char>::iterator	ite3(map3.end());
			for (; it3 != ite3; it3++)
				std::cout << "[" << it3->first << "|" << it3->second << "] ";
			std::cout << std::endl;
		}

		std::cout << std::endl << "--- SWAP ---" << std::endl << std::endl;
		map2.swap(map3);	// SWAP

		std::cout << "MAP2 SIZE : " << map2.size() << std::endl;
		{
			NAMESPACE::map<int, char>::iterator	it2(map2.begin());
			NAMESPACE::map<int, char>::iterator	ite2(map2.end());
			for (; it2 != ite2; it2++)
				std::cout << "[" << it2->first << "|" << it2->second << "] ";
			std::cout << std::endl;
		}

		std::cout << "MAP3 SIZE : " << map3.size() << std::endl;
		{
			NAMESPACE::map<int, char>::iterator	it3(map3.begin());
			NAMESPACE::map<int, char>::iterator	ite3(map3.end());
			for (; it3 != ite3; it3++)
				std::cout << "[" << it3->first << "|" << it3->second << "] ";
			std::cout << std::endl;
		}
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// COUNT
		NAMESPACE::map<int, char> map2;
		for (size_t i = 0; i < 10; i++)
			map2[i * 10] = 'A' + i;

		std::cout << "SIZE : " << map2.size() << std::endl;
		NAMESPACE::map<int, char>::iterator	it2(map2.begin());
		NAMESPACE::map<int, char>::iterator	ite2(map2.end());
		for (; it2 != ite2; it2++)
			std::cout << "[" << it2->first << "|" << it2->second << "] ";
		std::cout << std::endl;
		std::cout << "IS INDEX 99 EXISTING : " << map2.count(99) << std::endl;	// COUNT
		std::cout << "IS INDEX 80 EXISTING : " << map2.count(80) << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// FIND
		NAMESPACE::map<int, char> map2(map);
		std::cout << "SIZE : " << map2.size() << std::endl;
		NAMESPACE::map<int, char>::iterator	it2(map2.begin());
		NAMESPACE::map<int, char>::iterator	ite2(map2.end());
		for (; it2 != ite2; it2++)
			std::cout << "[" << it2->first << "|" << it2->second << "] ";
		std::cout << std::endl;

		NAMESPACE::map<int, char>::iterator	find1(map2.find(8));
		NAMESPACE::map<int, char>::iterator	find2(map2.find(80));
		std::cout << "DID WE FOUND 8 : ";
		std::cout << "[" << find1->first << "|" << find1->second << "]" << std::endl;
		std::cout << "DID WE FOUND 80 : ";
		// std::cout << "[" << find2->first << "|" << find2->second << "] " << std::endl;;
		// map2.erase(map2.find(80));
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// LOWER_BOUND
		NAMESPACE::map<int, char> map2(map);
		NAMESPACE::map<int, char>::iterator	lb1(map2.lower_bound(-5));	// LOWER_BOUND
		std::cout << "LOWER BOUND OF -5 : ";
		std::cout << "[" << lb1->first << "|" << lb1->second << "]" << std::endl;

		NAMESPACE::map<int, char>::iterator	lb2(map2.lower_bound(5));	// LOWER_BOUND
		std::cout << "LOWER BOUND OF 5 : ";
		std::cout << "[" << lb2->first << "|" << lb2->second << "]" << std::endl;

		NAMESPACE::map<int, char>::iterator	lb3(map2.lower_bound(15));	// LOWER_BOUND
		std::cout << "LOWER BOUND OF 15 : ";
		// std::cout << "[" << lb3->first << "|" << lb3->second << "]" << std::endl;
	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	{	// UPPER_BOUND
		NAMESPACE::map<int, char> map2(map);
		NAMESPACE::map<int, char>::iterator	lb1(map2.upper_bound(-5));	// UPPER_BOUND
		std::cout << "UPPER BOUND OF -5 : ";
		std::cout << "[" << lb1->first << "|" << lb1->second << "]" << std::endl;

		NAMESPACE::map<int, char>::iterator	lb2(map2.upper_bound(5));	// UPPER_BOUND
		std::cout << "UPPER BOUND OF 5 : ";
		std::cout << "[" << lb2->first << "|" << lb2->second << "]" << std::endl;

		NAMESPACE::map<int, char>::iterator	lb3(map2.upper_bound(15));	// UPPER_BOUND
		std::cout << "UPPER BOUND OF 15 : ";
		// std::cout << "[" << lb3->first << "|" << lb3->second << "]" << std::endl;
	}

	return (0);
}

// clear && c++ main.cpp && ./a.out
