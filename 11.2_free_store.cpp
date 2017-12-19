#include <iostream>
#include <complex>
#include <vector>

//===--------------------------------------------------------------===//
// 11.2 free store
//===--------------------------------------------------------------===//

void execute() {
    std::cout << "-----11.2 free store-----" << std::endl;

    // int *p = new int = 7; // Error

    auto pc1 = new std::complex<double>; // {0, 0}
    auto pi1 = new int;                  // not initialized

    auto pc2 = new std::complex<double>{}; // {0, 0}
    auto pi2 = new int {};                 // 0
    std::cout << *pi2 << std::endl;
}

//===--------------------------------------------------------------===//
// 11.2.1 memory management
//===--------------------------------------------------------------===//

void f1_1() {
    int *p1 = new int {99};
    int *p2 = p1;              // potential problem
    delete p1;                 // p2 is no longer a pointer to the correct object
    p1 = nullptr;
    char *p3 = new char {'x'}; // p3 point to memory pointed to by p2
    *p2 = 999;
    std::cout << *p3 << std::endl; // does not mean that display x
}

void sloppy() { // wrong code
    int *p = new int {1000}; // allocate memory
    // use *p
    delete[] p;

    // do something

    delete[] p; // sloppy doesn't have own *p
}

void f1_2(const std::string &s) {
    std::vector<char> v;
    for (auto c : s)
        v.push_back(c);

    for (auto c : v)
        std::cout << c;
    std::cout << std::endl;
}

std::string reverse(const std::string &s) {
    std::string ss;
    for (int i = s.size() - 1; 0 <= i; --i)
        ss.push_back(s[i]);

    return ss;
}

void f1_3(int n) {
    int *p1 = new int {n};
    std::unique_ptr<int[]> p2{new int[n]};
    // ...
    if (n % 2)
        throw std::runtime_error("odd");

    delete[] p1; // there is a possibility not to reach
}

void execute1() {
    std::cout << "-----11.2.1 memory management-----" << std::endl;
    f1_1();

    std::string s = "Test";
    f1_2(s);
    std::cout << reverse(s) << std::endl;
}

//===--------------------------------------------------------------===//
// 11.2.2 array
//===--------------------------------------------------------------===//

char *save_string(const char *p) {
    char *s = new char[strlen(p) + 1];
    strcpy(s, p); // copy from p to s

    return s;
}

std::string save_string2(const char *p) {
    return std::string{p};
}

void f2_1(int n) {
    auto *p = new std::vector<int>(n); // single object
    auto *q = new int[n];              // array
    // ...
    delete p;
    delete[] q;
}

void execute2() {
    char c[] = "Test";
    char *p = save_string(c);
    std::cout << p << std::endl;
    // ...
    delete[] p;

    std::string s = save_string2(c);
    std::cout << s << std::endl;
    // ...

    f2_1(3);
}

//===--------------------------------------------------------------===//
// 11.2.3 memory allocate
//===--------------------------------------------------------------===//

void f3_1() {
    std::vector<char *> v;
    try {
        for (;;) {
            char *p = new char[10000]; // allocate memory
            v.push_back(p);            // assume that refer new memory
            p[0] = 'x';                // use new memory
        }
    } catch (std::bad_alloc) {
        std::cerr << "Memory exhausted!" << std::endl;
    }
}

//===--------------------------------------------------------------===//
// 11.2.4 overloading of new
//===--------------------------------------------------------------===//

class X {
public:
    X(int);
    // ...
};

class Arena {
public:
    virtual void *alloc(size_t) = 0;

    virtual void free(void *) = 0;
    // ...
};

void *operator new(size_t sz, Arena *a) {
    return a->alloc(sz);
}

/*
extern Arena *Persistent;
extern Arena *Shared;

void f4_1(int i) {
    X *p = new(Persistent) X(i); // allocate to persistent storage
    X *q = new(Shared) X(i);     // allocate to shared storage
}
*/

void destroy(X *p, Arena *a) {
    p->~X();
    a->free(p);
}

//===--------------------------------------------------------------===//
// 11.2.4.1 nothrow new
//===--------------------------------------------------------------===//

void f4_1_1(int n) {
    int *p = new(std::nothrow) int[n];
    if (p == nullptr) { // memory shortage
        // ... error handle
    }

    operator delete(p, std::nothrow); // free *p
}

void execute4_1() {
    f4_1_1(2);
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute4_1();

    return 0;
}
