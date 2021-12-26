//
// Created by Simon Cros on 28/11/2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

namespace ft {

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class Iterator>
    class iterator_traits {
    public:
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template<class T>
    class iterator_traits<T *> {
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template<class T>
    class iterator_traits<const T *> {
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T& reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template<class Iterator>
    class __normal_iterator {
    private:
        Iterator current;
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::pointer pointer;
        typedef typename iterator_traits<iterator_type>::reference reference;
        typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

        __normal_iterator() {}

        __normal_iterator(pointer __x) : current(__x) {}

        template<typename _Iter>
        __normal_iterator(const __normal_iterator<_Iter>& __x) : current(__x.base()) {}

        virtual ~__normal_iterator() {}

        __normal_iterator& operator=(const __normal_iterator& rhs) {
            this->current = rhs.current;
            return *this;
        }

        reference operator*() const { return *current; }

        pointer operator->() const { return current; }

        __normal_iterator& operator++() {
            ++current;
            return *this;
        }

        __normal_iterator operator++(int) {
            __normal_iterator __tmp(*this);
            ++current;
            return __tmp;
        }

        __normal_iterator& operator--() {
            --current;
            return *this;
        }

        __normal_iterator operator--(int) {
            __normal_iterator __tmp(*this);
            --current;
            return __tmp;
        }

        __normal_iterator operator+(difference_type __n) const {
            __normal_iterator __w(*this);
            __w += __n;
            return __w;
        }

        __normal_iterator& operator+=(difference_type __n) {
            current += __n;
            return *this;
        }

        __normal_iterator operator-(difference_type __n) const {
            __normal_iterator __w(*this);
            __w -= __n;
            return __w;
        }

        __normal_iterator& operator-=(difference_type __n) {
            current -= __n;
            return *this;
        }

        reference operator[](difference_type __n) const { return current[__n]; }

        Iterator base() const { return current; }
    };

    template<class _Iter1, class _Iter2>
    inline bool operator==(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() == rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator!=(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() != rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator<(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() < rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator>(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() > rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator>=(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator<=(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline typename __normal_iterator<_Iter1>::difference_type operator+(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() + rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline typename __normal_iterator<_Iter1>::difference_type operator-(const __normal_iterator<_Iter1>& lhs, const __normal_iterator<_Iter2>& rhs) {
        return lhs.base() - rhs.base();
    }

    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T& >
    struct iterator {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

    template<class T>
    class reverse_iterator : public iterator<typename iterator_traits<T>::iterator_category,
            typename iterator_traits<T>::value_type,
            typename iterator_traits<T>::difference_type,
            typename iterator_traits<T>::pointer,
            typename iterator_traits<T>::reference> {
    protected:
        T current;
        typedef iterator_traits<T>                          __traits_type;
    public:
        typedef T                                           iterator_type;
        typedef typename __traits_type::difference_type     difference_type;
        typedef typename __traits_type::pointer             pointer;
        typedef typename __traits_type::reference           reference;

        reverse_iterator() : current() {}

        explicit reverse_iterator(iterator_type __x) : current(__x) {}

        template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) {}

        virtual ~reverse_iterator() {}

        reverse_iterator& operator=(const reverse_iterator<T>& rhs) {
            this->current = rhs.current;
            return *this;
        }

        reference operator*() const {
            T __tmp = current;
            return *--__tmp;
        }

        pointer operator->() const {
            T __tmp = current;
            return --__tmp;
        }

        reverse_iterator& operator++() {
            --current;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator __tmp(*this);
            --current;
            return __tmp;
        }

        reverse_iterator& operator--() {
            ++current;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator __tmp(*this);
            ++current;
            return __tmp;
        }

        reverse_iterator operator+(difference_type __n) const { return reverse_iterator(current - __n); }

        reverse_iterator& operator+=(difference_type __n) {
            current -= __n;
            return *this;
        }

        reverse_iterator operator-(difference_type __n) const { return reverse_iterator(current + __n); }

        reverse_iterator& operator-=(difference_type __n) {
            current += __n;
            return *this;
        }

        reference operator[](difference_type __n) const { return current[__n]; }

        iterator_type base() const { return current; }
    };

    template<class _Iter1, class _Iter2>
    inline bool operator==(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() == rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator!=(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() != rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator<(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() > rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator>(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() < rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator>=(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline bool operator<=(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline typename reverse_iterator<_Iter1>::difference_type operator+(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() - rhs.base();
    }

    template<class _Iter1, class _Iter2>
    inline typename reverse_iterator<_Iter1>::difference_type operator-(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs) {
        return lhs.base() + rhs.base();
    }
}

#endif //FT_CONTAINERS_ITERATOR_HPP
