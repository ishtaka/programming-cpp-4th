#include <iostream>

using namespace std;

//===--------------------------------------------------------------===//
// 18.1 introduction
//===--------------------------------------------------------------===//

class complex {     // very simplified complex
    double re, im;
public:
    complex(double r, double i) : re{r}, im{i} {}

    complex operator+(complex);

    complex operator*(complex);
};

complex complex::operator+(complex c) {
    return {re + c.re, im + c.im};
}

complex complex::operator*(complex c) {
    auto r = (re * c.re) - (im * c.im);
    auto i = (im * c.re) + (re * c.im);

    return complex(r, i);
}

void f() {
    complex a = complex{1, 3.1};
    complex b{1.2, 2};
    complex c{b};

    a = b + c;
    b = b + c * a;
    c = a * b + complex(1, 2);
}

void g(complex a, complex b) {
    a = {1, 2};            // OK: right hand side of assignment
    // b = a + {1, 2};     // syntax error
    b = a + complex{1, 2}; // OK
    g(a, {1, 2});          // OK: a function argument is considered an initializer
    // {a, b} = {b, a};    // syntax error
}

void execute() {
    f();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}
