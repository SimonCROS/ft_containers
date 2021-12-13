//
// Created by Simon Cros on 28/11/2021.
//

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

namespace ft {

	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

}

#endif //FT_CONTAINERS_TYPE_TRAITS_HPP
