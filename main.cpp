#include <iostream>
#include <string>
#if 0
    #include <map>
    #include <stack>
    #include <vector>
    namespace ft = std;
#else
    #include "map.hpp"
    #include "stack.hpp"
    #include "vector.hpp"
#endif

//class Test {
//public:
//    std::string issou;
//    std::string *a;
//    bool log;
//
//    Test(const Test &s): issou(s.issou), log(true) {
//        std::cout << "On - " << issou << " - copy" << std::endl;
//        a = new std::string("Hey");
//    }
//
//    Test(std::string issou): issou(issou), log(false) {
//        a = NULL;
//    }
//
//    ~Test() {
////        if (log)
////            std::cout << "Off - " << issou << std::endl;
//        delete a;
//    }
//};

int main() {
//    ft::vector<Test> vec;
//    vec.reserve(4);
//    vec.push_back(Test("Hello"));
//    std::cout << "---" << std::endl;
//    vec.push_back(Test("Nope"));
//    std::cout << "---" << std::endl;
//    vec.push_back(Test("Yes"));
//    std::cout << "---" << std::endl;
//    vec.assign(vec.begin() + 1, vec.end());

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
    std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;
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

    std::cout << "=========== Assign ===========" << std::endl;
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;

    std::string strs[] = { "a", "b", "c", "d" };
    vec.assign(strs, strs + 4);
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;

    vec.assign(3, "Hey");
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;

    vec.assign(10, "Hey ho");
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;

    // std::cout << "========== Pop back ==========" << std::endl;
    // vec.pop_back();
    // std::cout << vec.size() << " - " << vec.capacity() << std::endl;
    // std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;

    std::cout << "======== Clear vector ========" << std::endl;
    vec.clear();
    std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;

    std::cout << "------ end ------" << std::endl;
}
