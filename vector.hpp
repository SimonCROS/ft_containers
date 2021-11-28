//
// Created by Simon Cros on 25/11/2021.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

namespace ft {
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
