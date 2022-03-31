//
// Created by Simon Cros on 28/11/2021.
//

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

namespace ft {

	template <bool B, class T = void>
	struct enable_if {};
	
	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template< class T > struct remove_cv                   { typedef T type; };
	template< class T > struct remove_cv<const T>          { typedef T type; };
	template< class T > struct remove_cv<volatile T>       { typedef T type; };
	template< class T > struct remove_cv<const volatile T> { typedef T type; };

	template<class T, T v>
	struct integral_constant {
		const static T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() const { return value; }
		value_type operator()() const { return value; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template <class T>	struct _is_integral_impl                     		: public false_type {};
	template <>			struct _is_integral_impl<bool>						: public true_type {};
	template <>			struct _is_integral_impl<char>						: public true_type {};
	template <>			struct _is_integral_impl<char16_t>					: public true_type {};
	template <>			struct _is_integral_impl<char32_t>					: public true_type {};
	template <>			struct _is_integral_impl<wchar_t>					: public true_type {};
	template <>			struct _is_integral_impl<signed char>				: public true_type {};
	template <>			struct _is_integral_impl<short int>					: public true_type {};
	template <>			struct _is_integral_impl<int>						: public true_type {};
	template <>			struct _is_integral_impl<long int>					: public true_type {};
	template <>			struct _is_integral_impl<long long int>				: public true_type {};
	template <>			struct _is_integral_impl<unsigned char>				: public true_type {};
	template <>			struct _is_integral_impl<unsigned short int>		: public true_type {};
	template <>			struct _is_integral_impl<unsigned int>				: public true_type {};
	template <>			struct _is_integral_impl<unsigned long int>			: public true_type {};
	template <>			struct _is_integral_impl<unsigned long long int>	: public true_type {};

	template <class T>	struct is_integral : public _is_integral_impl<typename remove_cv<T>::type> {};
}

#endif //FT_CONTAINERS_TYPE_TRAITS_HPP
