//#include "vector.hpp"

#include <iostream>
#include <string>
#include <deque>
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
    ft::vector<std::string> vvv(50, "issou");
//    ft::vector<std::string>::iterator d = vvv.begin();
//    std::cout << *d++ << std::endl;

//    ft::vector<std::string> vec;
//    vec.push_back("zero");
//    vec.push_back("one");
//    vec.push_back("two");
//    vec.push_back("three");
//
//    std::cout << "========== Iterator ==========" << std::endl;
//    ft::vector<std::string>::iterator iter = vec.begin();
//    std::cout << *iter++ << std::endl;
//    std::cout << *iter << std::endl;
//    std::cout << *++iter << std::endl;
//    std::cout << (iter < iter + 1) << std::endl;
//
//    std::cout << "====== Reverse Iterator ======" << std::endl;
//    ft::vector<std::string>::reverse_iterator riter = vec.rbegin();
//    std::cout << *riter++ << std::endl;
//    std::cout << *riter << std::endl;
//    std::cout << *++riter << std::endl;
//    std::cout << (riter < riter + 1) << std::endl;
//
//    std::cout << "======= Const Iterator =======" << std::endl;
//    ft::vector<std::string>::const_iterator citer = vec.begin();
//    std::cout << *citer++ << std::endl;
//    std::cout << *citer << std::endl;
//    std::cout << *++citer << std::endl;
//    std::cout << (iter < iter + 1) << std::endl;
}
