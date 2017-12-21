#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 12.2 argument
//===--------------------------------------------------------------===//

int *find(int *first, const int *last, int v) { // find v from [first:last)
    while (first != last && *first != v)
        ++first;

    return first;
}

void g(int *p, int *q) {
    int *pp = find(p, q, 'x');
    // ...
}

//===--------------------------------------------------------------===//
// 12.2.1 reference argument
//===--------------------------------------------------------------===//

void f1_1(int val, int &ref) {
    ++val;
    ++ref;
}

void f1_2() {
    int i = 1;
    int j = 1;
    f1_1(i, j);

    std::cout << i << std::endl; // 1
    std::cout << j << std::endl; // 2
}

void f1_3(const int &arg) {
    // can not change arg value
    // (unless use explicit type conversion
}

void update(float &i) {}

void f1_4(double d, float r) {
    // update(2.0f); // Error: const argument
    update(r);
    // update(d);    // Error: need type conversion
}

void f1_5(std::vector<int> &v) {}       // (non const) lvalue reference parameter
void f1_5(const std::vector<int> &v) {} // const lvalue reference  parameter
void f1_5(std::vector<int> &&v) {}      // rvalue reference parameter

void f1_6(std::vector<int> &vi, const std::vector<int> &cvi) {
    f1_5(vi);                           // call f1_5(std::vector<int> &)
    f1_5(cvi);                          // call f1_5(const std::vector<int> &)
    f1_5(std::vector<int>{1, 2, 3, 4}); // call f1_5(std::vector<int> &&)
}

void execute1() {
    std::cout << "-----12.2.1 reference argument-----" << std::endl;
    f1_2();
}

//===--------------------------------------------------------------===//
// 12.2.2 array argument
//===--------------------------------------------------------------===//

void f2_1() {
    char v[] = "Annemarie";
    size_t i = strlen(v);
    size_t j = strlen("Nicholas");

    std::cout << i << std::endl;
    std::cout << j << std::endl;
}

void f2_2(int(&r)[4]) {};

void f2_3() {
    int a1[] = {1, 2, 3, 4};
    int a2[] = {1, 2};

    f2_2(a1);    // OK
    // f2_1(a2); // Error: different element count
}

template<typename T, int N>
void f2_4(T(&r)[N]) {};

void f2_5() {
    int a1[10];
    double a2[100];
    f2_4(a1); // T is int. N is 10
    f2_4(a2); // T is double. N is 100
}

void execute2() {
    std::cout << "-----12.2.2 array argument-----" << std::endl;
    f2_1();
    f2_3();
    f2_5();
}

//===--------------------------------------------------------------===//
// 12.2.3 list argument
//===--------------------------------------------------------------===//
template<typename T>
void f3_1(std::initializer_list<T>) {}

struct S {
    int a;
    std::string s;
};

void f3_2(S) {}

void f3_4(int) {}

void f3_5() {
    f3_1({1, 2, 3, 4}); // T is int. initializer_list size() is 4
    f3_2({1, "MKS"});   // f3_2(S{1, "MKS"})
    f3_4({1});          // f3_4(int{1});
}

void execute3() {
    f3_5();
}

//===--------------------------------------------------------------===//
// 12.2.4 variable argument
//===--------------------------------------------------------------===//

void f4_1() {
    std::printf("My name is %d %s\n", 2);
}

extern void error(int, ...);

void f4_2(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            error(0, argv[0], nullptr);
            break;
        case 2:
            error(0, argv[0], argv[1], nullptr);
            break;
        default:
            error(1, argv[0], "with arguments", nullptr);
    }
}

#include <cstdarg>

void error(int severity, ...) {
    va_list ap;
    va_start(ap, severity);

    for (;;) {
        char *p = va_arg(ap, char*);
        if (p == nullptr)
            break;
        std::cerr << p << ' ';
    }

    va_end(ap);

    std::cerr << std::endl;
    if (severity)
        exit(severity);
}

void error(int severity, std::initializer_list<std::string> err) {
    for (auto &s : err)
        std::cerr << s << ' ';

    std::cerr << std::endl;

    if (severity)
        exit(severity);
}

void error(int severity, const std::vector<std::string> &err) {
    for (auto &s : err)
        std::cerr << s << ' ';

    std::cerr << std::endl;

    if (severity)
        exit(severity);
}

void execute4() {
    std::cout << "-----12.2.4 variable argument-----" << std::endl;
    f4_1();
}

//===--------------------------------------------------------------===//
// 12.2.5 default argument
//===--------------------------------------------------------------===//

class complex {
    double re, im;
public:
    complex(double r, double i) : re{r}, im{i} {}

    complex(double r) : re{r}, im{0} {}

    complex() : re{0}, im{0} {}

    // ...
};

class complex2 {
    double re, im;
public:
    complex2(double r, double i) : re{r}, im{i} {}

    complex2(double r) : complex2{r, 0} {}

    complex2() : complex2{0, 0} {}

    // ...
};

class complex3 {
    double re, im;
public:
    complex3(double r = {}, double i = {}) : re{r}, im{i} {}

    // ...
};

void f5_1(int x = 7);
// void f5_1(int = 7); // Error: can not repeat
// void f5_1(int = 8); // Error: can not changes value

void f5_2() {
    void f5_1(int x = 9); // OK : hide declaration in outer scope
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
