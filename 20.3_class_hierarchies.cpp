#include <iostream>
#include <list>
#include <vector>

using namespace std;

//===--------------------------------------------------------------===//
// 20.3.1 type fields
//===--------------------------------------------------------------===//

struct Employee {
    enum Empl_type {
        man, empl
    };
    Empl_type type;

    Employee() : type{empl} {}

    string first_name, family_name;
    char middle_initial;

    string hiring_date;
    short department;
};

struct Manager : public Employee {
    Manager() { type = man; }

    list<Employee *> group; // people managed
    short level;
    // ...
};

void print_employee(const Employee *e) {
    switch (e->type) {
        case Employee::empl:
            cout << e->family_name << '\t' << e->department << endl;
            // ...
            break;
        case Employee::man:
            cout << e->family_name << '\t' << e->department << endl;
            // ...
            const Manager *p = static_cast<const Manager *>(e);
            cout << "level " << p->level << endl;
            break;
    }
}

void print_list(const list<Employee *> &elist) {
    for (auto x : elist)
        print_employee(x);
}

void print_employee2(const Employee *e) {
    cout << e->family_name << '\t' << e->department << endl;
    // ...
    if (e->type == Employee::man) {
        const Manager *p = static_cast<const Manager *>(e);
        cout << "level " << p->level << endl;
        // ...
    }
}

//===--------------------------------------------------------------===//
// 20.3.2 virtual functions
//===--------------------------------------------------------------===//

class Employee2 {
public:
    Employee2(const string &name, short dept)
            : family_name{name}, department{dept} {};

    virtual void print() const;
    // ...
private:
    string first_name, family_name;
    short department;
    //...
};

void Employee2::print() const {
    cout << family_name << '\t' << department << endl;
    // ...
}

class Manager2 : public Employee2 {
public:
    Manager2(const string &name, short dept, short level)
            : Employee2(name, dept),
              level{level} {}

    void print() const;
    // ...
private:
    list<Employee2 *> group;
    short level;
};

void Manager2::print() const {
    Employee2::print();
    cout << "\tlevel " << level << endl;
}

void print_list2(const list<Employee2 *> &s) {
    for (auto x : s)
        x->print();
}

void execute2() {
    cout << "-----20.3.2 virtual functions-----" << endl;
    Employee2 e{"Brown", 1234};
    Manager2 m{"Smith", 1234, 2};

    print_list2({&m, &e});
}

//===--------------------------------------------------------------===//
// 20.3.4 override control
//===--------------------------------------------------------------===//

struct B0 {
    void f(int) const;

    virtual void g(double);
};

struct B1 : B0 {};
struct B2 : B1 {};
struct B3 : B2 {};
struct B4 : B3 {};
struct B5 : B4 {};

struct D : B5 {
    void f(int) const; // override f() in base class
    void g(int);       // override g() in base class
    virtual int h();   // override h() in base class
};

//===--------------------------------------------------------------===//
// 20.3.4.1 override
//===--------------------------------------------------------------===//

struct D2 : B5 {
    // void f(int) const override; // Error: B0::f() is not virtual
    // void g(int) override;       // Error: B0::g() takes a double argument
    // virtual int h() override;   // Error: no function h() to override
};

class Base {
    virtual int f() {};

    virtual void g() {};
};

class Derived : public Base {
    int f() override; // OK if Base has a virtual f()
    void g() override; // OK if Base has a virtual g()
};

/*
void Derived::f() override { // Error: override out of class
    // ...
}
*/

int Derived::f() { // OK
    return 0;
}

void Derived::g() { // OK
    // ...
}


int override = 7; // override is contextual keyword

struct Dx : Base {
    int override;

    int f() override {
        return override + ::override;
    }
};

//===--------------------------------------------------------------===//
// 20.3.4.2 final
//===--------------------------------------------------------------===//

class Type {};

struct Node { // interface class
    virtual Type type() = 0;
};

class If_statement : public Node {
    Type type() override final; // prevent further overriding
};

class Modified_if_statement : public If_statement {
public:
    // Type type() override; // Error: If_statement::type() is final
    // ...
};

class For_statement final : public Node {
public:
    Type type() override;
    // ...
};

/*
class Modified_for_statement : public For_statement { // Error: For_statement is final
    Type type() override;
};
*/

class Base2 {
    virtual int f();
    virtual void g();
};

class Derived2: public Base2 {
    int f() final; // OK if Base2 has a virtual f()
    void g() final; // OK if Base2 has a virtual f()
};

/*
void Derived2::f() final { // Error: final out of class
    // ...
}
*/

void Derived2::g() { // OK
    // ...
}

int final = 7; // final is contextual keyword

struct Dx2 : Base2 {
    int final;

    int f() final {
        return final + ::final;
    }
};

//===--------------------------------------------------------------===//
// 20.3.5 using base members
//===--------------------------------------------------------------===//

struct Base3 {
    void f(int) {
        cout << "Base3::f(int) called" << endl;
    };
};

struct Derived3: Base3 {
    void f(double) {
        cout << "Derived3::f(double) called" << endl;
    };
};

void f5_1(Derived3 d) {
    d.f(1);        // call Derived3::f(double)
    Base3 &br = d;
    br.f(1);       // call Base3::f(int)
}

struct Derived4 : Base3 {
    using Base3::f; // bring all fs from Base3 into Derived4
    void f(double) {
        cout << "Derived4::f(double) called" << endl;
    };
};

void f5_2(Derived4 d) {
    d.f(1);        // call Derived4::f(int), that is, Base3::f(int)
    Base3 &br = d;
    br.f(1);       // call Base3::f(int)
}

struct Base4 {
    void f(int) {
        cout << "Base4::f(int) called" << endl;
    }
};

struct Base5 {
    void f(double) {
        cout << "Base5::f(double) called" << endl;
    }
};

struct Derived5: Base4, Base5 {
    using Base4::f;
    using Base5::f;
    void f(char) {
        cout << "Derived5::f(char) called" << endl;
    }
};

void f5_3(Derived5 d) {
    d.f(1);   // call Derived5::f(int), that is, Base4::f(int)
    d.f('a'); // call Derived5::f(char)
    d.f(1.0); // call Derived5::f(double), that is, Base5::f(double)
}

void execute5() {
    cout << "-----20.3.5 using base members-----" << endl;
    Derived3 d{};
    f5_1(d);
    cout << endl;

    Derived4 d2{};
    f5_2(d2);
    cout << endl;

    Derived5 d3{};
    f5_3(d3);
}

//===--------------------------------------------------------------===//
// 20.3.5.1 inheriting constructors
//===--------------------------------------------------------------===//

template<typename T>
struct Vector : std::vector<T> {
    using size_type = typename std::vector<T>::size_type; // using size_type of vector

    T &operator[](size_type i) {
        return this->at(i); // using checked access;
    }

    const T &operator[](size_type i) const {
        return this->at(i);
    }
};

// Vector<int> v{1, 2, 3, 5, 8}; // Erorr: no initializer-list constructor

template<typename T>
struct Vector2 : std::vector<T> {
    using size_type = typename std::vector<T>::size_type; // using size_type of vector

    using std::vector<T>::vector; // inherit constructors

    T &operator[](size_type i) {
        return this->at(i); // using checked access;
    }

    const T &operator[](size_type i) const {
        return this->at(i);
    }
};

Vector2<int> v{1, 2, 3, 5, 8}; // OK: use initializer-list constructor from std::vector

struct Base6 {
    Base6(int) {}
};

struct Derived6 : Base6 {
    using Base6::Base6; // implicit declares Derived6(int)
    string s;           // string has a default constructor
    int x;              // we "forgot" to provide for initialization of x
};

void f5_1_1() {
    Derived6 d{6}; // oops: d.x is not initialized
    cout << "d.x is " << d.x << endl;
    // Derived6 e;    // error: Derived6 has no default constructor
}

struct Derived7 : Base6 {
    Derived7(int i) : Base6(i) {}
    string s;           // string has a default constructor
    int x;              // we "forgot" to provide for initialization of x
};

struct Derived8 : Base6 {
    using Base6::Base6; // implicit declares Derived6(int)
    int x{0};           // note: x is initialized
};

void f5_1_2() {
    Derived8 d{6}; // d.x is zero
    cout << "d.x is " << d.x << endl;
}

void execute5_1() {
    cout << "-----20.3.5.1 inheriting constructors-----" << endl;
    f5_1_1();
    f5_1_2();
}

//===--------------------------------------------------------------===//
// 20.3.6 return type relaxation
//===--------------------------------------------------------------===//

class Expr {
public:
    Expr() {};             // default constructor
    Expr(const Expr &) {}; // copy constructor

    virtual Expr *new_expr() = 0;

    virtual Expr *clone() = 0;
    // ...
};

class Cond : public Expr {
public:
    Cond() {};

    Cond(const Cond &) {};

    Cond *new_expr() override {
        return new Cond();
    }

    Cond *clone() override {
        return new Cond(*this);
    }
};

void f6_1(Expr *p) {
    Expr *p2 = p->new_expr();
    cout << typeid(p2).name() << endl;
}

void f6_2(Cond *pc) {
    Cond *p1 = pc->clone();
    cout << typeid(p1).name() << endl;
}

void execute6() {
    cout << "-----20.3.6 return type relaxation-----" << endl;
    Cond c{};
    f6_1(&c);
    f6_2(&c);
}

//===--------------------------------------------------------------===//
int main() {
    execute2();
    execute5();
    execute5_1();
    execute6();
    return 0;
}
