//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator.hpp"

namespace ft {
    template<class T>
    class __wrap_iter {
    private:
        T pos;
    public:
        typedef T iterator_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::pointer pointer;
        typedef typename iterator_traits<iterator_type>::reference reference;
        typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

        __wrap_iter() {}

        __wrap_iter(value_type __x) : pos(__x) {}

        __wrap_iter(const __wrap_iter &__x) : pos(__x.base()) {}

        virtual ~__wrap_iter() {}

        __wrap_iter &operator=(const __wrap_iter &rhs) {
            this->pos = rhs.pos;
            return *this;
        }

        reference operator*() const { return *pos; }

        pointer operator->() const { return pos; }

        __wrap_iter &operator++() {
            ++pos;
            return *this;
        }

        __wrap_iter operator++(int) {
            __wrap_iter __tmp(*this);
            ++pos;
            return __tmp;
        }

        __wrap_iter &operator--() {
            --pos;
            return *this;
        }

        __wrap_iter operator--(int) {
            __wrap_iter __tmp(*this);
            --pos;
            return __tmp;
        }

        __wrap_iter operator+(difference_type __n) const { return __wrap_iter(pos + __n); }

        __wrap_iter &operator+=(difference_type __n) {
            pos += __n;
            return *this;
        }

        __wrap_iter operator-(difference_type __n) const { return __wrap_iter(pos - __n); }

        __wrap_iter &operator-=(difference_type __n) {
            pos -= __n;
            return *this;
        }

        reference operator[](difference_type __n) const { return pos[__n]; }

        value_type base() const { return pos; }
    };

    template<class _Iter1, class _Iter2>
    inline bool operator==(const __wrap_iter<_Iter1> &lhs, const __wrap_iter<_Iter2> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator<(const __wrap_iter<_Iter1> &lhs, const __wrap_iter<_Iter2> &rhs) { return lhs.base() < rhs.base(); }

    template<class _Iter1, class _Iter2>
    inline bool operator!=(const __wrap_iter<_Iter1> &lhs, const __wrap_iter<_Iter2> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator>(const __wrap_iter<_Iter1> &lhs, const __wrap_iter<_Iter2> &rhs) { return lhs.base() > rhs.base(); }

    template<class _Iter1, class _Iter2>
    inline bool operator>=(const __wrap_iter<_Iter1> &lhs, const __wrap_iter<_Iter2> &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator<=(const __wrap_iter<_Iter1> &lhs, const __wrap_iter<_Iter2> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class T, class Allocator = std::allocator<T> >
    class vector {
    private:
    protected:
    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename ft::__wrap_iter<pointer> iterator;
        typedef typename ft::__wrap_iter<const_pointer> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;

        explicit vector(const allocator_type &alloc = allocator_type()) {

        }

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) {

        }

        template<class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) {

        }

        vector(const vector &x) {

        }

        vector &operator=(const vector &other) {
            return *this;
        }
    };
}

#endif //FT_CONTAINERS_VECTOR_HPP
