//
// Created by Simon Cros on 29/12/2021.
//

#ifndef FT_CONTAINERS_NODE_HPP
#define FT_CONTAINERS_NODE_HPP

namespace ft {
	enum node_color {
		RED,
		BLACK
	};

	template <class Value>
	struct node {
		typedef Value value_type;

		node *parent;
		node *left;
		node *right;
		node_color color;
		value_type value;

		node(const value_type& val = value_type()) : parent(nullptr), left(nullptr), right(nullptr), color(RED), value(val) {}
	};
}

#endif //FT_CONTAINERS_NODE_HPP
