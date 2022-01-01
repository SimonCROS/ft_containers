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

			std::cout << "==============" << std::endl;

			// __tree.test(make_pair(1, mapped_type()));

			__tree.insert(make_pair(4, 2));
			__tree.insert(make_pair(8, 1));
			__tree.insert(make_pair(2, 4));
			__tree.insert(make_pair(1, 0));
			__tree.insert(make_pair(10, 5));
			__tree.insert(make_pair(9, 3));

			__tree.insert(make_pair(11, 3));
			__tree.insert(make_pair(12, 3));
			__tree.insert(make_pair(13, 3));
			__tree.insert(make_pair(14, 3));
			__tree.insert(make_pair(15, 3));
			__tree.insert(make_pair(16, 3));
			__tree.insert(make_pair(17, 3));
			__tree.insert(make_pair(18, 3));
			__tree.insert(make_pair(19, 3));
			__tree.insert(make_pair(20, 3));
			__tree.insert(make_pair(21, 3));
			__tree.insert(make_pair(22, 3));
			__tree.insert(make_pair(23, 3));

			// __tree.test(make_pair(8, mapped_type()));
			// __tree.test(make_pair(2, mapped_type()));
			// __tree.test(make_pair(5, mapped_type()));
			// __tree.test(make_pair(3, mapped_type()));
			// __tree.test(make_pair(1, mapped_type()));

			__tree.print_all();
		}

		// pair<iterator,bool> insert(const value_type& val) {
			
		// }

		// iterator insert(iterator position, const value_type& val) {

		// }

		// template <class InputIterator>
		// void insert(InputIterator first, InputIterator last) {

		// }

		// size_type size() const							{ return static_cast<size_type>(__end_ - __begin_); }
		size_type max_size() const						{ return _alloc.max_size(); }
		bool empty() const								{ return __tree.empty(); }

		// iterator begin()								{ return iterator(__begin_); }
		// const_iterator begin() const					{ return const_iterator(__begin_); }
		// iterator end()									{ return iterator(__end_); }
		// const_iterator end() const						{ return const_iterator(__end_); }
		// reverse_iterator rbegin()						{ return reverse_iterator(end()); }
		// const_reverse_iterator rbegin() const			{ return const_reverse_iterator(end()); }
		// reverse_iterator rend()							{ return reverse_iterator(begin()); }
		// const_reverse_iterator rend() const				{ return const_reverse_iterator(begin()); }
	};
}

#endif //FT_CONTAINERS_MAP_HPP
