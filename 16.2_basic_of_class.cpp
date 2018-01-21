#include <iostream>
#include <complex>

//===--------------------------------------------------------------===//
// 16.2 basic of class
//===--------------------------------------------------------------===//

class X {
private: // internal representation(implementation) is private
    int m;
public:  // user interface is public
    X(int i = 0) : m{i} {} // constructor (initialize data member m)

    int mf(int i) {  // member function
        int old = m;
        m = i;       // set new value
        return old;  // return old value
    }
};

X var{7}; // variable is X type and initialized by 7

int user(X var, X *ptr) {
    int x = var.mf(3);  // use .(dot) for access
    int y = ptr->mf(9); // use ->(arrow) for access
    // int z = var.m;   // Error: can't access private members

    std::cout << x << std::endl;
    std::cout << y << std::endl;

    return x;
}

void execute() {
    std::cout << "-----16.2 basic of class-----" << std::endl;
    user(var, &var);
}

//===--------------------------------------------------------------===//
// 16.2.1 member function
//===--------------------------------------------------------------===//

struct Date1 {   // internal data representation
    int d, m, y;
};

void init_date(Date1 &d, int, int, int); // initialize d
void add_year(Date1 &d, int n);          // add n years to d
void add_month(Date1 &d, int n);         // add n months to d
void add_day(Date1 &d, int n);           // add n days to d

struct Date2 {
    int d, m, y;

    void init(int dd, int mm, int yy);   // initialize
    void add_year(int n);                // add n years
    void add_month(int n);               // add n months
    void add_day(int n);                 // add n days
};

Date2 my_birthday;

void f1() {
    Date2 today;

    today.init(16, 10, 1996);
    my_birthday.init(30, 12, 1950);

    Date2 tomorrow = today;
    tomorrow.add_day(1);

    std::cout << today.y << today.m << today.d << std::endl;
    std::cout << my_birthday.y << my_birthday.m << my_birthday.d << std::endl;
    std::cout << tomorrow.y << tomorrow.m << tomorrow.d << std::endl;

}

void Date2::init(int dd, int mm, int yy) {
    d = dd;
    m = mm;
    y = yy;
}

void Date2::add_day(int n) {
    d += n;
}

void execute1() {
    std::cout << "-----16.2.1 member function-----" << std::endl;
    f1();
}

//===--------------------------------------------------------------===//
// 16.2.2 copy of default
//===--------------------------------------------------------------===//

void print_date(const Date2 &d) {
    std::cout << d.y << d.m << d.d << std::endl;
}

void f2_1() {
    Date2 d1 = my_birthday; // initialize by copy
    Date2 d2{my_birthday};  // initialize by copy

    print_date(d1);
    print_date(d2);
}

void f2_2(Date2 &d) {
    d = my_birthday;
}

void f2_3() {
    Date2 today{16, 10, 1996};
    print_date(today);
    f2_2(today);
    print_date(today);
}

void execute2() {
    std::cout << "-----16.2.2 copy of default-----" << std::endl;
    f2_1();
    std::cout << std::endl;

    f2_3();
}

//===--------------------------------------------------------------===//
// 16.2.3 access control
//===--------------------------------------------------------------===//

class Date3 {
    int d, m, y;
public:
    void init(int dd, int mm, int yy); // initialize

    void add_year(int n);                // add n years
    void add_month(int n);               // add n months
    void add_day(int n);                 // add n days
};

void Date3::init(int dd, int mm, int yy) {
    d = dd;
    m = mm;
    y = yy;
}

void Date3::add_year(int n) {
    y += n;
}

void timewarp(Date3 &d) {
    // d.y -= 200; // Error: Date3::y is private
}

void f3_1() {
    Date3 dx;
    // dx.m = 3;          // Error: m is private
    dx.init(25, 3, 2011); // OK
}

void execute3() {
    f3_1();
}

//===--------------------------------------------------------------===//
// 16.2.4 class and struct
//===--------------------------------------------------------------===//

class X4 { // class definition
};

struct S4 {
};

/* same as
class S4 {
public:
};
*/

class Date4 {
    int d, m, y; // private by default
public:
    Date4(int dd, int mm, int yy);

    void add_year(int n);
};

struct Date5 {
private:
    int d, m, y;
public:
    Date5(int dd, int mm, int yy);

    void add_year(int n);
};

class Date6 {
public:
    Date6(int dd, int mm, int yy);

    void add_year(int n);

private:
    int d, m, y;
};

class Date7 {
public:
    Date7(int dd, int mm, int yy);

private:
    int d, m, y;

public:
    void add_year(int n);
};

//===--------------------------------------------------------------===//
// 16.2.5 constructor
//===--------------------------------------------------------------===//

class Date8 {
    int d, m, y;
public:
    Date8(int dd, int mm, int yy); // constructor
    // ...
};

Date8::Date8(int dd, int mm, int yy) {
    d = dd;
    m = mm;
    y = yy;
}

void f5_1() {
    Date8 today = Date8{23, 6, 1983};
    Date8 xmas{25, 12, 1990};    // short syntax
    // Date8 release1_0{10, 12}; // Error: third argument does not exist
}

class Date9 {
    int d, m, y;
public:
    Date9(int, int, int); // day, month, year
    Date9(int, int);      // day, month, today's year
    Date9(int);           // day, today's month, today's year
    Date9();              // default Date9 : today
    Date9(const char *);  // date of string representation
    // ...
};

class Date10 {
    int d, m, y;
public:
    Date10(int dd = 0, int mm = 0, int yy = 0);
    // ...
};

Date2 today5{16, 10, 1996};

Date10::Date10(int dd, int mm, int yy) {
    d = dd ? dd : today5.d;
    m = mm ? mm : today5.m;
    y = yy ? yy : today5.y;

    // ...check if it is a valid date ...
}

void execute5() {
    f5_1();
}

//===--------------------------------------------------------------===//
// 16.2.6 explicit constructor
//===--------------------------------------------------------------===//

std::complex<double> d6{1}; // d == {1, 0}

void my_fct6_1(Date10 d) {
}

void f6_2() {
    Date10 d{15}; // OK: {15, today5.m, today5.y}
    // ...
    my_fct6_1(15); // ambiguous
    d = 15;        // ambiguous
}

class Date11 {
    int d, m, y;
public:
    explicit Date11(int dd = 0, int mm = 0, int yy = 0);
};

Date11::Date11(int dd, int mm, int yy) {
    d = dd ? dd : today5.d;
    m = mm ? mm : today5.m;
    y = yy ? yy : today5.y;
}

// explicit Date11::Date11(int dd, int mm, int yy) {} // Error

void my_fct6_2(Date11 d) {
}

void f6_4() {
    Date11 d1{15};          // OK: explicit
    Date11 d2 = Date11{15}; // OK: explicit
    // Date11 d3 = {15};    // Error: initialization by = do not implicit conversion
    // Date11 d4 = 15;      // Error: initialization by = do not implicit conversion
}

void f6_5() {
    // my_fct6_2(15);      // Error: argument do not implicit conversion
    // my_fct6_2({15});    // Error: argument do not implicit conversion
    my_fct6_2(Date11{15}); // OK: explicit
}

struct X6 {
    explicit X6();

    explicit X6(int, int);
};

X6::X6() {
}

X6::X6(int, int) {
}

void f6_6() {
    // X6 x1 = {};     // Error: implicit
    // X6 x2 = {1, 2}; // Error: implicit

    X6 x3{};     // OK: explicit
    X6 x4{1, 2}; // Ok: explicit
}

int f6_7(X6 x) {
    return 1;
}

void f6_8() {
    // int i1 = f6_7({});     // Error: implicit
    // int i2 = f6_7({1, 2}); // Error: implicit

    int i3 = f6_7(X6{});     // OK: explicit
    int i4 = f6_7(X6{1, 2}); // OK: explicit
}

void execute6() {
    f6_2();
    f6_4();
    f6_5();
    f6_6();
    f6_8();
}

//===--------------------------------------------------------------===//
// 16.2.7 initializer in class
//===--------------------------------------------------------------===//

struct {
    int d, m, y;
} data_initializer = {1, 1, 1970};

class Date12 {
    int d{data_initializer.d};
    int m{data_initializer.m};
    int y{data_initializer.y};
public:
    Date12(int, int, int); // day, month, year
    Date12(int, int);      // day, month, today's year
    Date12(int);           // day, today's month, today's year
    Date12();              // default Date9 : today
    Date12(const char *);  // date of string representation
    // ...
};

Date12::Date12(int dd) : d{dd} {}
// == Date12::Date12(int dd) : d{dd}, m{data_initializer.m}, y{data_initializer.y} {}

//===--------------------------------------------------------------===//
// 16.2.8 function definition in class
//===--------------------------------------------------------------===//

class Date13 {
public:
    void add_month(int n) { // add m in Date13
        m += n;
    }
    // ...
private:
    int d, m, y;
};

class Date14 {
public:
    void add_month(int n); // add m in Date14
    // ...
private:
    int d, m, y;
};

inline void Date14::add_month(int n) {
    m += n;
}

//===--------------------------------------------------------------===//
// 16.2.9.1 const member function
//===--------------------------------------------------------------===//

class Date15 {
    int d, m, y;
public:
    int day() const { return d; }

    int month() const { return m; }

    int year() const;

    void add_year(int n);
};

int Date15::year() const {
    // return ++y; // Error: change member in const function
    return y;
}

// int Date15::year() {} // Error: member function type lacks const

void Date15::add_year(int n) {
    y += n;
}

void f9_1_1(Date15 &d, const Date15 &cd) {
    int i = d.year(); // OK
    d.add_year(1);    // OK

    int j = cd.year(); // OK
    // cd.add_year(1); // Error: cannot change const Date15's value
}

void execute9_1() {
    Date15 d{};
    f9_1_1(d, d);
}

//===--------------------------------------------------------------===//
// 16.2.9.2 logical constness
//===--------------------------------------------------------------===//

class Date16 {
public:
    // ...
    std::string string_rep() const; // string
private:
    bool cache_valid;
    std::string cache;

    void compute_cache_value(); // compute cache
    // ...
};

//===--------------------------------------------------------------===//
// 16.2.9.3 mutable
//===--------------------------------------------------------------===//

class Date17 {
public:
    // ...
    std::string string_rep() const; // string
private:
    mutable bool cache_valid;
    mutable std::string cache;

    void compute_cache_value() const; // compute (mutable)cache
};

std::string Date17::string_rep() const {
    if (!cache_valid) {
        compute_cache_value();
        cache_valid = true;
    }

    return cache;
}

void Date17::compute_cache_value() const {
    cache = "cached";
}

void f9_3_1(Date17 d, const Date17 cd) {

    std::string s1 = d.string_rep();
    std::string s2 = cd.string_rep(); // OK!

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}

void execute9_3() {
    std::cout << "------16.2.9.3 mutable-----" << std::endl;
    Date17 d{};
    f9_3_1(d, d);
}

//===--------------------------------------------------------------===//
// 16.2.9.4 indirect reference and mutability
//===--------------------------------------------------------------===//

struct cache {
    bool valid;
    std::string rep;
};

class Date18 {
public:
    // ...
    std::string string_rep() const; // string
    explicit Date18(cache *c) : c{c} {}

private:
    cache *c; // initialize by constructor
    void compute_cache_value() const;
};

std::string Date18::string_rep() const {
    std::cout << c->rep << std::endl;
    if (!c->valid) {
        compute_cache_value();
        c->valid = true;
    }

    return c->rep;
}

void Date18::compute_cache_value() const {
    c->rep = "cached";
}

void f9_4_1(Date18 d) {
    std::string s1 = d.string_rep();

    std::cout << s1 << std::endl;
}

void execute9_4() {
    std::cout << "------indirect reference and mutability-----" << std::endl;
    cache c{false, "no cached"};
    Date18 d{&c};
    f9_4_1(d);
}

//===--------------------------------------------------------------===//
// 16.2.10 self reference
//===--------------------------------------------------------------===//

class Date19 {
    int d, m, y;
public:
    Date19(int dd, int mm, int yy) : d{dd}, m{mm}, y{yy} {}

    Date19 &add_year(int n);   // add n years
    Date19 &add_month(int n);  // add n months
    Date19 &add_day(int n);    // add n days
};

Date19 &Date19::add_year(int n) {
    y += n; // == this->y += n
    return *this;
}

struct Link {
    Link *pre;
    Link *suc;
    int data;

    Link *insert(int x) { // insert x before this
        return pre = new Link{pre, this, x};
    }

    void remove() { // delete this
        if (pre) pre->suc = suc;
        if (suc) suc->pre = pre;
        delete this;
    }
};

//===--------------------------------------------------------------===//
// 16.2.11 member access
//===--------------------------------------------------------------===//

struct X11 {
    void f1();

    int f2() { return m; } // OK: return X11's m

    int m;
};

void f11_1(X11 x, X11 *px) {
    // m = 1;    // Error: m not in scope
    x.m = 1;     // OK
    // x->m = 1; // Error: x is not pointer
    px->m = 2;   // OK
    // px.m = 1; // Error: px is pointer

    std::cout << x.m << std::endl;
    std::cout << x.f2() << std::endl;

    std::cout << px->m << std::endl;
    std::cout << px->f2() << std::endl;
}

void X11::f1() {
    m = 1; // OK: "this->m = 1;"
}

struct S11 {
    int m;

    int f();

    static int sm;
};

int S11::f() { return m; } // S11's f
int S11::sm{7};            // S11's static member sm

void execute11() {
    std::cout << "-----16.2.11 member access-----" << std::endl;
    X11 x{};
    f11_1(x, &x);
}

//===--------------------------------------------------------------===//
// 16.2.12 static member
//===--------------------------------------------------------------===//

class Date20 {
    int d, m, y;
    static Date20 default_date;
public:
    Date20(int dd = 0, int mm = 0, int yy = 0);

    // ...

    static void set_default(int dd, int mm, int yy); // set default_date to Date20(dd, mm, yy)
};

Date20::Date20(int dd, int mm, int yy) {
    d = dd ? dd : default_date.d;
    m = mm ? mm : default_date.m;
    y = yy ? yy : default_date.y;

    // ...check if it is a valid date ...
}

void f12_1() {
    Date20::set_default(4, 5, 1945); // call Date20's static member set_default()
}

Date20 Date20::default_date{16, 12, 1770}; // define Date20::default_date

void Date20::set_default(int dd, int mm, int yy) { // define Date20::set_default
    default_date = {dd, mm, yy};
}

void f12_2(Date20 d) {}

void f12_3(Date20 d) {}

void f12_3(int i) {}

void f12_4() {
    f12_2({});       // OK: same as f12_2(Date20{})
    f12_3({});       // ambiguous
    f12_3(Date20{}); // OK
}

void execute12() {
    f12_4();
}
//===--------------------------------------------------------------===//
// 16.2.13 member type
//===--------------------------------------------------------------===//

template<typename T>
class Tree {
    using value_type = T; // alias member
    enum Policy {         // enum member
        rb, splay, treeps
    };

    class Node {          // member class(nested class)
        Node *right;
        Node *left;
        value_type value;

    public:
        void f(Tree *);
    };

    Node *top;
public:
    void g(Node *);
    // ...
};

template<typename T>
void Tree<T>::Node::f(Tree *p) {
    // top = right;             // Error: not exists top(Tree object)
    p->top = right;             // OK
    value_type v = left->value; // OK: value_type is not associated with an object
}

template<typename T>
void Tree<T>::g(Tree::Node *p) {
    // value_type val = right->value;  // Error: not exists right(Tree::Node object)
    // value_type v = p->right->value; // Error: Node:right is private
    p->f(this);                        // OK
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute3();
    execute5();
    execute6();
    execute9_1();
    execute9_3();
    execute9_4();
    execute11();
    execute12();
    return 0;
}
