#include <iostream>
#include <string>
#ifdef STL_CONTAINERS
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
    static int guid;
    const int uid;
    static int gid;
    int id;
    std::string issou;
    std::string *a;

    Test(const Test &s): uid(guid), id(s.id), issou(s.issou) {
        guid++;
        gid++;
        std::cout << "> " << issou << " - " << id << " - copy from " << s.id << std::endl;
        a = new std::string("Hey");
    }

    Test(std::string issou): uid(guid), id(gid), issou(issou) {
        guid++;
        std::cout << "> " << issou << " - " << id << std::endl;
        a = new std::string("");
    }

    ~Test() {
        std::cout << "< " << issou << " - " << id << std::endl;
        delete a;
    }

    Test &operator=(const Test &rhs) {
        *this->a = *rhs.a;
        this->id = rhs.id;
        this->issou = rhs.issou;
        std::cout << "= " << issou << " - " << id << " - assign from " << rhs.id << std::endl;
        return *this;
    }
};

int Test::guid = 0;
int Test::gid = 0;

std::ostream &operator<<(std::ostream &lhs, const Test &rhs) {
    lhs << rhs.issou << " - " << rhs.uid;
    return lhs;
}

bool operator== (const Test& lhs, const Test& rhs) { return lhs.id == rhs.id; }
bool operator!= (const Test& lhs, const Test& rhs) { return lhs.id != rhs.id; }
bool operator<  (const Test& lhs, const Test& rhs) { return lhs.id <  rhs.id; }
bool operator<= (const Test& lhs, const Test& rhs) { return lhs.id <= rhs.id; }
bool operator>  (const Test& lhs, const Test& rhs) { return lhs.id >  rhs.id; }
bool operator>= (const Test& lhs, const Test& rhs) { return lhs.id >= rhs.id; }

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

// Insert (count)
void test1() {
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
    Test &t = *vec.insert(vec.begin(), Test("Issou"));
    std::cout << "*** " << t << std::endl;
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 2, 2, Test("Mow"));
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 2, 5, Test("Overflow"));
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 8, 2, Test("Realloc"));
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin() + 9, 50, Test("Realloc 2"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Insert (range)
void test2() {
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
}

// Insert on empty vector (count)
void test3() {
    ft::vector<Test> vec;
    vec.insert(vec.begin(), 50, Test("Message"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Insert on empty vector (range)
void test4() {
    std::string lst[100];
    for (size_t i = 0; i < 100; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec;
    vec.insert(vec.begin(), lst + 10, lst + 60);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Erase (simple)
void test5() {
    std::string lst[20];
    for (size_t i = 0; i < 20; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec;
    vec.insert(vec.begin(), lst + 0, lst + 20);
    std::cout << "--- "; show_cap(vec);
    Test &t = *vec.erase(vec.begin() + 10);
    std::cout << "*** " << t << std::endl;
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Erase (range)
void test6() {
    std::string lst[20];
    for (size_t i = 0; i < 20; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec;
    vec.insert(vec.begin(), lst + 0, lst + 20);
    std::cout << "--- "; show_cap(vec);
    Test &t = *vec.erase(vec.begin() + 8, vec.begin() + 12);
    std::cout << "*** " << t << std::endl;
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Swap (member and non-member overload)
void test7() {
    ft::vector<Test> foo(3, Test("FOO"));
    std::cout << "--- "; show_cap(foo);
    ft::vector<Test> bar(5, Test("BAR"));
    std::cout << "--- "; show_cap(bar);

    foo.swap(bar);
    std::cout << "--- foo "; show_cap(foo);
    print(foo);
    std::cout << "--- bar "; show_cap(bar);
    print(bar);
    std::cout << "--- ---" << std::endl;
    ft::swap(foo, bar);
    std::cout << "--- foo "; show_cap(foo);
    print(foo);
    std::cout << "--- bar "; show_cap(bar);
    print(bar);
    std::cout << "--- ---" << std::endl;
}

// Assign in empty vector (count)
void test8() {
    ft::vector<Test> vec;
    std::cout << "--- "; show_cap(vec);
    vec.assign(20, Test("Assigned"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Assign in smaller vector (count)
void test9() {
    ft::vector<Test> vec;
    vec.reserve(5);
    std::cout << "--- "; show_cap(vec);
    vec.push_back(Test("Little"));
    std::cout << "--- "; show_cap(vec);
    vec.push_back(Test("Little"));
    std::cout << "--- "; show_cap(vec);
    vec.assign(4, Test("Assigned"));
    std::cout << "--- "; show_cap(vec);
    vec.assign(10, Test("Assigned 2"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Assign in bigger vector (count)
void test10() {
    ft::vector<Test> vec;
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin(), 20, Test("Big")),
    std::cout << "--- "; show_cap(vec);
    vec.assign(8, Test("Assigned"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
    vec.assign(20, Test("Assigned 2"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Assign in empty vector (range)
void test11() {
    std::string lst[20];
    for (size_t i = 0; i < 20; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec;
    std::cout << "--- "; show_cap(vec);
    vec.assign(lst + 0, lst + 20);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Assign in smaller vector (range)
void test12() {
    std::string lst[20];
    for (size_t i = 0; i < 20; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec;
    vec.reserve(5);
    std::cout << "--- "; show_cap(vec);
    vec.push_back(Test("Little"));
    std::cout << "--- "; show_cap(vec);
    vec.push_back(Test("Little"));
    std::cout << "--- "; show_cap(vec);
    vec.assign(lst + 0, lst + 4);
    std::cout << "--- "; show_cap(vec);
    vec.assign(lst + 4, lst + 14);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Assign in bigger vector (range)
void test13() {
    std::string lst[28];
    for (size_t i = 0; i < 28; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec;
    std::cout << "--- "; show_cap(vec);
    vec.insert(vec.begin(), 20, Test("Big")),
    std::cout << "--- "; show_cap(vec);
    vec.assign(lst + 0, lst + 8);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
    vec.assign(lst + 8, lst + 28);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Constructor (default)
void test14() {
    ft::vector<Test> vec;
    std::cout << "--- "; show_cap(vec);
}

// Constructor (fill)
void test15() {
    ft::vector<Test> vec(20, Test("Fill"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Constructor (range)
void test16() {
    std::string lst[20];
    for (size_t i = 0; i < 20; i++)
        lst[i] = "Range " + std::to_string(i);

    ft::vector<Test> vec(lst + 0, lst + 20);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Constructor (copy)
void test17() {
    ft::vector<Test> base;
    base.reserve(10);
    base.assign(5, Test("Fill"));
    std::cout << "--- "; show_cap(base);

    ft::vector<Test> vec(base);
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

// Reserve
void test18() {
    ft::vector<Test> vec(2, Test("Fill"));
    std::cout << "--- "; show_cap(vec);
    vec.reserve(4);
    std::cout << "--- "; show_cap(vec);
    vec.reserve(2);
    std::cout << "--- "; show_cap(vec);
}

// Resize
void test19() {
    ft::vector<Test> vec(2, Test("Fill"));
    std::cout << "--- "; show_cap(vec);
    vec.resize(10, Test("New size"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
    vec.resize(6, Test("Reduce"));
    std::cout << "--- "; show_cap(vec);
    print(vec);
    std::cout << "--- "; show_cap(vec);
}

void test_operator(const ft::vector<Test>& vec, const ft::vector<Test>& base, bool (*op)(const ft::vector<Test>&, const ft::vector<Test>&), bool expected, std::string str) {
    if (op(vec, base) == expected)
        std::cout << "+ " << str << " OK" << std::endl;
    else
        std::cout << "- " << str << " KO" << std::endl;
}

// Operators
void test20() {
    ft::vector<Test> base(2, Test("Fill"));
    std::cout << "--- ---" << std::endl;
    ft::vector<Test> vec;
    std::cout << "--- ---" << std::endl;

    test_operator(vec, base, &ft::operator==, 0, "==");
    test_operator(vec, base, &ft::operator!=, 1, "!=");
    test_operator(vec, base, &ft::operator< , 1, "< ");
    test_operator(vec, base, &ft::operator> , 0, "> ");
    test_operator(vec, base, &ft::operator<=, 1, "<=");
    test_operator(vec, base, &ft::operator>=, 0, ">=");

    std::cout << "--- ---" << std::endl;
    vec = base;
    std::cout << "--- ---" << std::endl;

    test_operator(vec, base, &ft::operator==, 1, "==");
    test_operator(vec, base, &ft::operator!=, 0, "!=");
    test_operator(vec, base, &ft::operator< , 0, "< ");
    test_operator(vec, base, &ft::operator> , 0, "> ");
    test_operator(vec, base, &ft::operator<=, 1, "<=");
    test_operator(vec, base, &ft::operator>=, 1, ">=");

    vec.front().id++;
    std::cout << "--- ---" << std::endl;

    test_operator(vec, base, &ft::operator==, 0, "==");
    test_operator(vec, base, &ft::operator!=, 1, "!=");
    test_operator(vec, base, &ft::operator< , 0, "< ");
    test_operator(vec, base, &ft::operator> , 1, "> ");
    test_operator(vec, base, &ft::operator<=, 0, "<=");
    test_operator(vec, base, &ft::operator>=, 1, ">=");

    vec.back().id--;
    std::cout << "--- ---" << std::endl;

    test_operator(vec, base, &ft::operator==, 0, "==");
    test_operator(vec, base, &ft::operator!=, 1, "!=");
    test_operator(vec, base, &ft::operator< , 0, "< ");
    test_operator(vec, base, &ft::operator> , 1, "> ");
    test_operator(vec, base, &ft::operator<=, 0, "<=");
    test_operator(vec, base, &ft::operator>=, 1, ">=");

    vec.front().id--;
    std::cout << "--- ---" << std::endl;

    test_operator(vec, base, &ft::operator==, 0, "==");
    test_operator(vec, base, &ft::operator!=, 1, "!=");
    test_operator(vec, base, &ft::operator< , 1, "< ");
    test_operator(vec, base, &ft::operator> , 0, "> ");
    test_operator(vec, base, &ft::operator<=, 1, "<=");
    test_operator(vec, base, &ft::operator>=, 0, ">=");

    std::cout << "--- ---" << std::endl;
    vec.erase(vec.end() - 1);
    std::cout << "--- ---" << std::endl;

    test_operator(vec, base, &ft::operator==, 0, "==");
    test_operator(vec, base, &ft::operator!=, 1, "!=");
    test_operator(vec, base, &ft::operator< , 1, "< ");
    test_operator(vec, base, &ft::operator> , 0, "> ");
    test_operator(vec, base, &ft::operator<=, 1, "<=");
    test_operator(vec, base, &ft::operator>=, 0, ">=");

    vec.front().id++;
    std::cout << "--- ---" << std::endl;

    test_operator(vec, base, &ft::operator==, 0, "==");
    test_operator(vec, base, &ft::operator!=, 1, "!=");
    test_operator(vec, base, &ft::operator< , 0, "< ");
    test_operator(vec, base, &ft::operator> , 1, "> ");
    test_operator(vec, base, &ft::operator<=, 0, "<=");
    test_operator(vec, base, &ft::operator>=, 1, ">=");

    std::cout << "--- ---" << std::endl;
}

int main() {
    // std::cout << "========= TEST 1 =========" << std::endl;
    // test1();
    // std::cout << "========= TEST 2 =========" << std::endl;
    // test2();
    // std::cout << "========= TEST 3 =========" << std::endl;
    // test3();
    // std::cout << "========= TEST 4 =========" << std::endl;
    // test4();
    // std::cout << "========= TEST 5 =========" << std::endl;
    // test5();
    // std::cout << "========= TEST 6 =========" << std::endl;
    // test6();
    // std::cout << "========= TEST 7 =========" << std::endl;
    // test7();
    // std::cout << "========= TEST 8 =========" << std::endl;
    // test8();
    // std::cout << "========= TEST 9 =========" << std::endl;
    // test9();
    // std::cout << "========= TEST 10 =========" << std::endl;
    // test10();
    // std::cout << "========= TEST 11 =========" << std::endl;
    // test11();
    // std::cout << "========= TEST 12 =========" << std::endl;
    // test12();
    // std::cout << "========= TEST 13 =========" << std::endl;
    // test13();
    // std::cout << "========= TEST 14 =========" << std::endl;
    // test14();
    // std::cout << "========= TEST 15 =========" << std::endl;
    // test15();
    // std::cout << "========= TEST 16 =========" << std::endl;
    // test16();
    // std::cout << "========= TEST 17 =========" << std::endl;
    // test17();
    // std::cout << "========= TEST 18 =========" << std::endl;
    // test18();
    // std::cout << "========= TEST 19 =========" << std::endl;
    // test19();
    std::cout << "========= TEST 20 =========" << std::endl;
    test20();

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
