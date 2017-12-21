#include <iostream>
#include <complex>

//===--------------------------------------------------------------===//
// 12.2 function overloading
//===--------------------------------------------------------------===//

void print(int i) {
    std::cout << "print(int)" << std::endl;
}

void print(const char *c) {
    std::cout << "print(const char*)" << std::endl;
}

void execute() {
    std::cout << "-----12.2 function overloading-----" << std::endl;

    int i = 1;
    char c[] = "Test";
    print(i);
    print(c);
}

//===--------------------------------------------------------------===//
// 12.3.1 auto resolve of overload
//===--------------------------------------------------------------===//

void print1(double d) {
    std::cout << "print(double)" << std::endl;
}

void print1(long l) {
    std::cout << "print(long)" << std::endl;
}

void f1_1() {
    print1(1L);   // print(long)
    print1(1.0);  // print(double)
    // print1(1); // Error: ambiguous function call to print(long(1)) or print(double(1))
}

void print1(int i) {
    std::cout << "print(int)" << std::endl;
}

void print1(const char *c) {
    std::cout << "print(const char*)" << std::endl;
}

void print1(char c) {
    std::cout << "print(char)" << std::endl;
}

void f1_2(char c, int i, short s, float f) {
    print1(c);      // exact match: print(char)
    print1(i);      // exact match: print(int)
    print1(s);      // integral promotion: print(int)
    print1(f);      // promote from float to double: print(double)

    print1('a');    // exact match: print(char)
    print1(49);     // exact match: print(int)
    print1(0);      // exact match: print(int)
    print1("a");    // exact match: print(const char*)
    print(nullptr); // promote from nullptr_t to const char*: print(const char *)
}

void print_int(int i) {
    std::cout << "print_int " << i << std::endl;
}

void print_char(char c) {
    std::cout << "print_char " << c << std::endl;
}

void print_string(const char *c) { // C style string
    std::cout << "print_string " << c << std::endl;
}

void f1_3(char c, int i, const char *p, double d) {
    print_int(i);    // OK
    print_char(c);   // OK
    print_string(p); // OK

    print_int(c);       // OK? call print_int(int(c)).
    print_char(i);      // OK? call print_char(char(i)). narrowing conversion
    // print_string(i); // Error
    print_int(d);       // OK? call print_int(int(d)). narrowing conversion
}


void execute1() {
    std::cout << "-----12.3.1 auto resolve of overload-----" << std::endl;

    f1_1();
    std::cout << std::endl;

    char c = 'a';
    int i = 64;
    short s = 3;
    float f = 3.1;
    f1_2(c, i, s, f);
    std::cout << std::endl;

    char c2[] = "Test";
    double d = 3.2;
    f1_3(c, i, c2, d);
    std::cout << std::endl;
}

//===--------------------------------------------------------------===//
// 12.3.2 overloading and return type
//===--------------------------------------------------------------===//

float return_type(float f) {
    std::cout << "return_type(float)" << std::endl;
}

double return_type(double d) {
    std::cout << "return_type(double)" << std::endl;
}

void f2_1(double d, float f) {
    float f1 = return_type(d);  // call return_type(double)
    double d1 = return_type(d); // call return_type(double)
    f1 = return_type(f);        // call return_type(float)
    d1 = return_type(f);        // call return_type(float)
}

void execute2() {
    std::cout << "-----12.3.2 overloading and return type-----" << std::endl;

    double d = 3.2;
    float f = 5.6;
    f2_1(d, f);
}

//===--------------------------------------------------------------===//
// 12.3.3 overloading and scope
//===--------------------------------------------------------------===//

void f3_1(int i) {
    std::cout << "call f3_1(int)" << std::endl;
}

void f3_1(double d) {
    std::cout << "call f3_1(double)" << std::endl;
};

void f3_2() {
    void f3_1(double);
    f3_1(1);
}

struct Base {
    void f3_3(int);
};

void Base::f3_3(int) {
    std::cout << "call Base::f3_3(int)" << std::endl;
}

struct Derived : Base {
    void f3_3(double);
};

void Derived::f3_3(double) {
    std::cout << "call Derived::f3_3(double)" << std::endl;
}

void f3_4(Derived &d) {
    d.f3_3(1); // call Derived::f(double)
}


void execute3() {
    std::cout << "-----12.3.3 overloading and scope-----" << std::endl;

    f3_2();
    std::cout << std::endl;

    Derived d{};
    f3_4(d);
}

//===--------------------------------------------------------------===//
// 12.3.4 multiple arguments resolution
//===--------------------------------------------------------------===//

int f4(int i1, int i2) {
    std::cout << "call f4(int, int)" << std::endl;
    return 0;
}

double f4(double d1, double d2) {
    std::cout << "call f4(double, double)" << std::endl;
    return 1.2;
}

std::complex<double> f4(double d, std::complex<double> cx) {
    std::cout << "call f4(double, std::complex)" << std::endl;
    return cx;
}

std::complex<double> f4(std::complex<double> cx, int i) {
    std::cout << "call f4(std::complex, int)" << std::endl;
    return cx;
}

std::complex<double> f4(std::complex<double> cx1, std::complex<double> cx2) {
    std::cout << "call f4(std::complex, std::complex)" << std::endl;
    return cx1;
}

void f4_1(std::complex<double> z) {
    int i = f4(2, 2);          // call f4(int, int)
    double d1 = f4(2.0, 2.0);  // call f4(double, double)
    // double d2 = f4(2.0, 2); // Error: f4(int(2.0), 2) or f4(2.0, double(2))

    std::complex<double> z1 = f4(2, z); // call f4(double, std::complex);
    std::complex<double> z2 = f4(z, 2); // call f4(std::complex, int);
    std::complex<double> z3 = f4(z, z); // call f4(std::complex, std::complex);
}

void execute4() {
    std::cout << "-----12.3.4 multiple arguments resolution-----" << std::endl;

    std::complex<double> z{2.1, 3.2};
    f4_1(z);
}

//===--------------------------------------------------------------===//
// 12.3.5 manually resolve of overload
//===--------------------------------------------------------------===//

void f5_1(char c) {
    std::cout << "call f5_1(char)" << std::endl;
}

void f5_1(long l) {
    std::cout << "call f5_1(long)" << std::endl;
}

void f5_2(char *c) {
    std::cout << "call f5_2(char*)" << std::endl;
}

void f5_2(int *i) {
    std::cout << "call f5_2(int*)" << std::endl;
}

void f5_3(int i) {
    // f5_1(i); // ambiguous: f5_1(char) or f5_1(long)?
    // f5_2(0); // ambiguous: f5_2(char*) or f5_2(int*)?
}

inline void f5_1(int n) { f5_1(long(n)); }

void f5_4(int i) {
    f5_1(i);
    f5_2(static_cast<int*>(0));
}

void execute5() {
    std::cout << "-----12.3.5 manually resolve of overload-----" << std::endl;

    f5_4(3);
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute3();
    execute4();
    execute5();
    return 0;
}


