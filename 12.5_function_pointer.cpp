#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 12.5 function pointer
//===--------------------------------------------------------------===//

void error(std::string s) {
    std::cout << s << std::endl;
}

void (*efct)(std::string); // function pointer

void f1() {
    efct = &error; // efct points to error
    efct("error"); // call error(std::string) through efct
}

void (*f2)(std::string) = &error; // OK: same as = error
void (*f3)(std::string) = error;  // OK: same as = &error

void f4() {
    f2("Vasa");         // OK: same as (*f2)("Vasa")
    (*f2)("Mary Rose"); // OK: same as f2("Mary Rose")
}

void (*pf)(std::string);  // pointer to void(std::string)

void f5(std::string s) { std::cout << s << std::endl; } // void(std::string)

int f6(std::string s) {}  // int(std::string)

void f7(int *p) {}        // void(int*)

void f8() {
    pf = &f5;    // OK
    // pf = &f6; // Error: no match return type
    // pf = &f7  // Error: no match return type

    pf("Hera");  // OK
    // pf(1);    // Error:

    // int i = pf("Zeus"); // Error: assigned void to int
}

using P1 = int (*)(int *);
using P2 = void (*)(void);

void f9(P1 pf) {
    P2 pf2 = reinterpret_cast<P2>(pf);
    pf2(); // may be serious problem
    P1 pf1 = reinterpret_cast<P1>(pf2); // return to original
    int x = 7;
    int y = pf(&x); // OK
}

int f10(int *i) {
    std::cout << *i << std::endl;
    return *i;
}

struct User {
    const char *name;
    const char *id;
    int dept;
};

std::vector<User> heads = {
        {"Ritchie D.M.",   "dmr",  11271},
        {"Sethi R.",       "ravi", 11272},
        {"Szymanski T.G.", "tgs",  11273},
        {"Schryer N.L.",   "nls",  11274},
        {"Schryer N.L.",   "nls",  11275},
        {"Kernighan B.W.", "bwk",  11276},
};

void print_id(std::vector<User> &v) {
    for (auto &x : v)
        std::cout << x.name << '\t' << x.id << '\t' << x.dept << std::endl;
}

int cmp1(const void *p, const void *q) {// compare name
    return strcmp(static_cast<const User *>(p)->name,
                  static_cast<const User *>(q)->name);
}

int cmp2(const void *p, const void *q) {// compare dept
    return static_cast<const User *>(p)->dept
           - static_cast<const User *>(q)->dept;
}

int cmp3(const User *p, const User *q) {
    return strcmp(p->id, q->id);
}

void f11() {
    std::cout << "Heads in alphabetical order:" << std::endl;
    std::qsort(&heads[0], 6, sizeof(User), cmp1);
    print_id(heads);
    std::cout << std::endl;

    std::cout << "Heads in order of department number:" << std::endl;
    std::qsort(&heads[0], 6, sizeof(User), cmp2);
    print_id(heads);
}

void f12(int) noexcept {}

void f13(int) {}

void f14() {
    void (*p1)(int) = f12;             // OK: but lose valid information
    void (*p2)(int) noexcept = f12;    // OK: keep noexcept information
    // void (*p3)(int) noexcept = f13; // Error: don't know f13 does not throw exception
}

void execute() {
    std::cout << "-----12.5 function pointer-----" << std::endl;
    f1();
    std::cout << std::endl;
    f4();
    std::cout << std::endl;
    f8();
    std::cout << std::endl;
    P1 p = &f10;
    f9(p);
    std::cout << std::endl;
    f11();
    f14();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}
