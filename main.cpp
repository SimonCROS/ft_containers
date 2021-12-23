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

class Test {
public:
    static int gid;
    const int id;
    std::string issou;
    std::string *a;

    Test(const Test &s): id(gid), issou(s.issou) {
        gid++;
        std::cout << "> " << issou << " - " << id << " - copy from " << s.id << std::endl;
        a = new std::string("Hey");
    }

    Test(std::string issou): id(gid), issou(issou) {
        gid++;
        std::cout << "> " << issou << " - " << id << std::endl;
        a = new std::string("");
    }

    ~Test() {
        std::cout << "< " << issou << " - " << id << std::endl;
        delete a;
    }

    Test &operator=(const Test &rhs) {
        *this->a = *rhs.a;
        this->issou = rhs.issou;
        std::cout << "= " << issou << " - " << id << " - assign from " << rhs.id << std::endl;
        return *this;
    }
};

int Test::gid = 0;

std::ostream &operator<<(std::ostream &lhs, const Test &rhs) {
    lhs << rhs.issou << " - " << rhs.id;
    return lhs;
}

template<class T>
void show_cap(ft::vector<T> &vec) {
    std::cout << vec.size() << " - " << vec.capacity() << std::endl;
}

template<class T>
void show(ft::vector<T> &vec) {
    show_cap(vec);
    std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;
}

template<class T>
void print(ft::vector<T> &vec) {
    typename ft::vector<T>::iterator first = vec.begin();
    typename ft::vector<T>::iterator last = vec.end();
    while (first < last)
    {
        std::cout << *first << std::endl;
        first++;
    }
}

int main() {
    std::string lst[100];
    for (size_t i = 0; i < 100; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec;
    std::cout << "--- "; show_cap(vec);
    vec.reserve(12);
    std::cout << "--- "; show_cap(vec);
    vec.push_back(Test("Hello"));
    std::cout << "--- "; show_cap(vec);
    vec.push_back(Test("Nope"));
    std::cout << "--- "; show_cap(vec);
    vec.push_back(Test("Yes"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin(), Test("Issou"));
    std::cout << "--- "; show_cap(vec);
    // vec.insert(vec.begin() + 2, 2, Test("Mow"));
    // std::cout << "--- "; show_cap(vec);
    // vec.insert(vec.begin() + 2, 5, Test("Overflow"));
    // std::cout << "--- "; show_cap(vec);
    // vec.insert(vec.begin() + 8, 2, Test("Realloc"));
    // std::cout << "--- "; show_cap(vec);
    // vec.insert(vec.begin() + 9, 50, Test("Realloc 2"));
    // std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 2, lst + 0, lst + 2);
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 2, lst + 2, lst + 7);
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 8, lst + 7, lst + 9);
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 9, lst + 9, lst + 59);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);

    // ft::vector<std::string> vec;
    // try {
    //     std::cout << vec.at(2) << std::endl;
    // } catch (const std::out_of_range &e) {
    //     std::cout << "Error : " << e.what() << std::endl;
    // }
    // std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;
    // vec.reserve(3);
    // show_cap(vec);
    // vec.push_back("zero");
    // show_cap(vec);
    // vec.push_back("one");
    // show_cap(vec);
    // vec.push_back("two");
    // show_cap(vec);
    // vec.push_back("three");
    // show_cap(vec);
    // vec.push_back("four");
    // show(vec);
    // std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;

    // std::cout << "========== Iterator ==========" << std::endl;
    // ft::vector<std::string>::iterator iter = vec.begin();
    // std::cout << *iter++ << std::endl;
    // std::cout << *iter << std::endl;
    // std::cout << *++iter << std::endl;
    // std::cout << (iter < iter + 1) << std::endl;

    // std::cout << "====== Reverse Iterator ======" << std::endl;
    // ft::vector<std::string>::reverse_iterator riter = vec.rbegin();
    // std::cout << *riter++ << std::endl;
    // std::cout << *riter << std::endl;
    // std::cout << *++riter << std::endl;
    // std::cout << (riter < riter + 1) << std::endl;

    // std::cout << "======= Const Iterator =======" << std::endl;
    // ft::vector<std::string>::const_iterator citer = vec.begin();
    // std::cout << *citer++ << std::endl;
    // std::cout << *citer << std::endl;
    // std::cout << *++citer << std::endl;
    // std::cout << (iter < iter + 1) << std::endl;

    // std::cout << "=========== Assign ===========" << std::endl;
    // show(vec);

    // std::string strs[] = { "a", "b", "c", "d" };
    // vec.assign(strs, strs + 4);
    // show(vec);

    // vec.assign(3, "Hey");
    // show(vec);

    // vec.assign(10, "Hey ho");
    // show(vec);

    // std::cout << "========== Pop back ==========" << std::endl;
    // vec.pop_back();
    // show(vec);

    // std::cout << "=========== Insert ===========" << std::endl;
    // std::cout << "insert ⮐  " << *vec.insert(vec.begin(), "\033[32mNot hey\033[0m") << std::endl;
    // show(vec);
    // vec.insert(vec.begin() + 2, 9, "\033[33mMiddle\033[0m");
    // show(vec);
    // vec.insert(vec.begin() + 3, 22, "Other");
    // show(vec);
    // std::cout << "insert ⮐  " << *vec.insert(vec.end(), "\033[31mNot ho\033[0m") << std::endl;
    // show(vec);

    // std::cout << "======== Clear vector ========" << std::endl;
    // vec.clear();
    // std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;
    // show_cap(vec);

    // std::cout << "------ end ------" << std::endl;
}
