#include <iostream>

//===--------------------------------------------------------------===//
// 11.5 explicit conversion
//===--------------------------------------------------------------===//

void f1() {
    double d = 1234567890; // int to double
    int i = d;             // double to int

    std::cout << d << std::endl;
    std::cout << i << std::endl;
}

template<typename Target, typename Source>
Target narrow_cast(Source v) {
    auto r = static_cast<Target>(v);
    if (static_cast<Source>(r) != v)
        throw std::runtime_error("narrow_cast<>() failed");

    return r;
};

void f2() {
    auto c1 = narrow_cast<char>(64);
    std::cout << c1 << std::endl;

    auto d1 = narrow_cast<double>(1 / 3.0F);
    std::cout << d1 << std::endl;
}

void execute() {
    std::cout << "-----11.5 explicit conversion-----" << std::endl;
    f1();
    f2();
}

//===--------------------------------------------------------------===//
// 11.5.1 construction
//===--------------------------------------------------------------===//

void f1_1() {
    auto d1 = double{2};      // d1 == 2.0
    double d2{double{2} / 4}; // d2 == 0.5
    std::cout << d1 << std::endl;
    std::cout << d2 << std::endl;
}

void f1_2(char *p) {
    // int x = int{p}; // Error: no conversion from char* to int

    using Pint = int *;
    // int *p2 = Pint{p}; // Error: no conversion from char* to int
}

void execute1() {
    f1_1();
    char c[] = "Test";
    f1_2(c);
}

//===--------------------------------------------------------------===//
// 11.5.2 casting
//===--------------------------------------------------------------===//

void f2_1() {
    char x = 'a';
    // int *p1 = &x;                       // Error: no implicit conversion from char* to int*
    // int *p2 = static_cast<int*>(&x);    // Error: no implicit conversion from char* to int*
    int *p3 = reinterpret_cast<int *>(&x); // OK: but take responsibility on your own!

    std::cout << *p3 << std::endl;

    struct B {
    };
    struct D : B {
    };

    B *pb = new D;               // OK :
    // D *pd = pb;               // Error: no implicit conversion from B* to D*
    D *pd = static_cast<D*>(pb); // OK
}

void execute2() {
    std::cout << "-----11.5.2 casting-----" << std::endl;
    f2_1();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();

    return 0;
}
