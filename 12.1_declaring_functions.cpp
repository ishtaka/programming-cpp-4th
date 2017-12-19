#include <iostream>
#include <cmath>
#include <complex>

//===--------------------------------------------------------------===//
// 12.1.3 function definition
//===--------------------------------------------------------------===//

double s2 = sqrt(2);          // double{2}
// double s3 = sqrt("three"); // Error: sqrt needs double

void swap(int *, int *); // declaration

void swap(int *p, int *q) { // definition
    int t = *p;
    *p = *q;
    *q = t;
}

void f(int);       // void(int)
void f(const int); // void(int)

void f(int x) {
    /* can change x */
}

int &max(int &a, int &b, int &c);

int &max(int &x1, int &x2, int &x3) {
    return (x1 > x2) ? ((x1 > x3) ? x1 : x3) : ((x2 > x3) ? x2 : x3);
}

void search(int *i, const char *key, const char *) {
    // do not use 3rd argument
}

void execute3() {
    std::cout << "-----12.1.3 function definition-----" << std::endl;
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    std::cout << max(x1, x2, x3) << std::endl;
}

//===--------------------------------------------------------------===//
// 12.1.4 return type
//===--------------------------------------------------------------===//

std::string to_string(int a);         // pre return type
auto to_string(int a) -> std::string; // post return type

template<typename T, typename U>
auto product(const std::vector<T> &x, const std::vector<U> &y) -> decltype(x);

// int f4_1() {} // Error: no return
void f4_2() {}   // OK

int f4_3() { return 1; }     // OK
// void f4_4() { return 1; } // Error: void function return value

// int f4_5() { return; } // Error: no return value
void f4_6() { return; }   // OK

int fac(int n) {
    return (n > 1) ? n * fac(n - 1) : 1; // recursive
}

int fac2(int n) {
    if (n > 1)
        return n * fac2(n - 1);

    return 1;
}

double d() {
    return 1; // implicit conversion to double{1}
}

int *fp() {
    int local = 1;
    // ...
    return &local; // No!
}

int &fr() {
    int local = 1;
    // ...
    return local; // No!
}

void f4_7(int *p) {};

void f4_8(int *p) {
    // ...
    return f4_7(p); // OK: same with "f4_7(p); return;"
}

void execute4() {
    std::cout << "-----12.1.4 return type-----" << std::endl;
    std::cout << fac(5) << std::endl;
}

//===--------------------------------------------------------------===//
// 12.1.5 inline function
//===--------------------------------------------------------------===//

inline int fac3(int n) {
    return (n < 2) ? 1 : n * fac3(n - 1);
}

//===--------------------------------------------------------------===//
// 12.1.6 constexpr function
//===--------------------------------------------------------------===//

constexpr int fac4(int n) {
    return (n > 1) ? n * fac4(n - 1) : 1;
}

constexpr int f6_1 = fac4(9); // must be evaluated at compile time

void f6_2(int n) {
    int f5 = fac4(5); // may be evaluated at compile time
    int fn = fac4(n); // evaluated at runtime(because n is variable)

    constexpr int f6 = fac4(6);     // must be evaluated at compile time
    // constexpr int fnn = fac4(n); // Error: because n is variable

    char a1[fac4(4)];    // OK: fac4() is constexpr
    // char a2[fac4(n)]; // error n is variable
}

/*
int glob;

constexpr void bad1(int a) { // Error: constexpr cannot be void
    glob = a; // error: constexpr has side effect
}

constexpr int bad2(int a) {
    if (a >= 0)   // Error: constexpr has if statement
        return a;
    else
        return -a;
}

constexpr int bad3(int a) {
    int sum = 0;                // Error: constexpr has local variable
    for (int i = 0; i < a; ++i) // Error: constexpr has loop
        sum += fac4(i);

    return sum;
}
*/

//===--------------------------------------------------------------===//
// 12.1.6.1 constexpr with reference
//===--------------------------------------------------------------===//

constexpr int ftbl[]{0, 1, 1, 2, 3, 5, 8, 13};

constexpr int fib(int n) {
    return (n < sizeof(ftbl) / sizeof(*ftbl)) ? ftbl[n] : fib(n - 2) + fib(n - 1);
}

constexpr std::complex<float> z{2.0};

constexpr const int *addr(const int &r) {
    return &r; // OK
}

static const int scx = 5;
constexpr const int *p1 = addr(scx); // OK
constexpr int xx = *p1;              // OK

static int sy;
constexpr const int *p2 = addr(sy);   // OK
// constexpr int yy = *p2;            // Error: read variable
// constexpr const int *tp = addr(5); // Error: temporary variable's address

//===--------------------------------------------------------------===//
// 12.1.6.2 condition evaluation
//===--------------------------------------------------------------===//

constexpr int low = 0;
constexpr int high = 99;

constexpr int check(int i) {
    return (low <= i && i < high) ? i : throw std::out_of_range("check() failed");
}

constexpr int val1 = check(50);     // OK
// constexpr int val2 = check(200); // throw exception

//===--------------------------------------------------------------===//
// 12.1.7 [[noreturn]] function
//===--------------------------------------------------------------===//

[[noreturn]]void exit1(int); // exit never return

//===--------------------------------------------------------------===//
// 12.1.8 local variable
//===--------------------------------------------------------------===//

void local_variable(int a) {
    while (a--) {
        static int n = 0; // initialize only once
        int x = 0; // initialized 'a' time for one function call

        std::cout << "n == " << n++ << ", x == " << x++ << std::endl;
        // n == 0, x == 0
        // n == 1, x == 0
        // n == 2, x == 0 ...
    }
}

int f8_1(int n) {
    static int n1 = n;                // OK;
    // static int n2 = fn(n - 1) + 1; // undefined

    return n;
}

void execute8() {
    std::cout << "-----12.1.8 local variable-----" << std::endl;
    local_variable(4);
    local_variable(2);

    std::cout << f8_1(3) << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute3();
    execute4();
    execute8();

    return 0;
}
