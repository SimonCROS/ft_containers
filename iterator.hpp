//
// Created by Simon Cros on 28/11/2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

namespace ft {
    template <class T>
    class iterator
    {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
    private:
        value_type pos;
    public:
        iterator() {}
        iterator(value_type __x) : pos(__x) {}
        iterator(const iterator<T>& __u) : pos(__u.base()) {}
        virtual ~iterator() {}

        reference operator*() const { return *pos; }
        pointer   operator->() const { return pos }
        iterator& operator++() { ++pos; return *this; }
        iterator  operator++(int) { iterator __tmp(*this); ++(*this); return __tmp; }
        iterator& operator--() { --pos; return *this; }
        iterator  operator--(int) { iterator __tmp(*this); --(*this); return __tmp; }
        iterator  operator+ (difference_type __n) const { return iterator(*this + __n); }
        iterator& operator+=(difference_type __n) { pos += __n; return *this; }
        iterator  operator- (difference_type __n) const { return *this + (-__n); }
        iterator& operator-=(difference_type __n) { *this += -__n; return *this; }
        reference operator[](difference_type __n) const { return pos[__n]; }

        value_type base() const { return pos; }
    };

    template <class _Iter1, class _Iter2>
    inline bool operator==(const iterator<_Iter1> &lhs, const iterator<_Iter2> &rhs) { return lhs.base() == rhs.base(); }
    template <class _Iter1, class _Iter2>
    inline bool operator<(const iterator<_Iter1> &lhs, const iterator<_Iter2> &rhs) { return lhs.base() < rhs.base(); }
    template <class _Iter1, class _Iter2>
    inline bool operator!=(const iterator<_Iter1> &lhs, const iterator<_Iter2> &rhs) { return lhs.base() != rhs.base(); }
    template <class _Iter1, class _Iter2>
    inline bool operator>(const iterator<_Iter1> &lhs, const iterator<_Iter2> &rhs) { return lhs.base() > rhs.base(); }
    template <class _Iter1, class _Iter2>
    inline bool operator>=(const iterator<_Iter1> &lhs, const iterator<_Iter2> &rhs) { return lhs.base() >= rhs.base(); }
    template <class _Iter1, class _Iter2>
    inline bool operator<=(const iterator<_Iter1> &lhs, const iterator<_Iter2> &rhs) { return lhs.base() <= rhs.base(); }
}

#endif //FT_CONTAINERS_ITERATOR_HPP

//
// Created by Simon Cros on 28/11/2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

namespace ft {

    class iterator {
    protected:
        T *current;
    public:

        iterator() : p(NULL) {}
        iterator(pointer ptr) : current(ptr) {}
        iterator(const iterator &src) {}
        iterator &operator=(const iterator &rhs) { this->current = rhs.current; return *this; }
        ~iterator() {}

        reference operator*() const { return *current; }
        pointer operator->() const { return current; }
        iterator &operator++() { current++; return *this; }
        iterator operator++(int) { iterator tmp(*this); -current; return tmp; }
        iterator &operator--() { current--; return *this; }
        iterator operator--(int) { current--; return *this; }
        iterator operator+(difference_type x) { return iterator(*this + x) }
        iterator &operator+=(difference_type x) { current += x; }
        iterator operator-(difference_type x) { return iterator(*this - x) }
        iterator &operator-=(difference_type x) { current -= x; }
        reference operator[](difference_type &x) { return *(*this + x); }
}

#endif //FT_CONTAINERS_ITERATOR_HPP

