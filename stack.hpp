//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

	template <class T, class Container = vector<T> >
	class stack {
		template <class T, class Alloc>
		friend bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
		
	protected:
		container_type c;

	public:
		explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {}

		bool empty() const					{ return c.empty(); }
		size_type size() const				{ return c.size(); }
		value_type& top()					{ return c.back(); }
		const value_type& top() const		{ return c.back(); }
		void push(const value_type& val)	{ c.push_back(val); }
		void pop()							{ c.pop_back(); }
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return lhs.c == rhs.c; }
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return lhs.c != rhs.c; }
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return lhs.c <  rhs.c; }
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return lhs.c <= rhs.c; }
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return lhs.c >  rhs.c; }
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return lhs.c >= rhs.c; }
}

#endif //FT_CONTAINERS_STACK_HPP
