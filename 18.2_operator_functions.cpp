#include <iostream>
#include <array>

using namespace std;

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

//===--------------------------------------------------------------===//
// 18.2 operator functions
//===--------------------------------------------------------------===//

void f(complex a, complex b) {
    complex c = a + b;          // short hand
    complex d = a.operator+(b); // explicit call
}

//===--------------------------------------------------------------===//
// 18.2.1 binary and unary operators
//===--------------------------------------------------------------===//

class X1 {
    int i;
public:
    X1(int ii) : i{ii} {};

    void operator+(int i) {
        cout << "X1.operator+(int)" << endl;
    }
};

void operator+(X1 a, X1 b) {
    cout << "::operator+(X1, X1)" << endl;
}

void operator+(X1, double) {
    cout << "::operator+(X1, double)" << endl;
}

void f1_1(X1 a) {
    a + 1;   // a.operator+(1)
    1 + a;   // ::operator+(X1(1), a)
    a + 1.0; // ::operator+(a, 1.0)
}

class X2 {
public:  // members (with implicit this pointer)
    X2 *operator&();         // prefix unary & (address of)
    X2 operator&(X2);        // binary & (and)
    X2 operator++(int);      // postfix increment
    // X2 operator&(X2, X2); // Error: can't define ternary operator
    // X2 operator/();       // Error: / operator is not unary
};

// nonmember functions
X2 operator-(X2);            // prefix unary minus
X2 operator-(X2, X2);        // binary minus
X2 operator--(X2 &, int);    // postfix decrement
// X2 operator-();           // Error: no operand
// X2 operator-(X2, X2, X2); // Error: can't define ternary operator
// X2 operator%(X2);         // Error: % operator is not unary


void execute1() {
    cout << "-----18.2.1 binary and unary operators-----" << endl;
    X1 x1{1};
    f1_1(x1);
}

//===--------------------------------------------------------------===//
// 18.2.2 predefined meanings for operators
//===--------------------------------------------------------------===//

class X3 {
public:
    // ...
    void operator=(const X3 &) = delete;

    void operator&() = delete;

    void operator,(const X3 &) = delete;
    // ...
};

void f2_1(X3 a, X3 b) {
    // a = b; // Error: no operator=()
    // &a;    // Error: no operator&()
    // a, b;  // Error: no operator,()
}

//===--------------------------------------------------------------===//
// 18.2.3 operators and user-defined types
//===--------------------------------------------------------------===//

enum Day {
    sun, mon, tue, wed, thu, fri, sat,
};

Day &operator++(Day &d) {
    return d = (sat == d) ? sun : static_cast<Day>(d + 1);
}

//===--------------------------------------------------------------===//
// 18.2.4 passing Objects
//===--------------------------------------------------------------===//

struct Point { // small object
    // ...
    void operator+=(Point);
};

void Point::operator+=(Point delta) {} // pass by value

struct Matrix { // large object
    array<int, 2> dim;
    double *elem;
public:
    Matrix(int d1, int d2) : dim{d1, d2}, elem{new double[d1 * d2]} {}

    Matrix &operator+=(const Matrix &);

    ~Matrix() { delete[] elem; }
};

Matrix operator+(const Matrix &, const Matrix &);    // pass by const reference
Matrix operator+(const Matrix &a, const Matrix &b) { // return by value
    Matrix res = a + b;

    return res;
}

Matrix &Matrix::operator+=(const Matrix &a) { // return by value
    if (dim[0] != a.dim[0] || dim[1] != a.dim[1])
        throw runtime_error("bad Matrix += argument");

    double *p = elem;
    double *q = a.elem;
    double *end = p + dim[0] * dim[1];

    while (p != end)
        *p++ += *q++;

    return *this;
}

//===--------------------------------------------------------------===//
// 18.2.5 operators in namespaces
//===--------------------------------------------------------------===//

struct X5 {
};

X5 operator!(X5);

struct Z5 {
    Z5 operator!();             // does not hide ::operator!()

    X5 f(X5 x) { return !x; }   // invoke ::operator!(X5)

    int f(int x) { return !x; } // invoke the built-in ! for ints
};

//===--------------------------------------------------------------===//

int main() {
    execute1();
    return 0;
}
