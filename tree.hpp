//
// Created by Simon Cros on 29/12/2021.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

// TODO tmp
#include <iostream>

namespace ft {
	template <class Value, class Compare>
	class Tree {
	public:
		typedef Value value_type;
		typedef Compare value_compare;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		enum color {
			RED,
			BLACK
		};

		struct node {
			node *parent;
			node *left;
			node *right;
			color color;
			value_type value;

			node(const value_type& val) : parent(nullptr), left(nullptr), right(nullptr), color(RED), value(val) {}
		};

	private:
		size_type __size;
		value_compare comp;
		node *__root;

		void __rotate_left(node *x) {
			node* y = x->right;
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

		void __rotate_right(node *x) {
			node* y = x->left;
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

		node *__search(const value_type& v, node *pos) {
			if (!pos)
				return nullptr;
			else if (comp(v, pos->value))
				return __search(v, pos->left);
			else if (comp(pos->value, v))
				return __search(v, pos->right);
			else
				return pos;
		}

		node **__insert_r(node *n, node **pos) {
			if (!*pos)
				*pos = n;
			else if (comp(n->value, (*pos)->value))
				__insert_r(n, &(*pos)->left);
			else if (comp((*pos)->value, n->value))
				__insert_r(n, &(*pos)->right);
			else
				return pos;
			return nullptr;
		}

		void __repair(node *n) {
			(void)n;
		}

	public:
		Tree(value_compare comp) : __size(0), comp(comp), __root(nullptr) {
			std::cout << "Initialize tree" << std::endl;
		}

		void insert(const value_type &val) {
			node *n = new node(val);
			__insert_r(n, &__root);
			__repair(n);
			__size++;
		}

		void print_r(const node *n) {
			if (!n)
				return ;
			print_r(n->left);
			std::cout << (n->color == BLACK ? "B" : "R") << " " << n <<" " << n->value.first << " = " << n->value.second << std::endl;
			print_r(n->right);
		}

		void print_all() {
			print_r(__root);
		}

		void test(const value_type &val) {
			node *n = __search(val, __root);

			if (n)
				std::cout << (n->color == BLACK ? "B" : "R");
			else
				std::cout << "B";
			std::cout << " " << n;
			if (n)
				std::cout << " " << n->value.first << " = " << n->value.second;
			std::cout << std::endl;
		}
	};
}

#endif //FT_CONTAINERS_TREE_HPP
