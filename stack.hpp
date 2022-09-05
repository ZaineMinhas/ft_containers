/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:09:36 by zminhas           #+#    #+#             */
/*   Updated: 2022/09/05 16:34:19 by zminhas          ###   ########.fr       */
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

			stack(const container_type &ctnr = container_type()) : c(ctnr) {}

			/*--------------------------- Function ----------------------------*/

			bool	empty() const { return (c.empty()); }

			size_type	size() const { return (c.size()); }

			value_type&	top() { return (c.back()); }
			const value_type&	top() const { return (c.back()); }

			void	push(const value_type& val) { c.push_back(val); }

			void	pop() { c.pop_back(); }

		protected:
			container_type	c;

		private:
			template <class Type, class Cont>
			friend bool	operator==(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);

			template <class Type, class Cont>
			friend bool	operator!=(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);

			template <class Type, class Cont>
			friend bool	operator<(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);

			template <class Type, class Cont>
			friend bool	operator<=(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);

			template <class Type, class Cont>
			friend bool	operator>(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);

			template <class Type, class Cont>
			friend bool	operator>=(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);
	};

	/*--------------------- NON MEMBER FONCTION -----------------------*/
	/*--------------------- relational operators ----------------------*/

	template <class T, class Container>
	bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c == rhs.c); }

	template <class T, class Container>
	bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c != rhs.c); }

	template <class T, class Container>
	bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c < rhs.c); }

	template <class T, class Container>
	bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c <= rhs.c); }

	template <class T, class Container>
	bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c > rhs.c); }

	template <class T, class Container>
	bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c >= rhs.c); }
}

#endif
