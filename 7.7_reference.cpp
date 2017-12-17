#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 7.7 reference
//===--------------------------------------------------------------===//

void f(std::vector<double> &v) {
    double d1 = v[1]; // copy v[1]
    v[2] = 7;

    v.push_back(d1);

    for (const auto x : v)
        std::cout << x << ' ';
    std::cout << std::endl;
}

void execute() {
    std::cout << "-----7.7 reference-----" << std::endl;
    std::vector<double> v{0.1, 0.2, 0.3};
    f(v);
}

//===--------------------------------------------------------------===//
// 7.7.1 lvalue reference
//===--------------------------------------------------------------===//

void f1_1() {
    int var = 1;
    int &r{var}; // r and var refer same int

    int x = r; // x become 1
    r = 2;     // var become 2
    std::cout << x << std::endl;
    std::cout << r << std::endl;
}

void f1_2() {
    int var = 1;
    int &r{var};    // OK: r1 has been initialized
    // int &r2;     // Error: not initialized
    extern int &r3; // OK: r3 should have been initialized other place
}

void f1_3() {
    int var = 0;
    int &rr{var};
    ++rr; // ++var
    int *pp = &rr; // *pp = &var

    std::cout << var << std::endl;
    std::cout << rr << std::endl;
    std::cout << *pp << std::endl;
}

void f1_4() {
    // double &dr = 1; // Error: need lvalue
    const double &cdr{1}; // OK
    /*
    double temp = double{1};
    const double &cdr{temp};
    */
}

void increment(int &aa) {
    ++aa;
}

int next(int p) {
    return p + 1;
}

void f1_5() {
    int x = 1;
    increment(x);
    std::cout << x << std::endl; // x = 2
    x = next(x);
    std::cout << x << std::endl; // x = 3
}

void execute1() {
    std::cout << "-----7.7.1 lvalue reference-----" << std::endl;
    f1_1();
    f1_2();
    f1_3();
    f1_4();
    f1_5();
}

//===--------------------------------------------------------------===//
// 7.7.2 rvalue reference
//===--------------------------------------------------------------===//

std::string f2_1() {
    return std::string("Test");
}

std::string f2_2(std::string &&s) {
    if (s.size())
        s[0] = static_cast<char>(toupper(s[0]));

    return s;
}

template<typename T>
void old_swap(T &a, T &b) {
    T tmp{a}; // two a's copies
    a = b;    // tow b's copies
    b = tmp;  // tow tmp's copies
}

template<typename T>
void swap(T &a, T &b) {
    T tmp{static_cast<T &&>(a)};
    a = static_cast<T &&>(b);
    b = static_cast<T &&>(tmp);
}

template<typename T>
void perfect_swap(T &a, T &b) {
    T tmp{std::move(a)};
    a = std::move(b);
    b = std::move(tmp);
}

void execute2() {
    std::cout << "-----7.7.2 rvalue reference-----" << std::endl;

    std::string var{"Cambridge"};
    std::string &r1{var};            // lvalue reference
    // std::string &r2{f2_1()};      // Error: f2_1() is rvalue
    // std::string &r3{"Princeton"}; // Error: lvalue reference

    std::string &&rr1{f2_1()};       // rvalue reference
    // std::string &&rr2{var};       // Error: var is lvalue
    std::string &&rr3{"Oxford"};     // OK

    const std::string &cr1{"Harvard"}; // OK

    int a = 3;
    int b = 5;
    swap<int>(a, b);
    std::cout << a << std::endl; // a = 5
    std::cout << b << std::endl; // b = 3
}

//===--------------------------------------------------------------===//
// 7.7.4 pointer and reference
//===--------------------------------------------------------------===//

void f4_1(char *p) {
    while (*p)
        std::cout << *p++;
    std::cout << std::endl;
}

void f4_2(char &r) {
    while (r)
        std::cout << r++; // Increment the reference char
    // maybe, infinite loop
    std::cout << std::endl;
}

void f4_3() {
    std::string x = "College Station";
    std::string y = "Manhattan";

    // std::string &a1[] = {x, y}; // Error: array of reference
    std::string *a2[] = {&x, &y};  // OK

    // std::vector<std::string&> s1 = {x, y}; // Error: vector of reference
    std::vector<std::string *> s2 = {&x, &y}; // OK
}

void execute4() {
    std::cout << "-----7.7.4 pointer and reference" << std::endl;
    char c[] = "Test";
    f4_1(c);
    f4_3();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute4();
    return 0;
}
