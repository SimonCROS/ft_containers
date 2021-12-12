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
        size_type _capacity;
        allocator_type _alloc;
        pointer __begin_;
        pointer __end_;

        void __construct_at_end(size_type n, const value_type &val) {
            for (int i = 0; i < n; ++i)
                _alloc.construct(__end_ + i, val);
        }

        void __destruct_at_end(size_type n) {
            for (int i = n; i > 0; i--)
                _alloc.destroy(__end_ - i);
        }

        void __realloc(size_type n) {
            size_type s = size();
            pointer tmp = _alloc.allocate(n);
            for (size_type i = 0; i < s && i < n; i++)
                _alloc.construct(tmp + i, __begin_[i]);
            __destruct_at_end(size());
            _alloc.deallocate(__begin_, _capacity);
            __begin_ = tmp;
            __end_ = __begin_ + s;
            _capacity = n;
        }

        void __append(size_type n, const value_type &val) {
            if (size() + n > _capacity)
                this->__realloc(size() + n);
            __construct_at_end(n, val);
            __end_ += n;
        }

        void __grow() {
            this->__realloc(std::max(1UL, _capacity * 2));
        }

        void __out_of_range() const {
            throw std::out_of_range("vector");
        }
    public:

        // default
        explicit vector(const allocator_type &alloc = allocator_type()) : __begin_(NULL), __end_(NULL), _capacity(0), _alloc(alloc) {
        }

        // fill
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()): _capacity(n), _alloc(alloc) {
            this->__begin_ = _alloc.allocate(n);
            this->__end_ = this->__begin_ + n;
            this->__construct_at_end(size(), val);
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
            clear();
            _alloc.deallocate(__begin_, _capacity);
        }

        void resize(size_type __sz, value_type val = value_type()) {
            size_type __cs = size();
            if (__cs < __sz)
                this->__append(__sz - __cs, val);
            else if (__cs > __sz)
            {
                this->__destruct_at_end(__cs - __sz);
                __end_ -= __cs - __sz;
            }
        }

        void reserve(size_type n) {
            if (n > _capacity)
                this->__realloc(n);
        }

        void push_back(const value_type &value)
        {
            if (size() >= _capacity)
                this->__grow();
            this->__construct_at_end(1, value);
            this->__end_++;
        }

        size_type size() const {
            return static_cast<size_type>(this->__end_ - this->__begin_);
        }

        size_type maxsize() const {
            return _alloc.maxsize();
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

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {

        }

        void assign(size_type n, const value_type &val) {

        }

        void clear() {
            this->__destruct_at_end(this->size());
            this->__end_ = this->__begin_;
        }

        bool empty() const                              { return this->size() == 0; }
        iterator begin()                                { return iterator(__begin_); }
        const_iterator begin() const                    { return const_iterator(__begin_); }
        iterator end()                                  { return iterator(__end_); }
        const_iterator end() const                      { return const_iterator(__end_); }
        reverse_iterator rbegin()                       { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const           { return const_reverse_iterator(end()); }
        reverse_iterator rend()                         { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const             { return const_reverse_iterator(begin()); }
        reference front()                               { return *this->__begin_; }
        const_reference front() const                   { return *this->__begin_; }
        reference back()                                { return *(this->__end_ - 1); }
        const_reference back() const                    { return *(this->__end_ - 1); }
        reference operator[](size_type n)               { return this->__begin_[n]; }
        const_reference operator[](size_type n) const   { return this->__begin_[n]; }
        reference at(size_type n)                       { if (n >= this->size()) this->__out_of_range(); return this->__begin_[n]; }
        const_reference at(size_type n) const           { if (n >= this->size()) this->__out_of_range(); return this->__begin_[n]; }
    };
}

#endif //FT_CONTAINERS_VECTOR_HPP
