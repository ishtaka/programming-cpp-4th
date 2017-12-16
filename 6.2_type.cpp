#include <iostream>

//===--------------------------------------------------------------===//
// 6.2.2 bool data type
//===--------------------------------------------------------------===//

void print_bool(bool b) {
    std::cout << std::boolalpha << b << std::endl;
}

void f2_1(int a, int b) {
    bool b1{a == b};
    print_bool(b1);
}

void f2_2() {
    bool b1 = 7; // true
    // bool b2{7}; // Error: narrowing conversion
    print_bool(b1);

    int i1 = true; // i1 is 1
    int i2{true};  // i2 is 1
    std::cout << i1 << std::endl;
    std::cout << i2 << std::endl;
}

void f2_3(int i) {
    bool b2{i != 0};
    print_bool(b2); // true
}

void f2_4() {
    bool a = true;
    bool b = true;

    bool x = a + b; // a + b = 2,  x = true
    bool y = a || b; // a || b = true, y = true
    bool z = a - b; // a - b = 0, z = false;

    print_bool(x);
    print_bool(y);
    print_bool(z);
}

void f2_5(int *p) {
    bool b1 = p; // narrowing conversion to true or false
    bool b2{p != nullptr};

    print_bool(b1);
    print_bool(b2);
}

void execute2() {
    std::cout << "-----6.2.2 bool data type-----" << std::endl;
    f2_1(1, 1); // true
    f2_1(1, 2); // false

    f2_2();

    f2_3(7); // true
    f2_3(0); // false

    int i = 3;
    int *p1 = &i;
    int *p2 = nullptr;
    f2_5(p1); // true, true
    f2_5(p2); // false, false
}

//===--------------------------------------------------------------===//
// 6.2.3 string data type
//===--------------------------------------------------------------===//

void intval() {
    std::string str;
    std::cin >> str;

    for (char c: str)
        std::cout << "The value of '" << c << "' is " << int{c} << std::endl;
}

void digits() {
    for (int i = 0; i != 10; ++i)
        std::cout << static_cast<char>('0' + i);

    std::cout << std::endl;
}

void f3_1() {
    char c = 255;
    int i = c; //
    std::cout << i << std::endl;
}

void f3_2(char c, signed char sc, unsigned char uc) {
    // char *pc = &uc; error
    // signed char *psc = pc; error
    // unsigned char *puc = pc; error
    // psc = puc; error
}

void f3_3(char c, signed char sc, unsigned char uc) {
    c = 255; // implementation defined
    c = sc; // OK
    c = uc; // if char is signed and uc is bigger than it, implementation defined

    sc = uc; // if uc is bigger than signed, implementation defined
    uc = sc; // OK
    sc = c; // if char is signed and c is bigger than it, implementation defined
    uc = c; // OK
}

void f3_4() {
    signed char sc = -140;
    unsigned char uc = sc; // uc = (256 - 140) = 116
    std::cout << uc << std::endl; // 't'

    char count[256]; // assume that char is 8 bit
    char c1 = count[sc]; // out of range
    char c2 = count[uc]; // OK
}

void execute3() {
    std::cout << "-----6.2.3 string data type-----" << std::endl;
    intval();
    digits();

    f3_1();
    f3_4();
}

//===--------------------------------------------------------------===//
// 6.2.4 numeric data type
//===--------------------------------------------------------------===//

void execute4() {
    std::cout << "-----6.2.4 numeric data type-----" << std::endl;
    std::cout << "size of long " << sizeof(1L) << std::endl;
    std::cout << "size of long long " << sizeof(1LL) << std::endl;

    std::cout << "largest float ==  " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "char is signed ==  " << std::numeric_limits<char>::is_signed << std::endl;

    int16_t x{static_cast<int16_t>(0xaabb)}; // 2byte
    std::cout << "size of int16_t " << sizeof(x) << std::endl;

    int64_t xxxx{static_cast<int64_t>(0xaaaabbbbccccdddd)}; // 8byte
    std::cout << "size of int64_t " << sizeof(xxxx) << std::endl;

    std::cout << alignof(char) << std::endl;
    std::cout << alignof(int) << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute2();
    execute3();
    execute4();

    return 0;
}
