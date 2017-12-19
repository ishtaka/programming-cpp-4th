#include <iostream>
#include <cfloat>

//===--------------------------------------------------------------===//
// 10.5.2 conversion
//===--------------------------------------------------------------===//

void f2_1(double d) {
    char c = d;   // Caution: convert double into char(narrowing conversion)
    // char c{d}; // Error: convert double into char
    std::cout << c << std::endl;
}

void execute2() {
    std::cout << "-----10.5.2 conversion-----" << std::endl;
    f2_1(64.2);
}

//===--------------------------------------------------------------===//
// 10.5.2.1 integral conversion
//===--------------------------------------------------------------===//

void execute2_1() {
    std::cout << "-----10.5.2.1 integral conversion-----" << std::endl;

    unsigned char uc = 1023; // binary:11111111 = 255
    std::cout << std::bitset<8>(uc) << std::endl;
    std::cout << static_cast<int>(uc) << std::endl;

    signed char sc = 1023; // implementation-defined
    std::cout << std::bitset<8>(sc) << std::endl;
    std::cout << static_cast<int>(sc) << std::endl;
}

//===--------------------------------------------------------------===//
// 10.5.2.2 float conversion
//===--------------------------------------------------------------===//

void execute2_2() {
    std::cout << "-----10.5.2.2 float conversion-----" << std::endl;

    float f = FLT_MAX; // maximum float value
    double d = f;      // OK: d == f
    std::cout << d << std::endl;

    double d2 = DBL_MAX; // maximum double value
    float f2 = d2;       // undefined if FLT_MAX < DBL_MAX
    std::cout << f2 << std::endl;

    long double ld = d2; // OK: ld == d2
    long double ld2 = std::numeric_limits<long double>::max();
    double d3 = ld2;     // undefined if sizeof(long double> > sizeof(double>
    std::cout << ld << std::endl;
    std::cout << d3 << std::endl;
}

//===--------------------------------------------------------------===//
// 10.5.2.5 bool conversion
//===--------------------------------------------------------------===//

void f5_1(int *p, int i) {
    bool is_not_zero = p; // true if p != 0
    bool b2 = i;          // true if i != 0

    std::cout << std::boolalpha << is_not_zero << std::endl;
    std::cout << std::boolalpha << b2 << std::endl;
}

void fi(int i) {};

void fb(bool b) {};

void f5_2(int *p, int *q) {
    if (p)
        std::cout << "do something *p" << std::endl;
    if (q != nullptr)
        std::cout << "do something *q" << std::endl;

    //fi(p); // Error: no conversion point to int
    fb(p);   // OK: convert point to bool
}

void execute2_5() {
    std::cout << "-----10.5.2.5 bool conversion-----" << std::endl;

    int x = 2;
    int y = 3;
    f5_1(&x, x);
    f5_2(&x, &y);
}

//===--------------------------------------------------------------===//
// 10.5.2.6 conversion between float and int
//===--------------------------------------------------------------===//

void execute2_6() {
    std::cout << "-----10.5.2.6 conversion between float and int-----" << std::endl;

    int i = 2.7; // i = 2;
    std::cout << i << std::endl;

    char b = 2000.7; // undefined in 8bit char

    int i2 = float(1234567890); // 1234567936
    std::cout << i2 << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute2();
    execute2_1();
    execute2_2();
    execute2_5();
    execute2_6();

    return 0;
}
