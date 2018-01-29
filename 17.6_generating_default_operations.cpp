#include <iostream>
#include <valarray>
#include <vector>

using namespace std;

//===--------------------------------------------------------------===//
// 17.6.1 explicit defaults
//===--------------------------------------------------------------===//

class gslice1 {
    valarray<size_t> size;
    valarray<size_t> stride;
    valarray<size_t> dl;
public:
    gslice1() = default;

    ~gslice1() = default;

    gslice1(const gslice1 &) = default;

    gslice1(gslice1 &&) = default;

    gslice1 &operator=(const gslice1 &) = default;

    gslice1 &operator=(gslice1 &&) = default;
    // ...
};

class gslice2 {
    valarray<size_t> size;
    valarray<size_t> stride;
    valarray<size_t> dl;
public:
    // ...
};

//===--------------------------------------------------------------===//
// 17.6.2 default operations
//===--------------------------------------------------------------===//

struct S {
    string a;
    int b;
};

S f2(S arg) {
    S s0{};    // default construction: {"", 0}
    S s1{s0};  // copy construction
    s1 = arg;  // copy assignment
    return s1; // move construction
}

//===--------------------------------------------------------------===//
// 17.6.3.1 default constructors
//===--------------------------------------------------------------===//

struct X {
    X(int i) {} // require an int to initialize an X
};

X a{1};   // OK
// X b{}; // Error: no default constructor

struct Y {
    string s;
    int n;

    Y(const string &s); // initialize Y with a string
    Y() = default;      // allow default initialization with the default meaning
};

//===--------------------------------------------------------------===//
// 17.6.3.2 maintaining invariants
//===--------------------------------------------------------------===//

struct Z {
    // invariant:
    // my_favorite is the index of my favorite element of elem
    // largest points to the element with the highest value in elem

    vector<int> elem;
    int my_favorite;
    int *largest;
};

Z v0;                             // no initialization (possibility of undefined values)
Z val{{1, 2, 3}, 1, &v0.elem[2]}; // OK, but ugly and error-prone
Z v2 = val;                       // copy: v2.largest points into val
Z v3 = move(val);                 // move: val.elem becomes empty, v3.my_favorite is out of range


//===--------------------------------------------------------------===//
// 17.6.3.3 resource invariants
//===--------------------------------------------------------------===//

template<typename T>
class Handle {
    T *p;
public:
    Handle(T *pp) : p{pp} {}

    T &operator*() { return *p; }

    ~Handle() { delete p; }
};

void f3_3_1() {
    Handle<int> h1{new int {99}}; // OK
    // Handle<int> h1;            // Error: no default constructor
    // Handle<int> h2{h1};        // Error: no copy constructor
}

void execute3_3() {
    f3_3_1();
}

//===--------------------------------------------------------------===//
// 17.6.3.4 partially specified invariants
//===--------------------------------------------------------------===//

class Tic_tac_toe1 {
public:
    Tic_tac_toe1() : pos(9) {} // always 9 positions

    Tic_tac_toe1 &operator=(const Tic_tac_toe1 &arg) {
        for (int i = 0; i < 9; ++i)
            pos.at(i) = arg.pos.at(i);

        return *this;
    }

    // ... other operations ...

    enum State {
        empty, nought, cross,
    };
private:
    vector<State> pos;
};

class Tic_tac_toe2 {
public:
    Tic_tac_toe2() : pos(9) {} // always 9 positions

    Tic_tac_toe2(const Tic_tac_toe2 &) = default;

    Tic_tac_toe2 &operator=(const Tic_tac_toe2 &arg) = default;

    ~Tic_tac_toe2() = default;

    // ... other operations ...

    enum State {
        empty, nought, cross,
    };
private:
    vector<State> pos;
};

class Tic_tac_toe3 {
public:
    // ... other operations ...
    enum State {
        empty, nought, cross,
    };
private:
    vector<State> pos{vector<State>(9)};
};

//===--------------------------------------------------------------===//
// 17.6.4 deleted functions
//===--------------------------------------------------------------===//

class Base {
    // ...
    Base &operator=(const Base &) = delete; // disallow copying
    Base(const Base &) = delete;

    Base &operator=(Base &&) = delete;      // disallow moving
    Base(Base &&) = delete;
};

Base x1{};
// Base x2{x1}; // Error: no copy constructor

template<typename T>
T *clone(T *p) {
    return new T{*p};
}

struct Shape {
};
struct Foo {
};

Foo *clone(Foo *) = delete; // don’t try to clone a Foo

void f4_1(Shape *ps, Foo *pf) {
    Shape *ps2 = clone(ps);   // OK
    // Foo *pf2 = clone(pf);  // Error: clone(Foo*) has been deleted
}

struct Z4 {
    // ...
    Z4(double) {}     // can initialize with a double
    Z4(int) = delete; // but not with a int
};

void f4_2() {
    // Z4 z1{1}; // Error: Z4(int) has been deleted
    Z4 z2{1.0};  // OK
}

class Not_on_stack {
    // ...
    ~Not_on_stack() = delete;
};

class Not_on_free_store {
    // ...
    void *operator new(size_t) = delete;
};

void f4_3() {
    // Not_on_stack v1;   // Error: can't destroy
    Not_on_free_store v2; // OK

    Not_on_stack *p1 = new Not_on_stack;              // OK
    // Not_on_free_store *p2 = new Not_on_free_store; // Error: can't allocate
}

void execute4() {
    f4_2();
    f4_3();
}

//===--------------------------------------------------------------===//

int main() {
    execute3_3();
    execute4();
    return 0;
}
