/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 04:57:54 by zminhas           #+#    #+#             */
/*   Updated: 2022/08/25 16:56:23 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "pair.hpp"
# include <iostream>
# include <iterator>
# include <memory>
# include <deque>

namespace ft
{
	/*----- Lexicographical compare -----*/

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	/*----- IS_INTEGRAL -----*/

	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator T() { return v; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template <class T> struct is_integral : public false_type {};

	template<> struct is_integral<bool> : public true_type{};

	template<> struct is_integral<char> : public true_type{};
	template<> struct is_integral<wchar_t> : public true_type{};
	template<> struct is_integral<signed char> : public true_type {};
	template<> struct is_integral<unsigned char> : public true_type{};

	template<> struct is_integral<short int> : public true_type{};
	template<> struct is_integral<int> : public true_type{};
	template<> struct is_integral<long int> : public true_type{};
	template<> struct is_integral<long long int> : public true_type{};
	template<> struct is_integral<unsigned short int> : public true_type{};
	template<> struct is_integral<unsigned int> : public true_type{};
	template<> struct is_integral<unsigned long int> : public true_type{};
	template<> struct is_integral<unsigned long long int> : public true_type{};

	/*----- ENABLE IF -----*/

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	/*---------- LESS ----------*/

	template <class T>
	struct less : std::binary_function <T, T, bool>
	{ bool	operator()(const T& x, const T& y) const { return (x < y); } };

}

#endif
