#include <iostream>

using namespace std;

//===--------------------------------------------------------------===//
// 18.4.1 conversion operators
//===--------------------------------------------------------------===//

class Tiny {
    char v;

    void assign(int i) {
        if (i & ~077)
            throw Bad_range();
        v = i;
    }

public:
    class Bad_range {
    };

    Tiny(int i) { assign(i); }

    Tiny &operator=(int i) {
        assign(i);
        return *this;
    }

    operator int() const; // conversion to int function
};

Tiny::operator int() const { // right
    return v;
}

// int Tiny::operator int() const { return v; } // Error

void f1_1() {
    Tiny c1 = 2;
    Tiny c2 = 62;
    Tiny c3 = c2 - c1; // c3 = 60
    Tiny c4 = c3;      // no range check (not necessary)
    int i = c1 + c2;   // i = 64;
    cout << c3 << endl;
    cout << i << endl;
    cout << endl;

    // c1 = c1 + c2;   // range error: c1 can’t be 64
    i = c3 - 64;       // i = -4
    // c2 = c3 - 64;   // range error: c2 can't be -4
    c3 = c4;           // no range check (not necessary)
    cout << i << endl;
    cout << c3 << endl;
}

int operator+(Tiny a, Tiny b) {
    return a + b;
}

void f1_2(Tiny t, int i) {
    // t + i; // Error: ambiguous: "operator+(t,Tiny(i))" or "int(t)+i" ?
}

void execute1() {
    cout << "-----18.4.1 conversion operators-----" << endl;
    f1_1();
}

//===--------------------------------------------------------------===//
// 18.4.2 explicit conversion operators
//===--------------------------------------------------------------===//

void use(unique_ptr<Tiny> p, unique_ptr<int> q) {
    if (!p) // OK: we want this use
        throw invalid_argument{""};

    // bool b = p;    // Error ; suspicious use
    // int x = p + q; // Error; we definitely don’t want this
}

//===--------------------------------------------------------------===//
// 18.4.3 ambiguities
//===--------------------------------------------------------------===//

class X {
public:
    X(int i) {}

    X(const char *c) {}
};

class Y {
public:
    Y(int i) {}
};

class Z {
public:
    Z(X x) {}
};

X f3(X x) {
    return x;
}

Y f3(Y y) {
    return y;
}

Z g3(Z z) {
    return z;
}

void f3_1() {
    // f3(1); // Error: ambiguous f3(X(1)) or f3(Y(1)) ?
    f3(X{1}); // OK
    f3(Y{1}); // OK

    // g3("Mack"); // Error: g3(Z{X{"Mack"}) is needed
    g3(X{"Doc"});  // OK: g3(Z{X{"Doc"}})
    g3(Z{"Suzy"}); // OK: g3(Z{X{"Suzy"}})
}

class XX {
    XX(int i);
};

void h3(double d) {
    cout << "call h3(double)" << endl;
}

void h3(XX xx) {
    cout << "call h3(XX)" << endl;
}

void f3_2() {
    h3(1); // h(double{1}) or h(XX{1})? h(double{1})!
}

class Quad {
public:
    Quad(double d) {}
};

Quad operator+(Quad a, Quad b) {
    cout << "call Quad operator+(Quad, Quad)" << endl;
    return a;
}

void f3_3(double a1, double a2) {
    Quad r1 = a1 + a2;       // double-precision floating-point add
    Quad r2 = Quad{a1} + a2; // force Quad arithmetic
}

class Real {
    int i;
public:
    Real(int i) : i{i} {}

    operator double() const {
        cout << "call Real.double()" << endl;
        return i;
    };

    operator int() const {
        cout << "call Real.int()" << endl;
        return i;
    };
    // ...
};

void f3_4(Real a) {
    double d = a; // d = a.double();
    int i = a;    // i = a.int();

    d = a; // d = a.double();
    i = a; // i = a.int();
}

void execute3() {
    cout << "-----18.4.3 ambiguities-----" << endl;
    f3_1();
    f3_2();
    f3_3(1, 1);
    f3_4(1);
}

//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute3();
    return 0;
}
