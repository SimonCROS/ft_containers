//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <functional>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "tree.hpp"

namespace ft {
    template <class Value, class Iterator>
    class __map_iterator {
    private:
        Iterator current;
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<Value>::value_type value_type;
        typedef typename iterator_traits<Value>::pointer pointer;
        typedef typename iterator_traits<Value>::reference reference;
        typedef bidirectional_iterator_tag iterator_category;

        __map_iterator() {}

        __map_iterator(iterator_type __x) : current(__x) {}

        template <class _Value, class _Iterator>
        __map_iterator(const __map_iterator<_Value, _Iterator>& __x) : current(__x.base()) {}

        virtual ~__map_iterator() {}

        __map_iterator& operator=(const __map_iterator& rhs) {
            this->current = rhs.current;
            return *this;
        }

        reference operator*() const { return current->value; }

        pointer operator->() const { return &current->value; }

        __map_iterator& operator++() {
            ++current;
            return *this;
        }

        __map_iterator operator++(int) {
            __map_iterator __tmp(*this);
            this->operator++();
            return __tmp;
        }

        __map_iterator& operator--() {
			--current;
            return *this;
        }

        __map_iterator operator--(int) {
            __map_iterator __tmp(*this);
            this->operator--();
            return __tmp;
        }

        iterator_type base() const { return current; }
    };

    template <class Value, class Iterator>
    bool operator== (const ft::__map_iterator<Value, Iterator>& lhs, const ft::__map_iterator<Value, Iterator>& rhs) { return lhs.base() == rhs.base(); }
    template <class Value, class Iterator>
    bool operator!= (const ft::__map_iterator<Value, Iterator>& lhs, const ft::__map_iterator<Value, Iterator>& rhs) { return lhs.base() != rhs.base(); }

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Alloc allocator_type;
		typedef Compare key_compare;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

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
		typedef typename ft::tree<value_type, value_compare> tree_type;
	
	public:
		typedef typename ft::__map_iterator<pointer, typename tree_type::iterator> iterator;
		typedef typename ft::__map_iterator<const_pointer, typename tree_type::const_iterator> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename tree_type::difference_type difference_type;
		typedef typename tree_type::size_type size_type;

	private:
		allocator_type _alloc;
		tree_type _tree;

	public:
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _tree(value_compare(comp), alloc) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _tree(value_compare(comp), alloc) {
			insert(first, last);
		}

		map(const map& x) : _alloc(x._alloc), _tree(x._tree) {}

		map& operator=(const map& x) {
			this->_tree = x._tree;
			return *this;
		}

		~map() {}

		void clear() {
			_tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type& val) {
			ft::pair<typename tree_type::iterator, bool> tmp = _tree.insert(val);
			return ft::make_pair(iterator(tmp.first), tmp.second);
		}

		iterator insert(iterator position, const value_type& val) {
			return iterator(_tree.insert(position.base(), val));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			typename tree_type::iterator prev = _tree.end();

			while (first != last)
				prev = _tree.insert(prev, *first++);
		}

		void erase(iterator position) {
			(void)position;
		}

		size_type erase(const key_type& k) {
			iterator it = find(k);
			if (it == end())
				return 0;
			erase();
			return 1;
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		key_compare key_comp() const {
			return key_compare();
		}

		key_compare value_comp() const {
			return value_compare(key_comp());
		}

		iterator find(const key_type& k) {
			return iterator(_tree.find(ft::make_pair(k, mapped_type())));
		}

		const_iterator find(const key_type& k) const {
			return const_iterator(_tree.find(ft::make_pair(k, mapped_type())));
		}

		mapped_type& operator[](const key_type& k) {
			ft::pair<iterator, bool> it = insert(ft::make_pair(k, mapped_type()));
			return it.first->second;
		}

		size_type count(const key_type& k) const {
			return find(k) != end();
		}

		void swap(map& x) {
			std::swap(this->_tree, x._tree);
			std::swap(this->_alloc, x._alloc);
		}

		bool empty() const									{ return _tree.empty(); }
		size_type size() const								{ return _tree.size(); }
		// size_type max_size() const							{ return _alloc.max_size(); }

		iterator upper_bound(const key_type& k)				{ return iterator(_tree.upper_bound()); }
		const_iterator upper_bound(const key_type& k) const	{ return const_iterator(_tree.upper_bound()); }

		iterator lower_bound(const key_type& k)				{ return iterator(_tree.lower_bound()); }
		const_iterator lower_bound(const key_type& k) const	{ return const_iterator(_tree.lower_bound()); }

		iterator begin()									{ return iterator(_tree.begin()); }
		const_iterator begin() const						{ return const_iterator(_tree.begin()); }
		iterator end()										{ return iterator(_tree.end()); }
		const_iterator end() const							{ return const_iterator(_tree.end()); }
		reverse_iterator rbegin()							{ return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const				{ return const_reverse_iterator(end()); }
		reverse_iterator rend()								{ return reverse_iterator(begin()); }
		const_reverse_iterator rend() const					{ return const_reverse_iterator(begin()); }

		allocator_type get_allocator() const				{ return _alloc; };
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		x.swap(y);
	}
}

#endif //FT_CONTAINERS_MAP_HPP
