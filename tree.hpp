//
// Created by Simon Cros on 29/12/2021.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include "utility.hpp"
#include "node.hpp"

// TODO tmp
#include <iostream>
#include <unistd.h>

namespace ft {
	template <class Node, class Tree>
    class __tree_iterator {
    public:
        typedef Node iterator_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::pointer pointer;
        typedef typename iterator_traits<iterator_type>::reference reference;
        typedef bidirectional_iterator_tag iterator_category;
    private:
        iterator_type current;
		Tree *__tree;
    public:

        __tree_iterator() {}

        __tree_iterator(pointer __x, Tree *__t) : current(__x), __tree(__t) {}

        template <class _Node, class _Tree>
        __tree_iterator(const __tree_iterator<_Node, _Tree>& __x) : current(__x.base()), __tree(__x.tree()) {}

        virtual ~__tree_iterator() {}

        __tree_iterator& operator=(const __tree_iterator& rhs) {
			this->__tree = rhs.__tree;
            this->current = rhs.current;
            return *this;
        }

        reference operator*() const { return *current; }

        pointer operator->() const { return current; }

        __tree_iterator& operator++() {
            if (current->right) {
				current = current->right;
				while (current->left)
					current = current->left;
			} else {
				while (current->parent && current->parent->right == current)
					current = current->parent;
				current = current->parent;
			}
            return *this;
        }

        __tree_iterator operator++(int) {
            __tree_iterator __tmp(*this);
            this->operator++();
            return __tmp;
        }

        __tree_iterator& operator--() {
			if (!current)
				current = __tree->right();
            else if (current->left) {
				current = current->left;
				while (current->right)
					current = current->right;
			} else {
				while (current->parent && current->parent->left == current)
					current = current->parent;
				current = current->parent;
			}
            return *this;
        }

        __tree_iterator operator--(int) {
            __tree_iterator __tmp(*this);
            this->operator--();
            return __tmp;
        }

        iterator_type base() const { return current; }
		Tree *tree() const { return __tree; }
    };

    template <class _Node, class _Tree>
    bool operator== (const ft::__tree_iterator<_Node, _Tree>& lhs, const ft::__tree_iterator<_Node, _Tree>& rhs) { return lhs.base() == rhs.base(); }
    template <class _Node, class _Tree>
    bool operator!= (const ft::__tree_iterator<_Node, _Tree>& lhs, const ft::__tree_iterator<_Node, _Tree>& rhs) { return lhs.base() != rhs.base(); }

	template <class Value, class Compare, class Alloc = std::allocator<ft::node<Value> > >
	class tree {
	public:
		typedef Value value_type;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::__tree_iterator<pointer, ft::tree<value_type, value_compare> > iterator;
		typedef typename ft::__tree_iterator<const_pointer, const ft::tree<value_type, value_compare> > const_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		int _print_t(pointer tree, int is_left, int offset, int depth, char s[15][255], const_pointer selected)
		{
			char b[20];
			int real_width = 13;
			int width = 4;

			if (!tree) return 0;

			if (tree == selected && tree->color == RED)
				sprintf(b, "*\033[31m%03d\033[0m", tree->value.first);
			else if (tree == selected)
				sprintf(b, "*\033[37m%03d\033[0m", tree->value.first);
			else if (tree->color == RED)
				sprintf(b, " \033[31m%03d\033[0m", tree->value.first);
			else
				sprintf(b, " \033[37m%03d\033[0m", tree->value.first);

			int left  = _print_t(tree->left,  1, offset,                depth + 1, s, selected);
			int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s, selected);

		#ifdef COMPACT
			for (int i = 0; i < width; i++)
				s[depth][offset + left + i] = b[i];

			if (depth && is_left) {

				for (int i = 0; i < width + right; i++)
					s[depth - 1][offset + left + width/2 + i] = '-';

				s[depth - 1][offset + left + width/2] = '.';

			} else if (depth && !is_left) {

				for (int i = 0; i < left + width; i++)
					s[depth - 1][offset - width/2 + i] = '-';

				s[depth - 1][offset + left + width/2] = '.';
			}
		#else
			std::string l = std::string(s[2 * depth]);
			int n = std::count(l.begin(), l.end(), '\033');
			for (int i = 0; i < real_width; i++)
			{
				s[2 * depth][offset + left + (n / 2 * 7) + n + i] = b[i];
			}

			if (depth && is_left) {

				for (int i = 0; i < width + right; i++)
					s[2 * depth - 1][offset + left + width/2 + i] = '-';

				s[2 * depth - 1][offset + left + width/2] = '+';
				s[2 * depth - 1][offset + left + width + right + width/2] = '+';

			} else if (depth && !is_left) {

				for (int i = 0; i < left + width; i++)
					s[2 * depth - 1][offset - width/2 + i] = '-';

				s[2 * depth - 1][offset + left + width/2] = '+';
				s[2 * depth - 1][offset - width/2 - 1] = '+';
			}
		#endif

			return left + width + right;
		}

		void print_t(pointer tree, const_pointer selected) {
			char s[15][255];
			for (int i = 0; i < 15; i++)
				sprintf(s[i], "%150s", " ");

			_print_t(tree, 0, 0, 0, s, selected);

			for (int i = 0; i < 15; i++)
				printf("%s\n", s[i]);
		}

	private:
		allocator_type _alloc;
		size_type __size;
		value_compare comp;
		pointer __root;

		void __rotate_left(pointer x) {
			pointer y = x->right;
			x->right = y->left;
			if (y->left)
				y->left->parent = x;
			y->parent = x->parent;
			if (!x->parent)
				__root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void __rotate_right(pointer x) {
			pointer y = x->left;
			x->left = y->right;
			if (y->right)
				y->right->parent = x;
			y->parent = x->parent;
			if (!x->parent)
				__root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		pointer __search(const value_type& v, pointer pos) const {
			if (!pos)
				return nullptr;
			else if (comp(v, pos->value))
				return __search(v, pos->left);
			else if (comp(pos->value, v))
				return __search(v, pos->right);
			else
				return pos;
		}

		pointer *__insert_r(pointer n, pointer &pos, pointer parent) {
			if (!pos)
			{
				n->parent = parent;
				pos = n;
				return nullptr;
			} else if (comp(n->value, pos->value))
				return __insert_r(n, pos->left, pos);
			else if (comp(pos->value, n->value))
				return __insert_r(n, pos->right, pos);
			else
				return &pos;
		}

		pointer __parent(pointer n) {
			if (!n)
				return nullptr;
			return n->parent;
		}

		pointer __grand_parent(pointer n) {
			pointer parent = __parent(n);
			if (!parent)
				return nullptr;
			return parent->parent;
		}

		pointer __brother(pointer n) {
			pointer parent = __parent(n);
			if (!parent)
				return nullptr;
			else if (parent->left == n)
				return parent->right;
			else
				return parent->left;
		}

		pointer __uncle(pointer n) {
			return __brother(__parent(n));
		}

		void insert_line(pointer n) {
			pointer p = __parent(n);
			pointer g = __grand_parent(n);

			if (n == p->left)
				__rotate_right(g);
			else
				__rotate_left(g);

			p->color = BLACK;
			g->color = RED;

			print_all(n);
		}

		void insert_triangle(pointer n) {
			pointer p = __parent(n);
			pointer g = __grand_parent(n);

			if (g->left && n == g->left->right) {
				__rotate_left(p);
				n = n->left;
			} else if (g->right && n == g->right->left) {
				__rotate_right(p);
				n = n->right;
			}

			print_all(n);

			insert_line(n);
		}

		void __repair(pointer n) {
			if (!n)
				return;
			print_all(n);
			pointer p = __parent(n);
			if (!p) {
				n->color = BLACK;
				print_all(n);
			}
			else if (p->color == RED) {
				pointer g = __grand_parent(n);
				if (g) {
					pointer u = __uncle(n);
					if (u && u->color == RED) {
						g->color = RED;
						p->color = BLACK;
						u->color = BLACK;
						__repair(g);
					} else {
						insert_triangle(n);
					}
					print_all(n);
				}
			}
		}

	public:
		tree(value_compare comp, allocator_type alloc = allocator_type()) : _alloc(alloc), __size(0), comp(comp), __root(nullptr) {}

		pair<iterator, bool> insert(const value_type &val) {
			pointer *tmp;
			pointer n = _alloc.allocate(1);
			_alloc.construct(n, val);

			tmp = __insert_r(n, __root, nullptr);
			if (tmp)
				return ft::make_pair(iterator(*tmp, this), false);

			__repair(n);
			__size++;
			return ft::make_pair(iterator(n, this), true);
		}

		iterator insert(iterator position, const value_type& val) {
			pointer tmp_node = position.base();
			if (!tmp_node || comp(val, tmp_node->value))
				return insert(val).first;
			pointer *tmp;
			pointer n = _alloc.allocate(1);
			_alloc.construct(n, val);

			tmp = __insert_r(n, tmp_node, tmp_node->parent);
			if (tmp)
				return iterator(*tmp, this);

			__repair(n);
			__size++;
			return iterator(n, this);
		}

		void print_r(const_pointer n) {
			if (!n)
				return ;
			print_r(n->left);
			std::cout << (n->color == BLACK ? "B" : "R") << " " << n <<" " << n->value.first << " = " << n->value.second << std::endl;
			print_r(n->right);
		}

		void print_all(pointer selected = nullptr) {
			(void)selected;
			// static int first = 1;

			// if (!first)
			// 	std::cout << "\033[16A";
			// first = 0;
			// print_t(__root, selected);
			// char ch;
			// scanf("%c",&ch);
		}

		void test(const value_type &val) {
			pointer n = __search(val, __root);

			if (n)
				std::cout << (n->color == BLACK ? "B" : "R");
			else
				std::cout << "B";
			std::cout << " " << n;
			if (n)
				std::cout << " " << n->value.first << " = " << n->value.second;
			std::cout << std::endl;
		}

		pointer left() const {
			pointer tmp = __root; 
			if (!tmp)
				return nullptr;

			while (tmp->left)
				tmp = tmp->left;
			return tmp;
		}

		pointer right() const {
			pointer tmp = __root; 
			if (!tmp)
				return nullptr;

			while (tmp->right)
				tmp = tmp->right;
			return tmp;
		}

		iterator find(const value_type& v) {
			return iterator(__search(v, __root), this);
		}

		const_iterator find(const value_type& v) const {
			return const_iterator(__search(v, __root), this);
		}

		bool empty() const								{ return !__root; }
		size_type size() const							{ return __size; }

		iterator begin()								{ return iterator(left(), this); }
		const_iterator begin() const					{ return const_iterator(left(), this); }
		iterator end()									{ return iterator(nullptr, this); }
		const_iterator end() const						{ return const_iterator(nullptr, this); }
	};
}

#endif //FT_CONTAINERS_TREE_HPP
