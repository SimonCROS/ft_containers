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

	Test(): uid(guid), id(gid), issou("default") {
		guid++;
		gid++;
		std::cout << "> " << issou << " - " << uid << " - default" << std::endl;
		a = new std::string("");
	}

	Test(const Test& s): uid(guid), id(s.id), issou(s.issou) {
		guid++;
		std::cout << "> " << issou << " - " << uid << " - copy from " << s.uid << std::endl;
		a = new std::string("Hey");
	}

	Test(std::string issou): uid(guid), id(gid), issou(issou) {
		guid++;
		gid++;
		std::cout << "> " << issou << " - " << uid << std::endl;
		a = new std::string("");
	}

	~Test() {
		std::cout << "< " << issou << " - " << uid << std::endl;
		delete a;
	}

	Test& operator=(const Test& rhs) {
		*this->a = *rhs.a;
		this->id = rhs.id;
		this->issou = rhs.issou;
		std::cout << "= " << issou << " - " << uid << " - assign from " << rhs.uid << std::endl;
		return *this;
	}
};

int Test::guid = 0;
int Test::gid = 0;

std::ostream& operator<<(std::ostream& lhs, const Test& rhs) {
	lhs << rhs.issou << " - " << rhs.uid;
	return lhs;
}

bool operator== (const Test& lhs, const Test& rhs) { return lhs.id == rhs.id; }
bool operator!= (const Test& lhs, const Test& rhs) { return lhs.id != rhs.id; }
bool operator<  (const Test& lhs, const Test& rhs) { return lhs.id <  rhs.id; }
bool operator<= (const Test& lhs, const Test& rhs) { return lhs.id <= rhs.id; }
bool operator>  (const Test& lhs, const Test& rhs) { return lhs.id >  rhs.id; }
bool operator>= (const Test& lhs, const Test& rhs) { return lhs.id >= rhs.id; }

template <class T>
void show_cap(ft::vector<T>& vec) {
	std::cout << vec.size() << " - " << vec.capacity() << std::endl;
}

template <class T>
void show(ft::vector<T>& vec) {
	show_cap(vec);
	std::cout << vec.front() << " - " << vec[1] << " - " << vec.at(2) << " - " << vec.back() << std::endl;
}

template <class T>
void print(ft::vector<T>& vec) {
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
	Test& t = *vec.insert(vec.begin(), Test("Issou"));
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
	Test& t = *vec.erase(vec.begin() + 10);
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
	Test& t = *vec.erase(vec.begin() + 8, vec.begin() + 12);
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
		std::cout << "+ " << str << " OK (" << (expected == true ? "true" : "false") << ")" << std::endl;
	else
		std::cout << "- " << str << " KO (expected " << (expected == true ? "true" : "false") << ")" << std::endl;
}

void test_all_operators(const ft::vector<Test>& vec, const ft::vector<Test>& base,
	bool a, bool b, bool c, bool d, bool e, bool f) {
	test_operator(vec, base, &ft::operator==, a, "==");
	test_operator(vec, base, &ft::operator!=, b, "!=");
	test_operator(vec, base, &ft::operator< , c, "< ");
	test_operator(vec, base, &ft::operator> , d, "> ");
	test_operator(vec, base, &ft::operator<=, e, "<=");
	test_operator(vec, base, &ft::operator>=, f, ">=");
}

// Operators
void test20() {
	ft::vector<Test> base;
	base.reserve(4);
	base.assign(2, Test("Fill"));
	std::cout << "--- ---" << std::endl;
	ft::vector<Test> vec;
	std::cout << "--- ---" << std::endl;

	test_all_operators(vec, base, 0, 1, 1, 0, 1, 0);
	std::cout << "--- ---" << std::endl;
	vec = base;
	std::cout << "--- ---" << std::endl;
	test_all_operators(vec, base, 1, 0, 0, 0, 1, 1);
	vec.front().id++;
	std::cout << "--- ---" << std::endl;
	test_all_operators(vec, base, 0, 1, 0, 1, 0, 1);
	vec.back().id--;
	std::cout << "--- ---" << std::endl;
	test_all_operators(vec, base, 0, 1, 0, 1, 0, 1);
	vec.front().id--;
	std::cout << "--- ---" << std::endl;
	test_all_operators(vec, base, 0, 1, 1, 0, 1, 0);
	std::cout << "--- ---" << std::endl;
	vec.erase(vec.end() - 1);
	std::cout << "--- ---" << std::endl;
	test_all_operators(vec, base, 0, 1, 1, 0, 1, 0);
	vec.front().id++;
	std::cout << "--- ---" << std::endl;
	test_all_operators(vec, base, 0, 1, 0, 1, 0, 1);
	std::cout << "--- ---" << std::endl;
	vec = base;
	std::cout << "--- "; show_cap(vec);
}

// at
void test21() {
	std::string lst[3];
	for (size_t i = 0; i < 3; i++)
		lst[i] = "Range " + std::to_string(i);

	ft::vector<Test> vec;
	vec.reserve(5);
	vec.assign(lst + 0, lst + 3);
	std::cout << "--- ---" << std::endl;
	try {
		vec.at(8);
		std::cout << "- KO" << std::endl;
	} catch(const std::exception& e) {
		std::cout << "+ OK" << std::endl;
	}
	std::cout << "--- ---" << std::endl;
	try {
		vec.at(4);
		std::cout << "- KO" << std::endl;
	} catch(const std::exception& e) {
		std::cout << "+ OK" << std::endl;
	}
	std::cout << "--- ---" << std::endl;
	try {
		if (vec.at(2).issou == "Range 2")
			std::cout << "+ OK" << std::endl;
		else
			std::cout << "- KO" << std::endl;
	} catch(const std::exception& e) {
		std::cout << "- KO" << std::endl;
	}
	std::cout << "--- ---" << std::endl;
}

// pop_back
void test22() {
	std::string lst[3];
	for (size_t i = 0; i < 3; i++)
		lst[i] = "Range " + std::to_string(i);

	ft::vector<Test> vec;
	vec.reserve(5);
	vec.assign(lst + 0, lst + 3);
	std::cout << "--- "; show_cap(vec);
	print(vec);
	std::cout << "--- "; show_cap(vec);
	vec.pop_back();
	std::cout << "--- "; show_cap(vec);
	vec.pop_back();
	std::cout << "--- "; show_cap(vec);
	vec.pop_back();
	std::cout << "--- "; show_cap(vec);
}

// various
void test23() {
	ft::vector<std::string> vec;
	std::cout << vec.max_size() << std::endl;
	show_cap(vec);
	try {
		std::cout << vec.at(2) << std::endl;
	} catch (const std::out_of_range& e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;
	vec.reserve(3);
	show_cap(vec);
	vec.push_back("zero");
	show_cap(vec);
	vec.push_back("one");
	show_cap(vec);
	vec.push_back("two");
	show_cap(vec);
	vec.push_back("three");
	show_cap(vec);
	vec.push_back("four");
	show(vec);
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
	show(vec);

	std::string strs[] = { "a", "b", "c", "d" };
	vec.assign(strs, strs + 4);
	show(vec);

	vec.assign(3, "Hey");
	show(vec);

	vec.assign(10, "Hey ho");
	show(vec);

	std::cout << "========== Pop back ==========" << std::endl;
	vec.pop_back();
	show(vec);

	std::cout << "=========== Insert ===========" << std::endl;
	std::cout << "insert ⮐  " << *vec.insert(vec.begin(), "\033[32mNot hey\033[0m") << std::endl;
	show(vec);
	vec.insert(vec.begin() + 2, 9, "\033[33mMiddle\033[0m");
	show(vec);
	vec.insert(vec.begin() + 3, 22, "Other");
	show(vec);
	std::cout << "insert ⮐  " << *vec.insert(vec.end(), "\033[31mNot ho\033[0m") << std::endl;
	show(vec);

	std::cout << "======== Clear vector ========" << std::endl;
	vec.clear();
	std::cout << "Vector " << (vec.empty() ? "empty" : "not empty") << std::endl;
	show_cap(vec);

	std::cout << "------ end ------" << std::endl;
}

void print_map(ft::map<int, int> m) {
	ft::map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
		std::cout << (it->first) << std::endl;
}

// map empty iterator
void test24() {
	ft::map<int, int> m;
	ft::map<int, int>::iterator it;

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	std::cout << "--- Iterator	 -- ****" << std::endl;
 
	while (it != m.begin()) {
		--it;
		std::cout << (it->first) << std::endl;
	}

	std::cout << "--- Rev iterator ++ ****" << std::endl;

	ft::map<int, int>::reverse_iterator rit;
	for (rit = m.rbegin(); rit != m.rend(); rit++)
		std::cout << (rit->first) << std::endl;

	std::cout << "--- Rev iterator -- ****" << std::endl;

	while (rit != m.rbegin()) {
		--rit;
		std::cout << (rit->first) << std::endl;
	}
}

// map iterator
void test25() {
	ft::map<int, int> m;
	ft::map<int, int>::iterator it;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	std::cout << "--- Iterator	 -- ****" << std::endl;
 
	while (it != m.begin()) {
		--it;
		std::cout << (it->first) << std::endl;
	}

	std::cout << "--- Rev iterator ++ ****" << std::endl;

	ft::map<int, int>::reverse_iterator rit;
	for (rit = m.rbegin(); rit != m.rend(); rit++)
		std::cout << (rit->first) << std::endl;

	std::cout << "--- Rev iterator -- ****" << std::endl;

	while (rit != m.rbegin()) {
		--rit;
		std::cout << (rit->first) << std::endl;
	}
}

// map size
void test26() {
	ft::map<int, int> m;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));
	m.insert(ft::make_pair(2, 4));
	m.insert(ft::make_pair(1, 0));
	std::cout << m.size() << std::endl;
	m.insert(ft::make_pair(10, 5));
	m.insert(ft::make_pair(9, 3));
	m.insert(ft::make_pair(11, 3));
	m.insert(ft::make_pair(12, 3));
	std::cout << m.size() << std::endl;
	m.insert(ft::make_pair(13, 3));
	m.insert(ft::make_pair(14, 3));
	m.insert(ft::make_pair(15, 3));
	m.insert(ft::make_pair(16, 3));
	std::cout << m.size() << std::endl;
	m.insert(ft::make_pair(17, 3));
	m.insert(ft::make_pair(18, 3));
	m.insert(ft::make_pair(19, 3));
	m.insert(ft::make_pair(20, 3));
	std::cout << m.size() << std::endl;
	m.insert(ft::make_pair(21, 3));
	m.insert(ft::make_pair(22, 3));
	m.insert(ft::make_pair(23, 3));
	m.insert(ft::make_pair(3, 3));
	std::cout << m.size() << std::endl;
	m.insert(ft::make_pair(21, 3));
	m.insert(ft::make_pair(22, 3));
	m.insert(ft::make_pair(23, 3));
	m.insert(ft::make_pair(7, 3));
	std::cout << m.size() << std::endl;
}

// map insert return
void test27() {
	ft::map<int, int> m;

	ft::pair<ft::map<int, int>::iterator, bool> p;

	p = m.insert(ft::make_pair(7, 3));
	std::cout << "Inside " << p.second << " (" << p.first->second << ")" << std::endl;
	p = m.insert(ft::make_pair(7, 8));
	std::cout << "Inside " << p.second << " (" << p.first->second << ")" << std::endl;
	p.first->second = 7;
	p = m.insert(ft::make_pair(7, 3));
	std::cout << "Inside " << p.second << " (" << p.first->second << ")" << std::endl;
}

// map insert pos
void test28() {
	ft::map<int, int> m;

	ft::map<int, int>::iterator p;

	p = m.insert(m.end(), ft::make_pair(7, 3));
	std::cout << p->second << std::endl;
	p = m.insert(p, ft::make_pair(7, 8));
	std::cout << p->second << std::endl;
	p->second = 7;
	p = m.insert(p, ft::make_pair(7, 3));
	std::cout << p->second << std::endl;
	p = m.insert(p, ft::make_pair(2, 2));
	std::cout << p->second << std::endl;
	p = m.insert(p, ft::make_pair(4, 2));
	p = m.insert(p, ft::make_pair(8, 1));
	p = m.insert(p, ft::make_pair(2, 4));
	p = m.insert(p, ft::make_pair(1, 0));
	std::cout << m.size() << std::endl;
	p = m.insert(p, ft::make_pair(10, 5));
	p = m.insert(p, ft::make_pair(9, 3));
	p = m.insert(p, ft::make_pair(11, 3));
	p = m.insert(p, ft::make_pair(12, 3));
	std::cout << m.size() << std::endl;
	p = m.insert(p, ft::make_pair(13, 3));
	p = m.insert(p, ft::make_pair(14, 3));
	p = m.insert(p, ft::make_pair(15, 3));
	p = m.insert(p, ft::make_pair(16, 3));
	std::cout << m.size() << std::endl;
}

// map insert range
void test29() {
	ft::map<int, int> m;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));
	m.insert(ft::make_pair(2, 4));
	m.insert(ft::make_pair(1, 0));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	ft::map<int, int> new_m;
	new_m.insert(m.begin(), m.end());

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(new_m);

	std::cout << new_m.size() << std::endl;
}

// map find and count
void test30() {
	ft::map<int, int> m;
	ft::map<int, int>::iterator it;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));
	m.insert(ft::make_pair(2, 4));
	m.insert(ft::make_pair(1, 0));

	it = m.find(42);
	if (it == m.end())
		std::cout << "Not found" << std::endl;
	else
		std::cout << it->first << " = " << it->second << std::endl;
	std::cout << "Count : " << m.count(42) << std::endl;

	it = m.find(4);
	if (it == m.end())
		std::cout << "Not found" << std::endl;
	else
		std::cout << it->first << " = " << it->second << std::endl;
	std::cout << "Count : " << m.count(4) << std::endl;
	std::cout << "Size : " << m.size() << std::endl;
}

// map access operator
void test31() {
	ft::map<int, int> m;
	ft::map<int, int>::iterator it;

	m[42] = 21;

	it = m.find(42);
	if (it == m.end())
		std::cout << "Not found" << std::endl;
	else
		std::cout << it->first << " = " << it->second << std::endl;
	std::cout << "Count : " << m.count(42) << std::endl;

	it = m.find(4);
	if (it == m.end())
		std::cout << "Not found" << std::endl;
	else
		std::cout << it->first << " = " << it->second << std::endl;
	std::cout << "Count : " << m.count(4) << std::endl;
	std::cout << "Size : " << m.size() << std::endl;
}

// map copy
void test32() {
	ft::map<int, int>::iterator it;
	ft::map<int, int> m;
	ft::map<int, int> cpy;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));
	m.insert(ft::make_pair(2, 4));
	m.insert(ft::make_pair(1, 0));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	cpy = m;

	std::cout << "size: " << m.size() << std::endl;
	m.clear();
	std::cout << "size: " << m.size() << std::endl;

	std::cout << "--- Iterator	 ++ ****" << std::endl;
 
	for (it = cpy.begin(); it != cpy.end(); it++)
		std::cout << (it->first) << std::endl;

	ft::map<int, int> ccpy(cpy);

	std::cout << "size: " << cpy.size() << std::endl;
	cpy.clear();
	std::cout << "size: " << cpy.size() << std::endl;

	std::cout << "--- Iterator	 ++ ****" << std::endl;
 
	for (it = ccpy.begin(); it != ccpy.end(); it++)
		std::cout << (it->first) << std::endl;

	std::cout << "size: " << ccpy.size() << std::endl;
}

// map range constructor
void test33() {
	ft::map<int, int> m;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));
	m.insert(ft::make_pair(2, 4));
	m.insert(ft::make_pair(1, 0));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	ft::map<int, int> new_m(m.begin(), m.end());

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(new_m);

	std::cout << new_m.size() << std::endl;
}

void test_lower_upper(ft::map<int, int> m, int n) {
	ft::map<int, int>::iterator lower;
	ft::map<int, int>::iterator upper;
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> range;

	lower = m.lower_bound(n);
	if (lower == m.end())
		std::cout << "lower == end" << std::endl;
	else
		std::cout << "lower == " << (lower->second) << std::endl;

	upper = m.upper_bound(n);
	if (upper == m.end())
		std::cout << "upper == end" << std::endl;
	else
		std::cout << "upper == " << (upper->second) << std::endl;

	range = m.equal_range(n);
	if (range.first == m.end())
		std::cout << "range.first == end" << std::endl;
	else
		std::cout << "range.first == " << (range.first->second) << std::endl;
	if (range.second == m.end())
		std::cout << "range.second == end" << std::endl;
	else
		std::cout << "range.second == " << (range.second->second) << std::endl;
}

// map upper/lower bounds
void test34() {
	ft::map<int, int> m;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));
	m.insert(ft::make_pair(2, 4));
	m.insert(ft::make_pair(1, 0));

	test_lower_upper(m, 8);
	std::cout << "=====================" << std::endl;
	test_lower_upper(m, 18);
	std::cout << "=====================" << std::endl;
	test_lower_upper(m, 2);
	std::cout << "=====================" << std::endl;
	test_lower_upper(m, 3);
}

// map max_size
void test35() {
	ft::map<int, int> mi;
	std::cout << mi.max_size() << std::endl;

	ft::map<char, char> mc;
	std::cout << mc.max_size() << std::endl;
}

#include <map>

// map erase
void test36() {
	ft::map<int, int> m;
	ft::map<int, int>::iterator it;

	m.insert(ft::make_pair(4, 2));
	m.insert(ft::make_pair(8, 1));
	m.insert(ft::make_pair(2, 4));
	m.insert(ft::make_pair(1, 0));
	m.insert(ft::make_pair(10, 5));
	m.insert(ft::make_pair(9, 3));
	m.insert(ft::make_pair(11, 3));
	m.insert(ft::make_pair(12, 3));

	m.erase(m.find(11));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	m.insert(ft::make_pair(13, 3));
	m.insert(ft::make_pair(14, 3));
	m.insert(ft::make_pair(15, 3));
	m.insert(ft::make_pair(16, 3));

	m.erase(m.find(16));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	m.insert(ft::make_pair(17, 3));
	m.insert(ft::make_pair(18, 3));
	m.insert(ft::make_pair(19, 3));
	m.insert(ft::make_pair(20, 3));

	m.erase(m.find(17));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	m.insert(ft::make_pair(3, 3));
	m.insert(ft::make_pair(7, 3));
	m.insert(ft::make_pair(22, 3));
	m.insert(ft::make_pair(23, 3));

	m.erase(m.find(13));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	m.erase(m.find(9));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	m.erase(m.find(14));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);

	m.erase(m.find(10), m.find(18));

	std::cout << "--- Iterator	 ++ ****" << std::endl;
	print_map(m);
}

// is_integral
void test37() {
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "const int: " << ft::is_integral<const int>::value << std::endl;
	std::cout << "volatile int: " << ft::is_integral<volatile int>::value << std::endl;
	std::cout << "const volatile int: " << ft::is_integral<const volatile int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
}

// TODO Test iterators
int main() {
	// Vector

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
	// std::cout << "========= TEST 20 =========" << std::endl;
	// test20();
	// std::cout << "========= TEST 21 =========" << std::endl;
	// test21();
	// std::cout << "========= TEST 22 =========" << std::endl;
	// test22();
	// std::cout << "========= TEST 23 =========" << std::endl;
	// test23();

	// Map

	// std::cout << "========= TEST 24 =========" << std::endl;
	// test24();
	// std::cout << "========= TEST 25 =========" << std::endl;
	// test25();
	// std::cout << "========= TEST 26 =========" << std::endl;
	// test26();
	// std::cout << "========= TEST 27 =========" << std::endl;
	// test27();
	// std::cout << "========= TEST 28 =========" << std::endl;
	// test28();
	// std::cout << "========= TEST 29 =========" << std::endl;
	// test29();
	// std::cout << "========= TEST 30 =========" << std::endl;
	// test30();
	// std::cout << "========= TEST 31 =========" << std::endl;
	// test31();
	// std::cout << "========= TEST 32 =========" << std::endl;
	// test32();
	// std::cout << "========= TEST 33 =========" << std::endl;
	// test33();
	// std::cout << "========= TEST 34 =========" << std::endl;
	// test34();
	// std::cout << "========= TEST 35 =========" << std::endl;
	// test35();
	std::cout << "========= TEST 36 =========" << std::endl; // TODO
	test36();

	// Misc

	// std::cout << "========= TEST 37 =========" << std::endl;
	// test37();
}
