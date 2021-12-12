//#include "vector.hpp"

#include <iostream>
#include <string>
#if 0
    #include <map>
    #include <stack>
    #include <vector>
    namespace ft = std;
#else
    #include <map.hpp>
    #include <stack.hpp>
    #include <vector.hpp>
#endif

int main() {
    ft::vector<std::string> vec;
    try {
        std::cout << vec.at(2) << std::endl;
    } catch (const std::out_of_range &e) {
        std::cout << "Error : " << e.what() << std::endl;
    }
    std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;
    vec.reserve(3);
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    vec.push_back("zero");
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    vec.push_back("one");
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    vec.push_back("two");
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    vec.push_back("three");
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    vec.push_back("four");
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    std::cout << vec.front() << " - " << vec.back() << " - " << vec[2] << " - " << vec.at(2) << std::endl;
    std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;

    std::cout << "========== Iterator ==========" << std::endl;
    ft::vector<std::string>::iterator iter = vec.begin();
    std::cout << *iter++ << std::endl;
    std::cout << *iter << std::endl;
    std::cout << *++iter << std::endl;
    std::cout << (iter < iter + 1) << std::endl;

    std::cout << "====== Reverse Iterator ======" << std::endl;
    ft::vector<std::string>::reverse_iterator riter = vec.rbegin();
    std::cout << *riter++ << std::endl;
    std::cout << *riter << std::endl;
    std::cout << *++riter << std::endl;
    std::cout << (riter < riter + 1) << std::endl;

    std::cout << "======= Const Iterator =======" << std::endl;
    ft::vector<std::string>::const_iterator citer = vec.begin();
    std::cout << *citer++ << std::endl;
    std::cout << *citer << std::endl;
    std::cout << *++citer << std::endl;
    std::cout << (iter < iter + 1) << std::endl;

    std::cout << "======== Clear vector ========" << std::endl;

    vec.clear();
    std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;

    std::cout << "------ end ------" << std::endl;
}
