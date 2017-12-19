#include <iostream>
#include <vector>
#include <complex>
#include <numeric>

//===--------------------------------------------------------------===//
// 11.3 list
//===--------------------------------------------------------------===//

struct S {
    int a, b;
};

struct SS {
    double a, b;
};

void f(S) {};

void g(S) {};

void g(SS) {}; // overload g()

void h() {
    f({1, 2});    // OK: f(S{1, 2})
    // g({1, 2}); // Error: ambiguous
    g(S{1, 2});   // OK: g(S)
    g(SS{1.2});   // OK: g(SS)
}

void execute() {
    h();
}

//===--------------------------------------------------------------===//
// 11.3.1 implementation model
//===--------------------------------------------------------------===//

void f1_1() {
    std::vector<double> v = {1, 2, 3.14};
    /*
    const double temp[] = {double{1}, double{2}, 3.14};
    const std::initializer_list<double> tmp(temp, sizeof(temp) / sizeof(double));
    std::vector<double> v(tmp);
    */
}

void f1_2() {
    std::initializer_list<int> lst{1, 2, 3};

    std::cout << *lst.begin() << std::endl;
    // *lst.begin() = 2; // Error: lst is immutable
    std::cout << *lst.begin() << std::endl;
}

void execute1() {
    std::cout << "-----11.3.1 implementation model-----" << std::endl;
    f1_1();
    f1_2();
}

//===--------------------------------------------------------------===//
// 11.3.2 qualify list
//===--------------------------------------------------------------===//

void f2_1() {
    S v{7, 8};          // direct initialization
    v = S{7, 8};        // assign by modification list
    S *p = new S{7, 8}; // allocate on heap by assign by modification list
}

template<typename T>
T square(T x) {
    return x * x;
}

void f2_2(double i) {
    double d = square(double{i});
    std::complex<double> z = square(std::complex<double>{i});
}

void execute2() {
    f2_1();
}

//===--------------------------------------------------------------===//
// 11.3.3 qualified list
//===--------------------------------------------------------------===//

int f3_1() {
    int v{7};        // initializer(direct)
    int v2 = {7};    // initializer(copy)
    int v3 = int{7};

    v = {8};         // right operand of assignment
    // {v} = 9;      // Error
    // v = 7 + {10}; // Error
    f2_2({7});       // argument

    return {11};
}

int high_value(std::initializer_list<int> val) {
    int high = std::numeric_limits<int>::lowest();
    if (val.size() == 0)
        return high;

    for (auto x : val)
        if (x > high) high = x;

    return high;
}

void f3_2() {
    int v1 = high_value({1, 2, 3, 4, 5, 6, 7});
    std::cout << v1 << std::endl;
    int v2 = high_value({-1, 2, v1, 4, -9, 20, v1});
    std::cout << v2 << std::endl;
}

void f3_3() {
    // auto x0 = {};       // Error
    auto x1 = {1};         // initializer_list<int>
    auto x2 = {1, 2};      // initializer_list<int>
    auto x3 = {1, 2, 3};   // initializer_list<int>
    // auto x4 = {1, 2.0}; // Error
}

void execute3() {
    std::cout << "-----11.3.3 qualified list-----" << std::endl;
    f3_2();
    f3_3();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute3();

    return 0;
}
