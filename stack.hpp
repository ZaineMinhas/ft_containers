/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:09:36 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/04 20:47:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "utils.hpp"
# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T					value_type;
			typedef Container			container_type;
			typedef std::ptrdiff_t		size_type;

			/*-------------------------- Constructor --------------------------*/

			stack(const container_type &ctnr = container_type()) : _container(ctnr) {}

			bool	empty() const { return (_container.empty()); }

			size_type	size() const { return (_container.size()); }

			value_type&	top() { return (_container.back()); }
			const value_type&	top() const { return (_container.back()); }

			void	push(const value_type& val) { _container.push_back(val); }

			void	pop() { _container.pop_back(); }

			/*-------------------------- Getter --------------------------*/

			container_type	getContainer(void) const { return (_container); }


		private:
			container_type	_container;
	};

	/*--------------------- NON MEMBER FONCTION -----------------------*/
	/*--------------------- relational operators ----------------------*/

	template <class T, class Container>
  	bool	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.getContainer() == rhs.getContainer()); }

	template <class T, class Container>
	bool	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.getContainer() != rhs.getContainer()); }

	template <class T, class Container>
	bool	operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.getContainer() < rhs.getContainer()); }

	template <class T, class Container>
	bool	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.getContainer() <= rhs.getContainer()); }

	template <class T, class Container>
	bool	operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.getContainer() > rhs.getContainer()); }

	template <class T, class Container>
	bool	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.getContainer() >= rhs.getContainer()); }
}

#endif
