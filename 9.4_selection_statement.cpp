#include <iostream>

//===--------------------------------------------------------------===//
// 9.4.1 if statement
//===--------------------------------------------------------------===//

void f1_1() {
    int x = 1;
    if (x) {} // = if (x != 0) {}

    int *p = &x;
    if (p) {} // = if (p != nullptr) {}
}

enum E1 {
    a, b
};
enum class E2 {
    a, b
};

void f1_2(E1 x, E2 y) {
    if (x) {}          // OK
    // if (y) {}       // Error: no conversion to bool exists
    if (y == E2::a) {} // OK
}

int max(int a, int b) {
    return (a > b) ? a : b; // return larger of a and b
}

void f1_3(int i) {
    if (i) {
        int x = i + 2;
        ++x;
        std::cout << x << std::endl;
    } else {
        // ++x; // Error: x not exits in scope
    }
    // ++x; Error: x not exits in scope
}

void execute1() {
    std::cout << "-----9.4.1 if statement-----" << std::endl;

    f1_1();

    E1 e1 = a;
    E2 e2 = E2::b;
    f1_2(e1, e2);

    int a = 1, b = 3;
    std::cout << max(a, b) << std::endl; // 3

    int x = 4;
    f1_3(x);
}

//===--------------------------------------------------------------===//
// 9.4.2 switch statement
//===--------------------------------------------------------------===//

void f2_1(int i) {
    switch (i) {
        // case 2.7:   // Error: can't use float
        case 2:
            break;
        // case 4 - 2: // Error: duplicate case value '2'
    }
}

void f2_2() {
    int val = 1;
    switch (val) { // caution
        case 1:
            std::cout << "case 1" << std::endl; // fall through
        case 2:
            std::cout << "case 2" << std::endl;
        default:
            std::cout << "default: case not found" << std::endl;
    }
}

void execute2() {
    std::cout << "-----9.4.2 switch statement-----" << std::endl;
    f2_1(2);
    f2_2();
}

//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute2();
    return 0;
}
