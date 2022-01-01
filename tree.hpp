//
// Created by Simon Cros on 29/12/1021.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

// TODO tmp
#include <iostream>
#include <unistd.h>

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

		int _print_t(node *tree, int is_left, int offset, int depth, char s[15][255], const node *selected)
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

		void print_t(node *tree, const node *selected) {
			char s[15][255];
			for (int i = 0; i < 15; i++)
				sprintf(s[i], "%150s", " ");

			_print_t(tree, 0, 0, 0, s, selected);

			for (int i = 0; i < 15; i++)
				printf("%s\n", s[i]);
		}

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

		node **__insert_r(node *n, node *&pos, node *parent) {
			if (!pos)
			{
				n->parent = parent;
				pos = n;
			}
			else if (comp(n->value, pos->value))
				__insert_r(n, pos->left, pos);
			else if (comp(pos->value, n->value))
				__insert_r(n, pos->right, pos);
			else
				return &pos;
			return nullptr;
		}

		node *__parent(node *n) {
			if (!n)
				return nullptr;
			return n->parent;
		}

		node *__grand_parent(node *n) {
			node *parent = __parent(n);
			if (!parent)
				return nullptr;
			return parent->parent;
		}

		node *__brother(node *n) {
			node *parent = __parent(n);
			if (!parent)
				return nullptr;
			else if (parent->left == n)
				return parent->right;
			else
				return parent->left;
		}

		node *__uncle(node *n) {
			return __brother(__parent(n));
		}

		void insert_line(node *n) {
			node *p = __parent(n);
			node *g = __grand_parent(n);

			if (n == p->left)
				__rotate_right(g);
			else
				__rotate_left(g);

			p->color = BLACK;
			g->color = RED;

			print_all(n);
		}

		void insert_triangle(node *n) {
			node *p = __parent(n);
			node *g = __grand_parent(n);

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

		void __repair(node *n) {
			if (!n)
				return;
			print_all(n);
			node *p = __parent(n);
			if (!p) {
				n->color = BLACK;
				print_all(n);
			}
			else if (p->color == RED) {
				node *g = __grand_parent(n);
				if (g) {
					node *u = __uncle(n);
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
		Tree(value_compare comp) : __size(0), comp(comp), __root(nullptr) {
			std::cout << "Initialize tree" << std::endl;
		}

		void insert(const value_type &val) {
			node *n = new node(val);
			__insert_r(n, __root, __root);
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

		void print_all(node *selected = nullptr) {
			static int first = 1;

			if (!first)
				std::cout << "\033[16A";
			first = 0;
			print_t(__root, selected);
			// usleep(1.0 * 1000 * 1000);
			char ch;
			scanf("%c",&ch);
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

		bool empty() {
			return !__root;
		}
	};
}

#endif //FT_CONTAINERS_TREE_HPP
