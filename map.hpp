//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <functional>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "tree.hpp"

namespace ft {
	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair();

		template <class U, class V>
		pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs < lhs); }
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs < lhs; }
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs < rhs); }

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Alloc allocator_type;
		typedef Compare key_compare;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::__normal_iterator<pointer> iterator;
		typedef typename ft::__normal_iterator<const_pointer> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			protected:
				key_compare comp;
			public:
				value_compare(key_compare c) : comp(c) {}
				bool operator() (const value_type& x, const value_type& y) const {
					return comp(x.first, y.first);
				}
		};

	private:
		Tree<value_type, value_compare> __tree;

	public:
		map() : __tree(value_compare(key_compare())) {
			std::cout << "Initialize map" << std::endl;

			__tree.test(make_pair(1, mapped_type()));

			__tree.insert(make_pair(1, 0));
			__tree.insert(make_pair(8, 1));
			__tree.insert(make_pair(4, 2));
			__tree.insert(make_pair(9, 3));
			__tree.insert(make_pair(2, 4));

			__tree.test(make_pair(8, mapped_type()));
			__tree.test(make_pair(2, mapped_type()));
			__tree.test(make_pair(5, mapped_type()));
			__tree.test(make_pair(3, mapped_type()));
			__tree.test(make_pair(1, mapped_type()));

			std::cout << "==============" << std::endl;

			__tree.print_all();
		}
	};
}

#endif //FT_CONTAINERS_MAP_HPP
