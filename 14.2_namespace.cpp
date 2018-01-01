#include <iostream>

//===--------------------------------------------------------------===//
// 14.4 namespace
//===--------------------------------------------------------------===//

namespace Graph_lib {
    class Shape {
    };

    class Line : public Shape {
    };

    class Poly_line : public Shape {
    };

    class Text : public Shape {
    };

    Shape operator+(const Shape &, const Shape &);

    class Graph_reader {
    };

    Graph_reader open(const char *);
}

class Glyph {
};

class Line {
};

namespace Text_lib {
    class Glyph {
    };

    class Word {
    };

    class Line {
    };

    class Text {
    };

    Word operator+(const Line &, const Line &);

    FILE *open(const char *);
}

Glyph glyph(Line &ln, int i); // ln[i] ::Glyph, ::Line

Text_lib::Glyph glyph(Text_lib::Line &ln, int i);

//===--------------------------------------------------------------===//
// 14.2.1 explicit modify
//===--------------------------------------------------------------===//

namespace NamespaceName {
    // declaration and definition
}

namespace Parser {
    double expr(bool); // declaration
    double term(bool);

    double prim(bool);
}

double val = Parser::expr(true); // use

double Parser::expr(bool b) { // definition
    // ...
    return 0.0;
}

// void Parser::logical(bool); // Error: there is not logical() in Parser
// double Parser::trem(bool);  // Error: there is not trem() in Parser (typo)
// double Parser::prim(int);   // Error: Parser::prim() receives bool argument(type mismatch)

int f1_1() { // global function
    std::cout << "f1_1() is called" << std::endl;
    return 1;
};

int f1_2() {
    int f1_1;  // local variable: hides global function
    // f1_1(); // Error: it is impossible to call int variable
    ::f1_1();  // OK: call global function

    return 1;
}

void execute1() {
    std::cout << "-----14.2.1 explicit modify-----" << std::endl;
    f1_2();
}

//===--------------------------------------------------------------===//
// 14.2.2 using declaration
//===--------------------------------------------------------------===//

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split1(const std::string &s) { // split s into substrings delimited by space
    std::vector<std::string> res;
    std::istringstream iss(s);
    for (std::string buf; iss >> buf;)
        res.push_back(buf);

    return res;
}

using std::string; // use "string" for "std::string"

std::vector<string> split2(const string &s) { // split s into substrings delimited by space
    std::vector<string> res;
    std::istringstream iss(s);
    for (string buf; iss >> buf;)
        res.push_back(buf);

    return res;
}

namespace N {
    void f2(int i) {
        std::cout << "N::f2(int)" << std::endl;
    }

    void f2(std::string) {
        std::cout << "N::f2(std::string)" << std::endl;
    }
}

void f2_1() {
    using N::f2;
    f2(789);     // N::f2(int)
    f2("Bruce"); // N::f2(std::string);
}

void execute2() {
    std::cout << "-----14.2.2 using declaration-----" << std::endl;

    std::string str = "s p l i t";

    auto s1 = split1(str);
    for (const auto &s : s1)
        std::cout << s;
    std::cout << std::endl;

    auto s2 = split2(str);
    for (const auto &s : s2)
        std::cout << s;
    std::cout << std::endl;
    std::cout << std::endl;

    f2_1();
}

//===--------------------------------------------------------------===//
// 14.2.3 using directive
//===--------------------------------------------------------------===//

using namespace std;

vector<string> split3(const string &s) {
    vector<string> res;
    istringstream iss(s);
    for (string buf; iss >> buf;)
        res.push_back(buf);

    return res;
}

using namespace Graph_lib;
using namespace Text_lib;

// Text txt;                            // Error: ambiguous
// FILE *fp = open("my_precious_data"); // Error: ambiguous

void execute3() {
    std::cout << "-----14.2.3 using directive-----" << std::endl;

    std::string str = "s p l i t";
    auto s3 = split3(str);
    for (const auto &s : s3)
        std::cout << s;
    std::cout << std::endl;
}

//===--------------------------------------------------------------===//
// 14.2.4 argument dependent lookup (ADL)
//===--------------------------------------------------------------===//

namespace Chrono {
    class Date {
    };

    bool operator==(const Date &, const std::string &) {
        std::cout << "Chrono::operator== is called" << std::endl;
        return true;
    };

    std::string format(const Date &) {
        std::cout << "Chrono::format is called" << std::endl;
        return "Test";
    };
}

void f4_1(Chrono::Date d, int i) {
    std::string s = format(d);    // Chrono::format()
    // std::string t = format(i); // Error: format() is not in scope
}


void f4_2(Chrono::Date d, std::string s) {
    if (d == s) {
        // ...
    } else if (d == "August 4, 1914") {
        // ...
    }
}

namespace N4 {
    struct S {
        int i;
    };

    void f4_3(S);

    void g4_3(S) {
        std::cout << "N4::g4_3 is called" << std::endl;
    };

    void h4_3(int);
}

struct Base4 {
    void f4_3(N4::S) {
        std::cout << "Base4::f4_3 is called" << std::endl;
    };
};

struct D4 : Base4 {
    void mf(N4::S) {
        std::cout << "D4::mf is called" << std::endl;
    };

    void g4_3(N4::S x) {
        std::cout << "D4::g4_3 is called" << std::endl;
        f4_3(x);    // call Base4::f4_3()
        mf(x);      // D4::mf()
        // h4_3(1); // Error: h4_3(int) is not enable
    }
};

namespace N4_1 {
    template<typename T>
    void f4_4(T, int) { // N4_1::f4_4()
        std::cout << "N4_1::f4_4 is called" << std::endl;
    }

    class X {
    };
}

namespace N4_2 {
    N4_1::X x{};

    void f4_4(N4_1::X, unsigned) {
        std::cout << "N4_2::f4_4 is called" << std::endl;
    }

    void g4_4() {
        f4_4(x, 1); // call N4_1::f4_4(X, int)
    }
}

void execute4() {
    std::cout << "-----14.2.4 argument dependent lookup (ADL)-----" << std::endl;

    Chrono::Date d{};
    f4_1(d, 3);
    f4_2(d, "Test");
    std::cout << std::endl;

    N4::S s{};
    D4 d4{};

    g4_3(s);
    std::cout << std::endl;

    d4.g4_3(s);
    std::cout << std::endl;

    N4_2::g4_4();
}

//===--------------------------------------------------------------===//
// 14.2.5 namespace is open
//===--------------------------------------------------------------===//

namespace A {
    int f5(); // A has member f5()
}

namespace A {
    int g5(); // A has two members f5() and g5()
}

// my header
void mf(); // my function
void yf(); // your function
void mg(); // my function
// ...

// my header
namespace Mine {
    void mf(); // my function
    // ...
}

void yf(); // your function (not in namespace)

namespace Mine {
    int mg(); // my function
    // ...
}

//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute2();
    execute3();
    execute4();
    return 0;
}
