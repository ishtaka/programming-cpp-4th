#include <iostream>
#include <array>
#include <vector>


using namespace std;

//===--------------------------------------------------------------===//
// 17.5.1 copy
//===--------------------------------------------------------------===//

template<typename T>
class Matrix {
    array<int, 2> dim; // two dimensions
    T *elem;           // pointer to dim[0] * dim[1] elements of type T
public:
    Matrix(int d1, int d2) : dim{d1, d2}, elem{new T[d1 * d2]} {} // simplified(no error handling)

    int size() const { return dim[0] * dim[1]; }

    Matrix(const Matrix &);             // copy constructor
    Matrix &operator=(const Matrix &);  // copy assignment

    Matrix(Matrix &&);                   // move constructor
    Matrix &operator=(Matrix &&);        // move assignment

    ~Matrix() { delete[] elem; }
};

template<typename T>
Matrix<T>::Matrix(const Matrix &m)  // copy constructor
        : dim{m.dim}, elem{new T[m.size()]} {
    uninitialized_copy(m.elem, m.elem + m.size(), elem); // initialize elements of elem[0:m.size())
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &m) { // copy assignment
    if (dim[0] != m.dim[0] || dim[1] != m.dim[1])
        throw runtime_error("bad size in Matrix =");

    copy(m.elem, m.elem + m.size(), elem); // copy elements
}

/*
template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &m) { // copy assignment
    Matrix tmp{m};     // make a copy
    swap(tmp, *this);  // swap tmp’s representation with *this’s
    return *this;
}
*/

//===--------------------------------------------------------------===//
// 17.5.1.1 beware of default constructors
//===--------------------------------------------------------------===//

class X {
    string s;
    string s2;
    vector<string> v;

    X(const X &a) // copy constructor
            : s{a.s}, v{a.v} {} // probably sloppy and probably wrong
    // ...
};

//===--------------------------------------------------------------===//
// 17.5.1.2 copy of base
//===--------------------------------------------------------------===//

struct B1 {
    B1() {}

    B1(const B1 &) {}
    // ...
};

struct B2 {
    B2(int) {}

    B2(const B2 &) {}
    // ...
};

struct D : B1, B2 {
    D(int i) : B1{}, B2{i}, m1{}, m2{2 * i} {}

    D(const D &a) : B1{a}, B2{a}, m1{a.m1}, m2{a.m2} {}

    B1 m1;
    B2 m2;
};

D d{1};  // construct with int argument
D dd{d}; // copy construct

//===--------------------------------------------------------------===//
// 17.5.1.3 the meaning of copy
//===--------------------------------------------------------------===//

struct S {
    int *p; // a pointer
};

S x1{new int {0}};

void f1_3_1() {
    S y1{x1};  // "copy" x1

    *y1.p = 1;          // change y1: affects x1
    *x1.p = 2;          // change x1: affects y1
    delete y1.p;        // affects x1 and y1
    y1.p = new int {3}; // OK: change y1: does not affects x1
    *x1.p = 4;          // oops: write to deallocated memory
}

struct S2 {
    shared_ptr<int> p;
};

shared_ptr<int> p2(new int {0});
S2 x2{p2};

void f1_3_2() {
    S2 y2{x2}; // "copy" x2

    *y2.p = 1;               // change y2: affects x2
    *x2.p = 2;               // change x2: affects y2
    y2.p.reset(new int {3}); // change y2: affects x2
    *x2.p = 4;               // change x2: affects y2
}

class Descriptor {
};

class Representation {
};

class Image {
public:
    // ...
    Image(const Image &a); // copy constructor
    // ...
    void write_block(Descriptor);
    // ...
private:
    Representation *clone();        // copy *rep
    shared_ptr<Representation> rep; // possibility of share
};

Image::Image(const Image &a) // do shallow copy
        : rep{a.rep} {       // a.rep has 2 user
}

void Image::write_block(Descriptor d) {
    if (rep.use_count() > 1)
        rep = shared_ptr<Representation>{clone()};
    // ... now we can safely write to our own copy of rep ..
}

Representation *Image::clone() {
    return nullptr; // *Representation
}

//===--------------------------------------------------------------===//
// 17.5.1.4 slicing
//===--------------------------------------------------------------===//

struct Base {
    int b;

    Base(int i) : b{i} {}

    Base(const Base &) {}
};

struct Derived : Base {
    int d;

    Derived(int i) : d{i}, Base{i} {}

    Derived(const Derived &d) : Base{d.d} {}
};

void naive(Base *p) {
    Base b2 = *p; // may slice: invokes Base::Base(const Base &)
    // ...
}

void user() {
    Derived d{1};
    naive(&d);
    Base bb = d; // slices: invokes Base::Base(const Base &), not Derived::Derived(const Derived &)
    // ...
}

//===--------------------------------------------------------------===//
// 17.5.2 move
//===--------------------------------------------------------------===//

template<typename T>
void swap2(T &a, T &b) {
    const T tmp = a; // put a copy of 'a' into tmp
    a = b;           // put a copy of 'b' into 'a'
    b = tmp;         // put a copy of 'tmp' into 'b'
}

void f2_1(string &s1, string &s2,
          vector<string> &vs1, vector<string> &vs2,
          Matrix<string> &m1, Matrix<string> &m2) {
    swap2(s1, s2);
    swap2(vs1, vs2);
    swap2(m1, m2);
}

template<typename T>
Matrix<T>::Matrix(Matrix &&a)       // move constructor
        :dim{a.dim}, elem{a.elem} { // grab a’s representation
    a.dim = {0, 0};     // clear a's representation
    a.elem = nullptr;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&a) { // move assignment
    swap(dim, a.dim);   // swap representations
    swap(elem, a.elem);
    return *this;
}

template<typename T>
void p_swap(T &a, T &b) { // "perfect swap" (almost)
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b) { // res[i][j] = a[i][j]+b[i][j] for each i and j
    if (a.dim[0] != b.dim[0] || a.dim[1] != b.dim[1])
        throw runtime_error("unequal Matrix size in +");

    Matrix<T> res{a.dim[0], a.dim[1]};
    constexpr auto n = a.size();
    for (int i = 0; i != n; ++i)
        res.elem[i] = a.elem[i] + b.elem[i];

    return res;
}

//===--------------------------------------------------------------===//

int main() {
    return 0;
}
