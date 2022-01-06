//
// Created by Simon Cros on 29/12/2021.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include "utility.hpp"
#include "node.hpp"

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

	private:
		allocator_type _alloc;
		size_type _size;
		value_compare _comp;
		pointer _root;

		// ========================
		// ========================
		// ========================

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

		void print_all(std::string str, pointer selected = nullptr) {
			static int first = 1;

			if (!first)
				std::cout << "\033[17A";
			if (str.empty())
				str = "                   ";
			std::cout << str << std::endl;
			first = 0;
			print_t(_root, selected);
			char ch;
			scanf("%c",&ch);
		}

		// ========================
		// ========================
		// ========================

		void __rotate_left(pointer x) {
			pointer y = x->right;
			x->right = y->left;
			if (y->left)
				y->left->parent = x;
			y->parent = x->parent;
			if (!x->parent)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
			print_all("", x);
		}

		void __rotate_right(pointer x) {
			pointer y = x->left;
			x->left = y->right;
			if (y->right)
				y->right->parent = x;
			y->parent = x->parent;
			if (!x->parent)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
			print_all("", x);
		}

		pointer __search(const value_type& v, pointer pos) const {
			if (!pos)
				return nullptr;
			else if (_comp(v, pos->value))
				return __search(v, pos->left);
			else if (_comp(pos->value, v))
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
			} else if (_comp(n->value, pos->value))
				return __insert_r(n, pos->left, pos);
			else if (_comp(pos->value, n->value))
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
			else if (parent->left != n)
				return parent->left;
			else
				return parent->right;
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
			insert_line(n);
		}

		bool __is_red(pointer n) {
			return n && n->color == RED;
		}

		void __repair(pointer n) {
			if (!n)
				return;
			pointer p = __parent(n);
			if (!p) {
				n->color = BLACK;
			} else if (p->color == RED) {
				pointer g = __grand_parent(n);
				if (g) {
					pointer u = __uncle(n);
					if (__is_red(u)) {
						g->color = RED;
						p->color = BLACK;
						u->color = BLACK;
						__repair(g);
					} else {
						insert_triangle(n);
					}
				}
			}
		}

		void __copy(pointer n, pointer& to, pointer parent) {
			if (!n)
				return;
			to = _alloc.allocate(1);
			_alloc.construct(to, *n);
			to->parent = parent;
			__copy(n->left, to->left, to);
			__copy(n->right, to->right, to);
		}

		void __delete_node(pointer n) {
			_alloc.destroy(n);
			_alloc.deallocate(n, sizeof(value_type));
		}

		pointer *__get_parent_ptr(pointer n) {
			if (__is_left_child(n))
				return &__parent(n)->left;
			return __parent(n) ? &__parent(n)->right : &_root;
		}

		void __soft_delete_node(pointer n) {
			if (!n)
				return;
			*__get_parent_ptr(n) = nullptr;
			--_size;
			__delete_node(n);
		}
		
		bool __is_left_child(pointer n) {
			pointer p = __parent(n);
			return p && p->left == n;
		}

		void __copy_node(pointer src, pointer dst) {
			*__get_parent_ptr(dst) = src;
			dst->parent = src->parent;
			dst->color = src->color;
			dst->left = src->left;
			dst->right = src->right;
		}

		void __clear(pointer from) {
			if (!from)
				return;
			__clear(from->left);
			__clear(from->right);
			__delete_node(from);
		}

	public:
		tree(value_compare comp, allocator_type alloc = allocator_type()) : _alloc(alloc), _size(0), _comp(comp), _root(nullptr) {}

		tree(const tree& src) : _alloc(src._alloc), _size(0), _comp(src._comp), _root(nullptr) {
			this->operator=(src);
		}

		tree& operator=(const tree& rhs) {
			clear();
			_size = rhs._size;
			_comp = rhs._comp;
			__copy(rhs._root, _root, nullptr);
			return *this;
		}

		~tree() {
			clear();
		}

		void erase(iterator pos) {
			pointer n = pos.base();
			pointer v;
			if (!n)
				return;
			print_all("", n);
			if (!n->left && !n->right) { // good ?
				v = n;
			} else if (!n->right) {
				v = n->left;
				print_all("0", v);
				__copy_node(v, n);
			} else if (!n->left) {
				v = n->right;
				__copy_node(v, n);
			} else {
				v = (++pos).base();
				__copy_node(v, n);
			}
			print_all("1", v);

			pointer u = v->left ? v->left : v->right;
			if (__is_red(v) || __is_red(u)) {
				v->color = BLACK;
				print_all("2", v);
			} else {
				while (1) {
					pointer s = __brother(u);
					print_all("3 (u)", u);
					print_all("3 (s)", s);
					if (u == _root) {
						u->color = BLACK;
						break;
					} else if (!__is_red(s) && (__is_red(s->left) || __is_red(s->right))) {
						pointer p = __parent(s);
						print_all("2.2", u);
						if (__is_left_child(s)) {
							if (!__is_red(s->left))
								__rotate_right(s);
							__rotate_left(p);
						} else {
							if (!__is_red(s->right))
								__rotate_left(s);
							__rotate_right(p);
						}
						break;
					} else if (!__is_red(s)) {
						s->color = RED;
						u = __parent(s);
						print_all("", u);
						if (__is_red(u)) {
							u->color = BLACK;
							break;
						}
					} else {
						print_all("", u);
						if (__is_left_child(s))
							__rotate_right(__parent(s));
						else
							__rotate_left(__parent(s));
						s = __brother(u);
						if (__is_left_child(s))
							__rotate_right(__parent(s));
						else
							__rotate_left(__parent(s));
						break;
					}
				}
			}
			__soft_delete_node(n);
			print_all("");
		}

		iterator lower_bound(const value_type& val) {
			iterator it = begin();
			while (it != end() && _comp(it->value, val) == true)
				it++;
			return it;
		}

		iterator upper_bound(const value_type& val) {
			iterator it = begin();
			while (it != end() && _comp(val, it->value) == false)
				it++;
			return it;
		}

		ft::pair<iterator,iterator> equal_range(const value_type& val) {
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}

		ft::pair<iterator, bool> insert(const value_type &val) {
			pointer *tmp;
			pointer n = _alloc.allocate(1);
			_alloc.construct(n, val);

			tmp = __insert_r(n, _root, nullptr);
			if (tmp) {
				__delete_node(n);
				return ft::make_pair(iterator(*tmp, this), false);
			}

			__repair(n);
			_size++;
			return ft::make_pair(iterator(n, this), true);
		}

		iterator insert(iterator position, const value_type& val) {
			pointer tmp_node = position.base();
			if (!tmp_node || _comp(val, tmp_node->value))
				return insert(val).first;
			pointer *tmp;
			pointer n = _alloc.allocate(1);
			_alloc.construct(n, val);

			tmp = __insert_r(n, tmp_node, tmp_node->parent);
			if (tmp) {
				__delete_node(n);
				return iterator(*tmp, this);
			}

			__repair(n);
			_size++;
			return iterator(n, this);
		}

		void clear() {
			__clear(_root);
			_root = nullptr;
			_size = 0;
		}

		pointer left() const {
			pointer tmp = _root; 
			if (!tmp)
				return nullptr;

			while (tmp->left)
				tmp = tmp->left;
			return tmp;
		}

		pointer right() const {
			pointer tmp = _root; 
			if (!tmp)
				return nullptr;

			while (tmp->right)
				tmp = tmp->right;
			return tmp;
		}

		iterator find(const value_type& v) {
			return iterator(__search(v, _root), this);
		}

		const_iterator find(const value_type& v) const {
			return const_iterator(__search(v, _root), this);
		}

		bool empty() const								{ return !_root; }
		size_type size() const							{ return _size; }
		size_type max_size() const						{ return std::min<size_type>(std::numeric_limits<size_type>::max() / sizeof(node<value_type>), std::numeric_limits<difference_type>::max()); }

		iterator begin()								{ return iterator(left(), this); }
		const_iterator begin() const					{ return const_iterator(left(), this); }
		iterator end()									{ return iterator(nullptr, this); }
		const_iterator end() const						{ return const_iterator(nullptr, this); }
	};
}

#endif //FT_CONTAINERS_TREE_HPP
