#include <iostream>
#include <vector>
#include <list>
#include <complex>

void f() {
    int count{1}; // initialize to 1
    const char *name{"Bjarne"}; // name is variable that pointed const
    count = 2; // assign 2 to count
    name = "Marian";

    std::cout << count << std::endl; // 2
    std::cout << name << std::endl; // Marian
}

//===--------------------------------------------------------------===//
// 6.3.1 structure of declaration
//===--------------------------------------------------------------===//

const char *kings[] = {"Antigonus", "Seleucus", "Ptolemy"};
// Type: const char
// Declarators: *kings[]
// Initializer: = {"Antigonus", "Seleucus", "Ptolemy"};

// const c = 7; // Error: no type
// gt(int a, int b) { return (a > b) ? a : b; } // Error: no return type

unsigned ui; // OK: "unsigned" is "unsigned int"
long li;     // OK: "long" is "long int"

//===--------------------------------------------------------------===//
// 6.3.2 multiple declaration
//===--------------------------------------------------------------===//

int x_1, y_1; // int x_1; int y_1;

//===--------------------------------------------------------------===//
// 6.3.4 scope
//===--------------------------------------------------------------===//

int x_4; // global scope

void f4_1() { // function scope
    int x_4; // local x_4 hide global x_4
    x_4 = 1; // assignment to local x_4

    { // block
        int x_4; // hide first local x_4
        x_4 = 2; // assignment to second local x_4
        std::cout << x_4 << std::endl; // 2
    }

    std::cout << x_4 << std::endl; // 1
    x_4 = 3; // assignment to first local x_4
}

void f4_2() {
    int x_4 = 1; // hide global x_4
    ::x_4 = 2; // assignment to global x_4
    std::cout << x_4 << std::endl; // 1

    x_4 = 2;
    std::cout << x_4 << std::endl; // 2
}

int x_4_2 = 97;

void f4_3() {
    int x_4_2 = x_4_2; // initialize by uninitialized self value
    std::cout << x_4_2 << std::endl;
}

int x_4_3 = 11;

void f4_4() {
    int y = x_4_3; // global x_4_3 : y = 11
    std::cout << y << std::endl;

    int x_4_3 = 22;
    y = x_4_3; // local x_4_3 : y = 22
    std::cout << y << std::endl;
}

void f4_5(int x) {
    // int x; // Error
}

void f4_6(std::vector<std::string> &v, std::list<int> &lst) {
    for (const auto &x : v) std::cout << x << std::endl;
    for (auto x : lst) std::cout << x << std::endl;
    for (int i = 0; i != v.size(); i++) std::cout << v[i] << std::endl;
    for (auto i : {1, 2, 3, 4}) std::cout << i << std::endl;
}

void execute4() {
    std::cout << "-----6.3.4 scope-----" << std::endl;
    f4_1();
    f4_2();
    f4_3();
    f4_4();
    f4_5(7);
    std::vector<std::string> v{"1st", "2nd"};
    std::list<int> lst{1, 2, 3};
    f4_6(v, lst);
}

//===--------------------------------------------------------------===//
// 6.3.5 Initialization
//===--------------------------------------------------------------===//

void f5_1(double val, int val2) {
    int x1 = val;   // x2 is 7
    char c1 = val2; // c2 is A
    std::cout << x1 << std::endl;
    std::cout << c1 << std::endl;

    // int x2{val}; // Error: possibility to round down
    // int c2{val2}; // Error: possibility to narrowing conversion

    char c3{24}; // OK
    // char c5{264}; // Error: 264 cannot conversion to char

    // int x3{2.0}; // Error: double cannot be narrowed to int
}

void f5_2() {
    auto z1{99}; // z1 is initializer_list<int>
    auto z2 = 99; // z2 is int

    std::vector<int> v1{99}; // v1 is vector that have single element
    std::vector<int> v2{99}; // v2 is vector that have 99's elements

    std::vector<std::string> v3{"hello"};
    // std::vector<std::string> v4("hello"); // Error: std::vector has not string literal constructor
}

void f5_3() {
    int x{}; // x is 0
    double d{}; // d is 0.0
    char *p{}; // p is nullptr
    std::vector<int> v{}; // v is empty vector
    std::string s{}; // s is ""
}

void f5_4() {
    int a[] = {1, 2}; // array initializer
    struct S {
        int x;
        std::string s;
    };
    S s = {1, "Helios"}; // struct initializer
    std::complex<double> z = {0, 1}; // use constructor
    std::vector<double> v = {0.0, 1.1, 2, 2}; // use list initializer
}

void execute5() {
    std::cout << "-----6.3.5 Initialization-----" << std::endl;
    f5_1(7.9, 1025);
    f5_2();
    f5_3();
    f5_4();
}

//===--------------------------------------------------------------===//
// 6.3.6 auto and decltype()
//===--------------------------------------------------------------===//

void f6_1() {
    int a1 = 123;
    char a2 = 123;
    auto a3 = 123; // a3 is int
}

template<typename T>
void f6_2(std::vector<T> &arg) {
    for (typename std::vector<T>::iterator p = arg.begin(); p != arg.end(); ++p)
        *p = 7;

    for (auto p = arg.begin(); p != arg.end(); ++p)
        *p = 7;
}

void f6_3(std::complex<double> d) {
    auto max = d + 7.0; // OK: max is complex<double>
    // double min = d - 9.0; // Error: it's assuming that d is scalar
}

void f6_4(std::vector<int> &v) {
    for (const auto &x : v) // x is const int&
        std::cout << x << std::endl;
}

void f6_5(int &v) {
    auto x = v; // x is int (is not int&)
    auto &y = v; // y is int&
    std::cout << &x << std::endl;
    std::cout << &y << std::endl;
}

void execute6() {
    std::cout << "-----6.3.6 auto and decltype()-----" << std::endl;
    f6_1();
    std::vector<int> v{1, 2, 3};
    f6_2(v);
    std::complex<double> c{0.0, 1.0};
    f6_3(c);
    std::vector<int> v2{1, 2, 3};
    f6_4(v2);
    int i = 3;
    std::cout << &i << std::endl;
    f6_5(i);
}

//===--------------------------------------------------------------===//

int main() {
    f();
    execute4();
    execute5();
    execute6();

    return 0;
}
