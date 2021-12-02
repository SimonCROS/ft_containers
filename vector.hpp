//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator.hpp"

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
        value_type *array;
        size_type _size;
        size_type _capacity;
        allocator_type allocator;
    public:

        explicit vector(const allocator_type &alloc = allocator_type()) : array(nullptr), _size(0), _capacity(0), allocator(alloc) { }

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()): allocator(alloc) {

        }

        template<class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()): allocator(alloc) {

        }

        // TODO copy constructor
        vector(const vector &x) {

        }

        ~vector() {

        }

        vector &operator=(const vector &other) {
            return *this;
        }

        void push_back(const value_type &val) {
        }

        iterator begin()                { return iterator(this->array); }
        iterator begin() const          { return iterator(this->array); }
        iterator end()                  { return iterator(this->array + this->_size); }
        iterator end() const            { return iterator(this->array + this->_size); }
        reverse_iterator rbegin()       { return reverse_iterator(end()); }
        reverse_iterator rbegin() const { return reverse_iterator(end()); }
        reverse_iterator rend()         { return reverse_iterator(begin()); }
        reverse_iterator rend() const   { return reverse_iterator(begin()); }
    };
}

#endif //FT_CONTAINERS_VECTOR_HPP
