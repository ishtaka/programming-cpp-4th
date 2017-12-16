#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 7.3 array
//===--------------------------------------------------------------===//

void f() {
    int aa[10];
    aa[6] = 9;
    int x = aa[99]; // undefined
}

void f(int n) {
    int v1[n]; // Error: array elements is not const expression
    std::vector<int> v2(n); // OK
}

int a1[10]; // static

void f_2() {
    int a2[20]; // stack
    int *p = new int[40]; // heap
    delete[] p;
}

void execute() {
    std::cout << "-----7.3 array-----" << std::endl;
    float v[3]; // v[0], v[1], v[2]
    char *a[32]; // a[0]...a[31]

    f();
    f(3);
    f_2();
}

//===--------------------------------------------------------------===//
// 7.3.1 array initialization
//===--------------------------------------------------------------===//

void f1_1() {
    int v1[] = {1, 2, 3, 4}; // int[4]
    char v2[] = {'a', 'b', 'c', 0}; // char[4]
    std::cout << v2 << std::endl;

    // char v3[2] = {'a', 'b', 0}; // Error: to many initializer
    char v4[3] = {'a', 'b', 0}; // OK
    std::cout << v4 << std::endl;

    int v5[8] = {1, 2, 3, 4}; // == {1, 2, 3, 4, 0, 0, 0, 0};
    for (const auto i : v5)
        std::cout << i << ',';
    std::cout << std::endl;

    // int v6[8] = v5; // Error: array cannot copy
    int v6[8];
    // v6 = v5; // Error: cannot assignment
}

void execute1() {
    std::cout << "-----7.3.1 array initialization-----" << std::endl;
    f1_1();
}

//===--------------------------------------------------------------===//
// 7.3.2 string literal
//===--------------------------------------------------------------===//

void f2_1() {
    std::cout << std::boolalpha << (sizeof("Bohr") == 5) << std::endl; // const char[5] {'B', 'o', 'h', 'r', 0}
}

void f2_2() {
    // char *p = "Plato"; // Error: however, It's ok before C++11
    // p[4] = 'e'; // Error: assignment to const

    char p[] = "Zeno";
    p[0] = 'R'; // OK
    std::cout << p << std::endl;
}

const char *error_message(int i) {
    return "range error";
}

void f2_3() {
    const char *p = "Heraclitus";
    const char *q = "Heraclitus";
    if (p == q) // implementation-define. == compare pointer address
        std::cout << "one!" << std::endl;
}

void f2_4() {
    char alpha[] = "abcdef"
            "ABCDEF";
    std::cout << alpha << std::endl; // "abcdefABCDEF"
}

void execute2() {
    std::cout << "-----7.3.2 string literal-----" << std::endl;
    f2_1();
    f2_2();
    std::cout << error_message(0) << std::endl;
    f2_3();
    std::cout << "beep at end of message\a" << std::endl;
    f2_4();
}

//===--------------------------------------------------------------===//
// 7.3.2.1 raw string literal
//===--------------------------------------------------------------===//

void f2_1_1() {
    std::string s1 = "\\w+\\\\\\w+";
    std::string s2 = R"(\w+\\\w+)";
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}

void f2_1_2() {
    std::string counts1{"1\n22\n333"};
    std::string counts2{R"(1
22
333)"};
    std::cout << counts1 << std::endl;
    std::cout << counts2 << std::endl;
}

void execute2_1() {
    std::cout << "-----7.3.2.1 raw string literal-----" << std::endl;
    f2_1_1();
    f2_1_2();
}

//===--------------------------------------------------------------===//
// 7.3.2.1 raw string literal
//===--------------------------------------------------------------===//

void execute2_2() {
    std::cout << "-----7.3.2.1 raw string literal-----" << std::endl;
    "folder\\file"; // implementation-define string literal
    R"(folder\file)"; // implementation-define raw string literal
    u8"folder\\file"; // UTF-8 string literal
    u8R"(folder\file)"; // UTF-8 raw string literal
    u"folder\\file"; // UTF-16 string literal
    uR"(folder\file)"; // UTF-16 raw string literal
    U"folder\\file"; // UTF-32 string literal
    UR"(folder\file)"; // UTF-32 raw string literal
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute2_1();
    execute2_2();

    return 0;
}
