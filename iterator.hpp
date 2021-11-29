//
// Created by Simon Cros on 28/11/2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

namespace ft {

    template<class T>
    struct iterator_traits<_Tp*>
    {
        typedef ptrdiff_t difference_type;
        typedef typename remove_cv<_Tp>::type value_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator
    {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
    private:
        pointer pos;
    public:
        iterator() {}
        iterator(value_type __x) : pos(__x) {}
        iterator(const iterator<T> &__u) : pos(__u.base()) {}
        virtual ~iterator() {}

        iterator &operator=(const iterator<T> &rhs) { this->pos = rhs.pos; return *this; }

        reference operator*() const { return *pos; }
        pointer   operator->() const { return pos; }
        iterator &operator++() { ++pos; return *this; }
        iterator  operator++(int) { iterator __tmp(*this); ++pos; return __tmp; }
        iterator &operator--() { --pos; return *this; }
        iterator  operator--(int) { iterator __tmp(*this); --pos; return __tmp; }
        iterator  operator+ (difference_type __n) const { return iterator(pos + __n); }
        iterator &operator+=(difference_type __n) { pos += __n; return *this; }
        iterator  operator- (difference_type __n) const { return iterator(pos - __n); }
        iterator &operator-=(difference_type __n) { pos -= __n; return *this; }
        reference operator[](difference_type __n) const { return pos[__n]; }

        value_type base() const { return pos; }
    };

    template <class T>
    class reverse_iterator : public iterator<T>
    {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef T iterator_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
    private:
        value_type current;
    public:
        reverse_iterator(): iterator<T>() {}
        reverse_iterator(value_type __x): iterator<T>(__x) {}
        reverse_iterator(const reverse_iterator<T> &__u): iterator<T>(__u) {}
        virtual ~reverse_iterator() {}

        reverse_iterator &operator=(const reverse_iterator<T> &rhs) { this->current = rhs.current; return *this; }

        reference operator*() const {T __tmp = current; return *--__tmp;}
        pointer   operator->() const { T __tmp = current; return --__tmp; }
        reverse_iterator &operator++() { --current; return *this; }
        reverse_iterator  operator++(int) { reverse_iterator __tmp(*this); --current; return __tmp; }
        reverse_iterator &operator--() { ++current; return *this; }
        reverse_iterator  operator--(int) { reverse_iterator __tmp(*this); ++current; return __tmp; }
        reverse_iterator  operator+ (difference_type __n) const { return reverse_iterator(current - __n); }
        reverse_iterator &operator+=(difference_type __n) { current -= __n; return *this; }
        reverse_iterator  operator- (difference_type __n) const { return reverse_iterator(current + __n); }
        reverse_iterator &operator-=(difference_type __n) { current += __n; return *this; }
        reference operator[](difference_type __n) const { return current[__n]; }

        value_type base() const { return current; }
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

