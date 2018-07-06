#include <iostream>
#include <vector>
#include <complex>
#include <list>

using namespace std;

//===--------------------------------------------------------------===//
// 19.2 special operators
//===--------------------------------------------------------------===//

// Special Operators
// [] () -> ++ -- new delete

//===--------------------------------------------------------------===//
// 19.2.1 subscripting
//===--------------------------------------------------------------===//

struct Assoc {
    vector<pair<string, int>> vec; // vector of {name,value} pairs

    //const int &operator[](const string &) const;

    int &operator[](const string &);
};

int &Assoc::operator[](const string &s) {
    // search for s; return a reference to its value if found;
    // otherwise, make a new pair {s,0} and return a reference to its value
    for (auto &x : vec)
        if (s == x.first) return x.second;

    vec.push_back({s, 0}); // initial value: 0

    return vec.back().second; // return
}

void execute1() {
    cout << "-----19.2.1 subscripting-----" << endl;
    Assoc values;
    string buf;

    while (cin >> buf)
        ++values[buf];

    for (auto x : values.vec)
        cout << '{' << x.first << ", " << x.second << '}' << endl;
}

//===--------------------------------------------------------------===//
// 19.2.2 function call
//===--------------------------------------------------------------===//

struct Action {
    int operator()(int i) { return i + i; };

    pair<int, int> operator()(int a, int b) {
        return {a, b};
    };

    double operator()(double d) { return d + d; };
};

void f2_1(Action act) {
    int x = act(2);
    auto y = act(3, 4);
    double z = act(2.3);

    cout << x << endl;
    cout << y.first << ", " << y.second << endl;
    cout << z << endl;
}

class Add {
    complex<double> val;
public:
    Add(complex<double> c) : val{c} {}               // save a value
    Add(double r, double i) : val{complex<double>{r, i}} {}

    void operator()(complex<double> &c) const {      // add a value to argument
        c += val;
        cout << c.real() << ", " << c.imag() << endl;
    }
};

void f2_2(vector<complex<double>> &vec, list<complex<double>> &lst, complex<double> z) {
    for_each(vec.begin(), vec.end(), Add{2, 3});
    for_each(lst.begin(), lst.end(), Add{z});
}

void f2_2_2(vector<complex<double>> &vec, list<complex<double>> &lst, complex<double> z) {
    for_each(vec.begin(), vec.end(), [](complex<double> &a) { a += complex<double>{2, 3}; });
    for_each(lst.begin(), lst.end(), [z](complex<double> &a) { a += z; });
}

void execute2() {
    cout << "-----19.2.2 function call-----" << endl;
    Action act = Action{};
    f2_1(act);

    vector<complex<double>> vec = {{1, 1},
                                   {2, 2},
                                   {3, 3}};
    list<complex<double>> lst = {{4, 4},
                                 {5, 5},
                                 {6, 6}};
    f2_2(vec, lst, {1, 1});
    f2_2_2(vec, lst, {1, 2});
}

//===--------------------------------------------------------------===//
// 19.2.3 dereferencing
//===--------------------------------------------------------------===//

class X {
public:
    int m;
};

class Ptr {
public:
    Ptr(X x) : x{x} {}

    X *operator->();

private:
    X x;
    // ...

};

X *Ptr::operator->() {
    return &x;
}

void f3_1(Ptr p) {
    p->m = 7; // (p.operator->())->m = 7
    cout << p->m << endl;
}

void f3_2(Ptr p) {
    // X *q1 = p->;         // syntax error
    X *q2 = p.operator->(); // OK
}

template<typename T>
class Disk_ptr {
    string identifier;
    T *in_core_address;
    // ...
public:
    Disk_ptr(const string &s) : identifier{s}, in_core_address{nullptr} {}

    ~Disk_ptr() { write_to_disk(in_core_address, identifier); }

    void write_to_disk(T *address, string name) {
        // write to disk
    }

    T *read_from_disk(string name) {
        // read from disk
        return nullptr;
    }

    T *operator->() {
        if (in_core_address == nullptr)
            in_core_address = read_from_disk(identifier);
        return in_core_address;
    }
};

struct Rec {
    string name;
};

void update(const string &s) {
    Disk_ptr<Rec> p{s}; // get Disk_ptr for s
    // p->name = "Roscoe"; // update s; if necessary, first retrieve from disk
    // ...
} // p's destructor writes back to disk

// p->m == (*p).m   // true
// (*p).m == p[0].m // true
// p->m == p[0].m   // true

template<typename T>
class Ptr2 {
    T *p;
public:
    T *operator->() { return p; }         // dereference to access member

    T &operator*() { return *p; }         // dereference to access whole object

    T &operator[](int i) { return p[i]; } // dereference to access element
    // ...
};

void execute3() {
    cout << "-----19.2.3 dereferencing-----" << endl;
    Ptr p{{1}};
    f3_1(p);
    f3_2(p);
    update("Test");
}

//===--------------------------------------------------------------===//
// 19.2.4 increment and decrement
//===--------------------------------------------------------------===//

void f4_1(X a) { // traditional use
    X v[200];
    X *p = &v[0];
    p--;
    // *p = a; // oops: p out of range, uncaught
    ++p;
    *p = a; // OK
}

template<typename T>
class Ptr3 {
    T *ptr;
    T *array;
    int sz;
public:
    template<int N>
    Ptr3(T *p, T(&a)[N]);    // bind to array a, sz==N, initial value p
    Ptr3(T *p, T *a, int s); // bind to array a of size s, initial vlaue p
    Ptr3(T *p);              // bind to single object, sz==0, initial value p

    Ptr3<T> &operator++();      // prefix
    Ptr3<T> &operator--();      // prefix
    Ptr3<T> operator++(int);    // postfix
    Ptr3<T> operator--(int);    // postfix

    T &operator*();          // postfix
};

template<typename T>
Ptr3<T> &Ptr3<T>::operator++() { // return the current object after incrementing
    // check that ptr+1 can be pointed to ...
    ++ptr;
    return *this;
}

template<typename T>
Ptr3<T> Ptr3<T>::operator++(int) { // increment and return a Ptr with old value
    // check that ptr+1 can be pointed to ...
    Ptr3<T> old{ptr, array, sz};
    ++ptr;
    return old;
}

template<typename T>
T &Ptr3<T>::operator*() {
    return ptr;
}

void execute4() {
    X a{1};
    f4_1(a);
}

//===--------------------------------------------------------------===//
// 19.2.5 allocation and deallocation
//===--------------------------------------------------------------===//

class Employee {
public:
    // ...
    void *operator new(size_t);          // use for individual object
    void operator delete(void *, size_t); // use for array

    void *operator new[](size_t);           // use for individual object
    void operator delete[](void *, size_t); // use for array
};

void *Employee::operator new(size_t s) {
    // allocate s bytes of memory and return a pointer to it
}

void Employee::operator delete(void *p, size_t) {
    if (p) { // delete only if p != 0;
        // assume p points to s bytes of memory allocated by Employee::operator new()
        // and free that memory for reuse
    }
}

//===--------------------------------------------------------------===//
// 19.2.6 user-defined literals
//===--------------------------------------------------------------===//

// 123  // int
// 1.2  // double
// 1.2F // float
// 'a'  // char
// 1ULL // unsigned long long
// 0xD0 // hexadecimal unsigned
// "as" // C-style string (const char[3])

// "Hi!"s           // string, not "zero-terminated array of char"
// 1.2i             // imaginary
// 101010111000101b // binary
// 123s             // seconds
// 123.56km         // not miles! (units)
// 1234567890123456789012345678901234567890x // extended-precision


constexpr complex<double> operator"" _i(long double d) { // imaginary literal
    return {0, static_cast<double>(d)}; // complex is literal type
}

std::string operator "" _s(const char *p, size_t n) { // std::string literal
    return string{p, n}; // require free-store allocation
}

template<typename T>
void f6_1(const T &s) {
    cout << s << endl;
}

void f6_2() {
    f6_1("Hello");    // pass pointer to char*
    f6_1("Hello"_s);   // pass (five-character) string object
    f6_1("Hello\n"_s); // pass (six-character) string object
}

void execute6() {
    f6_2();
}

//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute2();
    execute3();
    execute4();
    execute6();
    return 0;
}
