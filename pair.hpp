/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:50:50 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/31 18:21:24 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include "utils.hpp"

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1			first_type;
		typedef T2			second_type;

		first_type		first;
		second_type		second;

		/*----- Constructors -----*/

		pair() : first(first_type()), second(second_type()) {}
		template<class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		/*----- Assignation operator -----*/

		pair	&operator=(const pair &pr)
		{
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};

	/*---------- Non member functions ----------*/

	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }
	
	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (!(lhs < rhs)); }

	/*---------- Make pair ----------*/

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) { return (pair<T1, T2>(x, y)); }

}

#endif
