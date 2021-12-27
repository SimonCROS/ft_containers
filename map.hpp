//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map {
    public:
		typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const key_type, mapped_type> value_type;
        typedef Allocator allocator_type;
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
    private:
    public:
	};
}

#endif //FT_CONTAINERS_MAP_HPP
