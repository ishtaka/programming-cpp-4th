#include <iostream>
#include <vector>

using namespace std;

//===--------------------------------------------------------------===//
// 17.4.1 member initialization
//===--------------------------------------------------------------===//

struct Date {
    int d, m, y;
};

class Club {
    string name;
    vector<string> members;
    vector<string> officers;
    Date founded;

    // ...
public:
    Club(const string &n, Date fd);
};

Club::Club(const string &n, Date fd)
        : name{n}, founded{fd} { // member initializer list
    // ...
}

struct B {
    B(int);
};

struct BB : B {
    BB();
};

struct BBB : BB {
    // BBB(int i) : B(i) {} // Error: trying to initialize base’s base
};

//===--------------------------------------------------------------===//
// 17.4.1.1 member initialization and assignment
//===--------------------------------------------------------------===//

class X {
    const int i;
    Club cl;
    Club &rc;
    // ...
public:
    X(int ii, const string &n, Date d, Club &c) : i{ii}, cl{n, d}, rc{c} {}
};

class Person {
    string name;
    string address;
    // ...
public:
    Person(const Person &);

    Person(const string &n, const string &a);
};

Person::Person(const string &n, const string &a)
        : name{n} {
    address = a;
}

//===--------------------------------------------------------------===//
// 17.4.2 base initializer
//===--------------------------------------------------------------===//

class B1 {
public:
    B1() {} // has default constructor
};

class B2 {
public:
    B2(int i) {} // no default constructor
};

struct D1 : B1, B2 {
    D1(int i) : B1{}, B2{i} {}
};

struct D2 : B1, B2 {
    D2(int i) : B2{i} {} // B1{} is used implicitly
};

struct D3 : B1, B2 {
    // D3(int i) {} // Error: B2 requires an int initializer
    D3(int i) : B2{i} {}
};

//===--------------------------------------------------------------===//
// 17.4.3 delegating constructors
//===--------------------------------------------------------------===//

class X3 {
    int a;
    const int max = 100;
public:
    class Bad_X {
    };

    X3(int x) {
        if (0 < x && x <= max)
            a = x;
        else
            throw Bad_X();
    }

    X3() : X3{42} {}
    // X3() : X3{42}, a{56} {} // Error

    X3(string s) : X3{stoi(s)} {}
};

//===--------------------------------------------------------------===//
// 17.4.4  in-class initializers
//===--------------------------------------------------------------===//

class A1 {
public:
    int a{7};
    int b = 77;
};

class A2 {
public:
    int a;
    int b;

    A2() : a{7}, b{77} {}
};

class A3 {
public:
    A3() : a{7}, b{5} {}

    A3(int a_val) : a{a_val}, b{5} {}
    // ...
private:
    int a, b;
    string algorithm{"MD5"};
    string state{"Constructor run"};
};

class A4 {
public:
    A4() {}

    A4(int a_val) : a{a_val} {}
    // ...
private:
    int a{7};
    int b{5};
    string algorithm{"MD5"};
    string state{"Constructor run"};
};

int count1 = 0;
int count2 = 0;

int f4(int i) {
    return i + count1;
}

struct S {
    int m1{count2};   // ::count2
    int m2{f4(m1)};   // this->m1 + ::count1, ::count2 + ::count
    S() { ++count2; } // very odd constructor
};

int execute4() {
    S s1; // {0, 0}
    ++count1;
    S s2; // {1, 2}
}

//===--------------------------------------------------------------===//
// 17.4.5  static member initialization
//===--------------------------------------------------------------===//

class Node {
    // ...
    static int node_count; // declaration
};

int Node::node_count = 0; // definition

class Curious {
public:
    static const int c1 = 7;          // OK
    // static int c2 = 11;            // Error: not const
    const int c3 = 13;                // OK: but not static
    // static const int c4 = sqrt(9); // Error: in-class initializer not constant
    // static const float c5 = 7.0;   // Error: in-class not integral (use constexpr rather than const)
    // ...
};

const int Curious::c1;       // don’t repeat initializer here
const int *p = &Curious::c1; // OK: Curious::c1 has been defined

template<typename T, int N>
class Fixed {   // fixed-size array
public:
    static constexpr int max = N;
    // ...
private:
    T a[max];
};

class X5 {
    enum {
        c1 = 7, c2 = 11, c3 = 13, c4 = 17
    };
};

//===--------------------------------------------------------------===//

int main() {
    execute4();
    return 0;
}
