#include <iostream>

//===--------------------------------------------------------------===//
// 8.4.1 enum class
//===--------------------------------------------------------------===//

enum class Traffic_light {
    red,
    yellow,
    green
};

enum class Warning { // default underlying type is int
    green,
    yellow,
    orange,
    red
};

void f1_1() {
    // Warning a1 = 7;           // Error: no conversion from int to Warning
    // int a2 = green;           // Error: no green in scope
    // int a3 = Warning::green   // Error: no conversion from Waning to int
    Warning a4 = Warning::green; // OK
}

void f1_2(Traffic_light x) {
    // if (x) {}                    // Error: no implicit conversion to 0
    // if (x == 9) {}               // Error: 9 is not Traffic_light
    // if (x == red) {}             // Error: no red in scope
    // if (x == Warning::red)       // Error: x is not Warning
    if (x == Traffic_light::red) {} // OK
}

enum class Warning2 : int { // underlying type is int
    green,
    yellow,
    orange,
    red
}; // sizeof(Warning2) == sizeof(int)

enum class Warning3 : char { // underlying type is char
    green,
    yellow,
    orange,
    red
}; // sizeof(Warning3) == sizeof(char)

void f1_3() {
    std::cout << std::boolalpha << (sizeof(Warning) == sizeof(int)) << std::endl;
    std::cout << std::boolalpha << (sizeof(Warning2) == sizeof(int)) << std::endl;
    std::cout << std::boolalpha << (sizeof(Warning3) == sizeof(char)) << std::endl;
}

void f1_4() {
    std::cout << std::boolalpha << (static_cast<int>(Warning::green) == 0) << std::endl;
    std::cout << std::boolalpha << (static_cast<int>(Warning::yellow) == 1) << std::endl;
    std::cout << std::boolalpha << (static_cast<int>(Warning::orange) == 2) << std::endl;
    std::cout << std::boolalpha << (static_cast<int>(Warning::red) == 3) << std::endl;
}

void f1_5(Warning key) {
    switch (key) { // Warning: Not all switch cases were handled
        case Warning::green:
            std::cout << "Green" << std::endl;
            break;
        case Warning::orange:
            std::cout << "Orange" << std::endl;
            break;
        case Warning::red:
            std::cout << "Red" << std::endl;
            break;
    }
}

enum class Printer_flags {
    none = 0,
    acknowledge = 1,
    paper_empty = 2,
    busy = 4,
    out_of_black = 8,
    out_of_color = 16,
};

constexpr Printer_flags operator|(Printer_flags a, Printer_flags b) {
    return static_cast<Printer_flags>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr Printer_flags operator&(Printer_flags a, Printer_flags b) {
    return static_cast<Printer_flags>(static_cast<int>(a) & static_cast<int>(b));
}

void try_to_print(Printer_flags x) {
    if ((x & Printer_flags::acknowledge) != Printer_flags::none) {
        std::cout << "acknowledge" << std::endl;
    } else if ((x & Printer_flags::busy) != Printer_flags::none) {
        std::cout << "busy" << std::endl;
    } else if ((x & (Printer_flags::out_of_black | Printer_flags::out_of_color)) != Printer_flags::none) {
        std::cout << "out_of_black or out_of_color" << std::endl;
    }
}

void f1_6(Printer_flags x) {
    switch (x) {
        case Printer_flags::none:
            break;
        case Printer_flags::acknowledge:
            break;
        case Printer_flags::paper_empty:
            break;
        case Printer_flags::busy:
            break;
        case Printer_flags::out_of_black:
            break;
        case Printer_flags::out_of_color:
            break;
        case Printer_flags::out_of_black | Printer_flags::out_of_color:
            std::cout << "out_of_black or out_of_color" << std::endl;
            break;
    }
}

void execute1() {
    std::cout << "-----8.4.1 enum class-----" << std::endl;

    auto t = Traffic_light::red;
    f1_2(t);

    f1_3();
    f1_4();

    Warning w = Warning::red;
    f1_5(w);

    auto x = Printer_flags::acknowledge;
    auto y = Printer_flags::out_of_color;
    try_to_print(x);
    try_to_print(y);

    auto b = Printer_flags::out_of_black | Printer_flags::out_of_color;
    f1_6(b);
}

//===--------------------------------------------------------------===//
// 8.4.2 enum
//===--------------------------------------------------------------===//

enum Traffic_light_2 {
    red,
    yellow,
    blue,
};

enum Warning_2 {
    green,
    orange,
    // yellow, // Error: two yellow definition exists(same value)
    // red,    // Error: two red definition exists(different value)
};


void f2_1() {
    // Warning a1 = 7;               // Error: no conversion from int to Warning
    int a2 = green;                  // OK: green exists in scope, convert to int
    int a3 = Warning_2::green;       // OK: conversion from Warning to int
    Warning_2 a4 = Warning_2::green; // OK
}

void f2_2(Traffic_light_2 x) {
    if (x == 9) {}                   // OK (but 9 not exists in Traffic_light)
    // if (x == red) {}              // Error: two red exits in scope
    if (x == Warning_2::green) {     // OK (wrong)
        std::cout << "Warning_2::green" << std::endl;
    }
    if (x == Traffic_light_2::red) { // OK
        std::cout << "Traffic_light_2::red" << std::endl;
    }
}

void execute2() {
    std::cout << "-----8.4.2 enum-----" << std::endl;
    f2_1();

    auto x = Traffic_light_2::red;
    f2_2(x);
}

//===--------------------------------------------------------------===//
// 8.4.3 anonymous enum
//===--------------------------------------------------------------===//
enum {
    arrow_up = 1,
    arrow_down,
    arrow_sideways,
};

//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute2();
    return 0;
}
