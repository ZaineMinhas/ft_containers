/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 00:05:49 by zminhas           #+#    #+#             */
/*   Updated: 2022/09/05 00:38:13 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>
#define NAMESPACE ft

int	main(void)
{

	ft::stack<int, ft::vector<int> > stack_1, stack_2;

	for (size_t i = 0; i < 10; i++)
	{
		stack_1.push(i);	// PUSH
		stack_2.push(i * 10);	// PUSH
	}

	stack_2.pop();	// POP

	std::cout << "---------------------------" << std::endl;

	std::cout << "SIZE OF STACK_1 : " << stack_1.size() << std::endl;	// SIZE
	std::cout << "SIZE OF STACK_2 : " << stack_1.size() << std::endl;	// SIZE

	std::cout << "---------------------------" << std::endl;

	std::cout << "RELATIONAL OPERATOR :" << std::endl;
	std::cout << "STACK_1 VS STACK_2" << std::endl;
	std::cout << "== : " << (stack_1 == stack_2) << " | != : " << (stack_1 != stack_2) << std::endl;	// RELATIONAL OPERATOR
	std::cout << " < : " << (stack_1 < stack_2) << " | >  : " << (stack_1 > stack_2) << std::endl;	// RELATIONAL OPERATOR
	std::cout << "<= : " << (stack_1 <= stack_2) << " | >= : " << (stack_1 >= stack_2) << std::endl;	// RELATIONAL OPERATOR

	std::cout << "---------------------------" << std::endl;

	std::cout << "STACK_1 = ";
	while (!(stack_1.empty()))	// EMPTY
	{
		std::cout << "[" << stack_1.top() << "] ";	// TOP
		stack_1.pop();
	}
	std::cout << std::endl;

	std::cout << "STACK_2 = ";
	while (!(stack_2.empty()))	// EMPTY
	{
		std::cout << "[" << stack_2.top() << "] ";	// TOP
		stack_2.pop();
	}
	std::cout << std::endl;

	return (0);
}
