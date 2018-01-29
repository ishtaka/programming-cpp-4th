#include <iostream>
#include <vector>

using namespace std;

//===--------------------------------------------------------------===//
// 17.2 constructor and destructor
//===--------------------------------------------------------------===//

struct Tracer {
    string mess;

    explicit Tracer(const string &s) : mess{s} {
        cout << mess;
    }

    ~Tracer() {
        cout << "~" << mess;
    }
};

void f(const vector<int> &v) {
    Tracer tr{"in f()\n"};
    for (auto x : v) {
        Tracer tr{string{"v loop "} + to_string(x) + "\n"};
        // ...
    }
}

void execute() {
    cout << "-----17.2 constructor and destructor-----" << endl;
    f({2, 3, 5});
}

//===--------------------------------------------------------------===//
// 17.2.1 constructor and invariant
//===--------------------------------------------------------------===//

struct S {
    S();                  // OK
    // void S(int);       // Error: can not specify return type to constructor
    // int S;             // Error: can not use class name except for constructor
    // enum S {foo ,bar}; // Error: can not use class name except for constructor
};

class Vector1 {
public:
    Vector1(int s);

    class Bad_size {
        int s;
    public:
        Bad_size(int s) : s(s) {}
    };
    // ...
private:
    double *elem; // elem points to an array consisting of sz doubles.
    int sz;       // sz is not minus
};

Vector1::Vector1(int s) {
    if (s < 0)
        throw Bad_size{s};

    sz = s;
    elem = new double[s];
}

//===--------------------------------------------------------------===//
// 17.2.2 destructor and resource
//===--------------------------------------------------------------===//

class Vector2 {
public:
    Vector2(int s)
            : elem{new double[s]}, sz{s} {} // constructor: allocate memory
    ~Vector2() {                            // destructor: delete memory
        cout << "delete" << endl;
        delete[] elem;
    }

private:
    double *elem;
    int sz;
};

Vector2 *f2(int s) {
    Vector2 v1(s);
    // ...
    return new Vector2(s + s);
}

void execute2() {
    cout << "-----17.2.2 destructor and resource-----" << endl;
    Vector2 *p = f2(5);
    // ...
    delete p;
}

//===--------------------------------------------------------------===//
// 17.2.3 destructors of bases and members
//===--------------------------------------------------------------===//

/*
 constructor
 [1] execute base classes constructor
 [2] execute members constructor
 [3] execute self constructor
*/

/*
 destructor
 [1] execute self destructor
 [2] execute members destructor
 [3] execute base classes destructor
*/

struct S1 {
    string s;
};

S1 x3; // OK: x.s is initialized by ""

struct X {
    int m;

    X(int x) : m{x} {}
};

struct S2 {
    X x;
};

// S2 x3_1; // Error: not exists value for x3_1.x
S2 x3_2{1}; // OK: x3_2.x is initialized by 1

//===--------------------------------------------------------------===//
// 17.2.4 calling constructors and destructors
//===--------------------------------------------------------------===//

class Nonlocal {
public:
    // ...
    void destroy() { delete this; } // explicit delete
private:
    // ...
    ~Nonlocal() {}  // can not implicit delete
};

void execute4() {
    // Nonlocal x;              // Error: can not delete Nonlocal
    Nonlocal *p = new Nonlocal; // OK
    // ...
    // delete p;  // Error: can not delete Nonlocal
    p->destroy(); // OK
}

//===--------------------------------------------------------------===//
// 17.2.5 virtual destructor
//===--------------------------------------------------------------===//

class Shape {
public:
    // ...
    virtual void draw() = 0;

    virtual ~Shape() {
        cout << "Shape destructor" << endl;
    };
};

class Circle : public Shape {
public:
    void draw() {
        cout << "draw" << endl;
    }

    ~Circle() { // override ~Shape()
        cout << "Circle destructor" << endl;
    }
    // ...
};

void f5(Shape *p) {
    p->draw(); // execute appropriate draw()
    // ...
    delete p; // execute appropriate destructor
}

void execute5() {
    cout << "-----17.2.5 virtual destructor-----" << endl;
    auto *c = new Circle;
    f5(c);
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute2();
    execute4();
    execute5();
    return 0;
}
