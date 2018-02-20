#include <iostream>

using namespace std;

//===--------------------------------------------------------------===//
// 18.3.1 member and nonmember operators
//===--------------------------------------------------------------===//

class complex {
    double re, im;
public:
    // complex() : re{0}, im{0} {}

    // complex(double r) : re{r}, im{0} {} // build a complex from a double

    constexpr complex(double r = 0, double i = 0) : re{r}, im{i} {}

    constexpr double real() const { return re; }

    constexpr double imag() const { return im; }

    void real(double r) { re = r; }

    void imag(double i) { im = i; }

    complex &operator+=(complex a); // needs access to representation
    complex &operator+=(double a);
    // -=, *=, /=
};

complex operator+(complex a, complex b) {
    return a += b; // access to representation through +=
}

inline complex &complex::operator+=(complex a) {
    re += a.re;
    im += a.im;

    return *this;
}

void f(complex x, complex y, complex z) {
    complex r1{x + y + z}; // r1 = operator+(operator+(x, y), z)

    complex r2{x}; // r2 = x
    r2 += y;       // r2.operator+=(y)
    r2 += z;       // r2.operator+=(z)
}

//===--------------------------------------------------------------===//
// 18.3.2 mixed-mode arithmetic
//===--------------------------------------------------------------===//

inline complex &complex::operator+=(double a) {
    re += a;

    return *this;
}

complex operator+(complex a, double b) {
    return {a.real() + b, a.imag()};
}

complex operator+(double a, complex b) {
    return {a + b.real(), b.imag()};
}

void f2(complex x, complex y) {
    auto r1 = x + y; // call operator+(complex, complex)
    auto r2 = x + 2; // call operator+(complex, double)
    auto r3 = 2 + x; // call operator+(double, complex)
    auto r4 = 2 + 3; // built-in integer addition
}

//===--------------------------------------------------------------===//
// 18.3.3 conversions
//===--------------------------------------------------------------===//

complex b{3}; // should mean b.re = 3, b.im = 0

void comp(complex x) {
    x = 4; // should mean x.re = 4, x.im = 0
}

void f3() {
    complex z;
    complex x{1, 2};
    complex y{x};    // y also has the value {1, 2}
    z = x;           // z also has the value {1, 2}
}

//===--------------------------------------------------------------===//
// 18.3.3.1 conversions of operands
//===--------------------------------------------------------------===//

bool operator==(complex a, complex b) {
    return a.real() == b.real()
           && a.imag() == b.imag();
}

void f3_1_1(complex x, complex y) {
    x == y; // means operator==(x, y)
    x == 3; // means operator==(x, complex(3))
    3 == y; // means operator==(complex(3), y)
}

void f3_1_2(complex z) {
    3 + z;              // OK: complex(3) + z
    // 3.operator+=(z); // Error: 3 is not a class object
    // 3 += z;          // Error: 3 is not a class object
}

//===--------------------------------------------------------------===//
// 18.3.4 literals
//===--------------------------------------------------------------===//

complex z1{1.2, 12e3};
constexpr complex z2{1.2, 12e3}; // guaranteed compile-time initialization

constexpr complex operator "" i(long double d) {
    return {0, static_cast<double>(d)};
}

complex z3{1.2 + 12e3i};

complex f4_1(double d) {
    auto x{2.3i};
    return x + 12e3i;
}

complex z4{1.2, 12e3};

complex f4_2(double d) {
    complex x{0, 2.3};
    return x + complex{0, 12e3};
}

//===--------------------------------------------------------------===//
// 18.3.6 helper functions
//===--------------------------------------------------------------===//

complex operator+(complex, complex);

complex operator+(complex, double);

complex operator+(double, complex);

// binary -, *, and /

complex operator-(complex); // unary minus
complex operator+(complex); // unary plus

bool operator==(complex, complex);

bool operator!=(complex, complex);

istream &operator>>(istream &, complex &); // input
ostream &operator<<(ostream &, complex);   // output

complex polar(double rho, double theta);

complex conj(complex);

double abs(complex);

double arg(complex);

double norm(complex);

double real(complex); // for notational convenience

double imag(complex); // for notational convenience

complex acos(complex);

complex asin(complex);

complex atan(complex);
// ...

//===--------------------------------------------------------------===//

int main() {
    return 0;
}
