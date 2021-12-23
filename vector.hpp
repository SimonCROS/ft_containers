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
            while (n--)
                _alloc.construct(__end_++, val);
        }

        void __destruct_at_end(pointer __new_end) {
            while (__end_ > __new_end)
                _alloc.destroy(--__end_);
        }

        void __realloc(size_type n) {
            size_type s = this->size();
            pointer tmp = _alloc.allocate(n);
            for (size_type i = 0; i < s && i < n; i++)
                _alloc.construct(tmp + i, __begin_[i]);
            this->clear();
            _alloc.deallocate(__begin_, _capacity);
            __begin_ = tmp;
            __end_ = __begin_ + s;
            _capacity = n;
        }

        void __append(size_type n, const value_type &val) {
            if (this->size() + n > _capacity)
                __realloc(this->size() + n);
            __construct_at_end(n, val);
        }

        void __grow() {
            __realloc(std::max(1UL, _capacity * 2));
        }

        void __out_of_range() const {
            throw std::out_of_range("vector");
        }

        void __reset() {
            this->clear();
            _alloc.deallocate(__begin_, _capacity);
            __begin_ = __end_ = nullptr;
        }

        template <class InputIterator>
        typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last) {
            typename iterator_traits<InputIterator>::difference_type dist = 0;
            while (first < last) {
                first++;
                dist++;
            }
            return dist;
        }

        void __move_range(pointer begin, pointer end, pointer to) {
            difference_type length = end - begin;
            if (to <= begin) {
                for (difference_type i = 0; i < length; i++)
                    to[length] = begin[length];
            } else {
                while (length--)
                    to[length] = begin[length];
            }
        }
    public:

        // default
        explicit vector(const allocator_type &alloc = allocator_type()) : _capacity(0), _alloc(alloc), __begin_(nullptr), __end_(nullptr) {
        }

        // fill
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()): _capacity(n), _alloc(alloc) {
            __begin_ = __end_ = _alloc.allocate(n);
            __construct_at_end(n, val);
        }

        // range
        // template<class InputIterator>
        // vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()): _alloc(alloc) {

        // }

        // copy
        // vector(const vector &x) {
        // }

        ~vector() {
            __reset();
        }

        void resize(size_type count, value_type value = value_type()) {
            size_type __cs = size();
            if (__cs < count)
                __append(count - __cs, value);
            else if (__cs > count)
                __destruct_at_end(__end_ - static_cast<difference_type>(__cs - count));
        }

        void reserve(size_type new_cap) {
            if (new_cap > _capacity)
                __realloc(new_cap);
        }

        void push_back(const value_type &value)
        {
            if (size() >= _capacity)
                __grow();
            __construct_at_end(1, value);
        }

        size_type size() const {
            return static_cast<size_type>(__end_ - __begin_);
        }

        size_type maxsize() const {
            return _alloc.maxsize();
        }

        size_type capacity() const {
            return _capacity;
        }

        allocator_type get_allocator() const {
            return _alloc;
        }

        // vector &operator=(const vector &other) {
        //     return *this;
        // }

        iterator insert(iterator pos, const value_type &value) {
            insert(pos, 1, value);
            return pos;
        }

        void insert(iterator pos, size_type count, const value_type &value) {
            if (size() + count > capacity()) {
                size_type old_size = size();
                size_type new_capacity = capacity() * 2;
                if (old_size + count > new_capacity)
                    new_capacity = old_size + count;

                difference_type distance = pos - begin();

                pointer tmp = _alloc.allocate(new_capacity);
                for (size_type i = 0; i < count; i++)
                    _alloc.construct(tmp + i + distance, value);
                for (size_type i = distance; i > 0; i--)
                    _alloc.construct(tmp + (i - 1), __begin_[i - 1]);
                for (size_type i = distance; i < old_size; i++)
                    _alloc.construct(tmp + i + count, __begin_[i]);
                clear();
                _alloc.deallocate(__begin_, _capacity);
                __begin_ = tmp;
                __end_ = __begin_ + old_size + count;
                _capacity = new_capacity;
            } else {
                pointer start = this->__begin_ + (pos - begin());
                pointer old_end = __end_;
                size_type construct_count = count;
                size_type overflow_count = 0;
                while (construct_count && start + construct_count > old_end) {
                    push_back(value);
                    overflow_count++;
                    construct_count--;
                }
                while (construct_count) {
                    push_back(*(old_end - construct_count));
                    construct_count--;
                }
                __move_range(start, old_end - (count - overflow_count), start + (count - overflow_count));
                for (size_type i = 0; i < count - overflow_count; i++)
                    start[i] = value;
            }
        }

        template <class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last) {
            size_type count = static_cast<size_type>(__distance(first, last));
            if (size() + count > capacity()) {
                size_type old_size = size();
                size_type new_capacity = capacity() * 2;
                if (old_size + count > new_capacity)
                    new_capacity = old_size + count;

                difference_type distance = pos - begin();

                pointer tmp = _alloc.allocate(new_capacity);
                for (size_type i = 0; i < count; i++)
                    _alloc.construct(tmp + i + distance, first[i]);
                for (size_type i = distance; i > 0; i--)
                    _alloc.construct(tmp + (i - 1), __begin_[i - 1]);
                for (size_type i = distance; i < old_size; i++)
                    _alloc.construct(tmp + i + count, __begin_[i]);
                clear();
                _alloc.deallocate(__begin_, _capacity);
                __begin_ = tmp;
                __end_ = __begin_ + old_size + count;
                _capacity = new_capacity;
            } else {
                pointer start = this->__begin_ + (pos - begin());
                pointer old_end = __end_;
                size_type construct_count = count;
                size_type overflow_count = 0;
                while (construct_count && start + construct_count > old_end) {
                    push_back(first[old_end - (start + construct_count)]);
                    overflow_count++;
                    construct_count--;
                }
                while (construct_count) {
                    push_back(*(old_end - construct_count));
                    construct_count--;
                }
                __move_range(start, old_end - (count - overflow_count), start + (count - overflow_count));
                for (size_type i = 0; i < count - overflow_count; i++)
                    start[i] = first[i];
            }
        }

        void pop_back() {
            __destruct_at_end(__end_ - 1);
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
            size_type n = static_cast<size_type>(__distance(first, last));
            clear();
            reserve(n);
            while (first < last) {
                push_back(*first);
                first++;
            }
        }

        void assign(size_type count, const value_type &val) {
            clear();
            reserve(count);
            resize(count, val);
        }

        void clear() {
            __destruct_at_end(__begin_);
        }

        bool empty() const                              { return size() == 0; }
        iterator begin()                                { return iterator(__begin_); }
        const_iterator begin() const                    { return const_iterator(__begin_); }
        iterator end()                                  { return iterator(__end_); }
        const_iterator end() const                      { return const_iterator(__end_); }
        reverse_iterator rbegin()                       { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const           { return const_reverse_iterator(end()); }
        reverse_iterator rend()                         { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const             { return const_reverse_iterator(begin()); }
        reference front()                               { return *__begin_; }
        const_reference front() const                   { return *__begin_; }
        reference back()                                { return *(__end_ - 1); }
        const_reference back() const                    { return *(__end_ - 1); }
        reference operator[](size_type n)               { return __begin_[n]; }
        const_reference operator[](size_type n) const   { return __begin_[n]; }
        reference at(size_type n)                       { if (n >= size()) __out_of_range(); return __begin_[n]; }
        const_reference at(size_type n) const           { if (n >= size()) __out_of_range(); return __begin_[n]; }
    };
}

#endif //FT_CONTAINERS_VECTOR_HPP
