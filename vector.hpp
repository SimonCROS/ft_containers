//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator.hpp"
#include <stdexcept>

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

        void __construct_at_end(size_type n, const value_type &val) {
            for (int i = 0; i < n; ++i)
                _alloc.construct(_data + _size + i, val);
            _size += n;
        }

        void __destruct_at_end(size_type n) {
            for (int i = 0; i < n; ++i)
                _alloc.destroy(_data + _size - i);
            _size -= n;
        }

        void __realloc(size_type n) {
            pointer tmp = _alloc.allocate(n);
            for (size_type i = 0; i < _size && i < n; i++)
                tmp[i] = _data[i];
            _alloc.deallocate(_data, _capacity);
            _data = tmp;
            _capacity = n;
        }

        void __append(size_type n, const value_type &val) {
            if (_size + n > _capacity)
                this->__realloc(_size + n);
            __construct_at_end(n, val);
        }

        void __grow() {
            this->__realloc(std::max(1UL, _capacity * 2));
        }

        void __out_of_range() const {
            throw std::out_of_range("vector");
        }
    public:

        // default
        explicit vector(const allocator_type &alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _alloc(alloc) { }

        // fill
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()): _size(0), _capacity(n), _alloc(alloc) {
            _data = _alloc.allocate(n);
            this->__construct_at_end(n, val);
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
            this->__destruct_at_end(_size);
            _alloc.deallocate(_data, _capacity);
        }

        void resize(size_type __sz, value_type val = value_type()) {
            size_type __cs = size();
            if (__cs < __sz)
                this->__append(__sz - __cs, val);
            else if (__cs > __sz)
                this->__destruct_at_end(__cs - __sz);
        }

        void reserve(size_type n) {
            if (n > _capacity)
                this->__realloc(n);
        }

        void push_back(const value_type &value)
        {
            if (_size >= _capacity)
                this->__grow();
            _alloc.construct(_data + _size, value);
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

        allocator_type get_allocator() const {
            return this->_alloc;
        }

        vector &operator=(const vector &other) {
            return *this;
        }

        bool empty() const                              { return this->_size == 0; }
        iterator begin()                                { return iterator(_data); }
        const_iterator begin() const                    { return const_iterator(_data); }
        iterator end()                                  { return iterator(_data + _size); }
        const_iterator end() const                      { return const_iterator(_data + _size); }
        reverse_iterator rbegin()                       { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const           { return const_reverse_iterator(end()); }
        reverse_iterator rend()                         { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const             { return const_reverse_iterator(begin()); }
        reference front()                               { return *this->_data; }
        const_reference front() const                   { return *this->_data; }
        reference back()                                { return this->_data[_size - 1]; }
        const_reference back() const                    { return this->_data[_size - 1]; }
        reference operator[](size_type n)               { return this->_data[n]; }
        const_reference operator[](size_type n) const   { return this->_data[n]; }
        reference at(size_type n)                       { if (n >= this->_size) this->__out_of_range(); return this->_data[n]; }
        const_reference at(size_type n) const           { if (n >= this->_size) this->__out_of_range(); return this->_data[n]; }
    };
}

#endif //FT_CONTAINERS_VECTOR_HPP
