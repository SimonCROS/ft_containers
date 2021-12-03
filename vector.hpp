//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator.hpp"

#include "<algorithm>"

namespace ft {

    template<class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T value_type;
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
        value_type *_data;
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;

        void realloc(size_type n) {
            _capacity = n;
            _alloc.allocate();
        }
    public:

        // default
        explicit vector(const allocator_type &alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _alloc(alloc) { }

        // fill
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()): _size(n), _capacity(n), _alloc(alloc) {
            _data = _alloc.allocate(n);
            for (int i = 0; i < n; ++i)
            {
                static_cast< std::allocator<T> >(_alloc).construct(n + i);
            }
        }

        // range
        template<class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()): _alloc(alloc) {

        }

        // copy
        // TODO copy constructor
        vector(const vector &x) {

        }

        ~vector() {

        }

        void reserve(size_type n) {
            if (n >= _capacity)
                realloc(n);
        }

        void push_back(const T &value)
        {
            if (_size >= _capacity)
                reserve(std::max(1, _capacity * 2));
            _data[_size] = value;
            _size++;
        }

        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        size_type capacity() const {
            return _capacity;
        }

        vector &operator=(const vector &other) {
            return *this;
        }

        void push_back(const value_type &val) {
        }

        iterator begin()                        { return iterator(_data); }
        const_iterator begin() const            { return const_iterator(_data); }
        iterator end()                          { return iterator(_data + _size); }
        const_iterator end() const              { return const_iterator(_data + _size); }
        reverse_iterator rbegin()               { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const   { return const_reverse_iterator(end()); }
        reverse_iterator rend()                 { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const     { return const_reverse_iterator(begin()); }
    };
}

#endif //FT_CONTAINERS_VECTOR_HPP
