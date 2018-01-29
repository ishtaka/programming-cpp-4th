#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

//===--------------------------------------------------------------===//
// 17.3.1 initialization without constructors
//===--------------------------------------------------------------===//

int a1{1};
char *p{nullptr};

struct Work {
    string author;
    string name;
    int year;
};

Work s9{"Beethoven", "Symphony No. 9 in D minor, Op. 125; Choral", 1824}; // memberwize initialization
Work currently_playing{s9}; // copy initialization
Work none{};                // default initialization

Work alpha; // {"", "", 0}

void f1() {
    Work beta; // {"", "", unknown}
    // ...
}

struct Buf {
    int count;
    char buf[16 * 1024];
};

Buf buf0; // statically allocated, so initialized by default

void f2() {
    Buf buf1;   // leave elements uninitialized
    Buf buf2{}; // elements are initialized by 0

    int *p1 = new int;    // *p1 is uninitialized
    int *p2 = new int {};  // *p2 == 0
    int *p3 = new int {7}; // *p3 == 7
}

template<typename T>
class Checked_pointer {
private:
    T *p;
public:
    T &operator*();
    // ...
};

// Checked_pointer<int> p{new int{7}}; // Error: can not access to p.p

//===--------------------------------------------------------------===//
// 17.3.2 initialization using constructors
//===--------------------------------------------------------------===//

struct X2 {
    X2(int i) {}
};

// X2 x0;        // Error: no initializer
// X2 x1{};      // Error: empty initializer
X2 x2{2};        // OK
// X2 x3{"two"}; // Error: wrong initializer type
// X2 x4{1, 2};  // Error: wrong number of initializer
X2 x5{x2};       // OK: a copy constructor is implicitly defined

struct Y2_1 : X2 {
    X2 m{0};                     // provide default initializer for member m
    Y2_1(int a) : X2{a}, m{a} {} // initialize base and member
    Y2_1() : X2{0} {}            // initialize base and member
};

X2 g1{1}; // initialize global variable

void f2_1(int a) {
    // X2 def{};              // Error: no default value for X2
    Y2_1 de2{};               // OK: use default constructor
    X2 *p{nullptr};           // initialize local variable
    X2 var{2};                // initialize local variable
    p = new X2{4};            // initialize object on free store
    X2 b[]{1, 2, 3};          // initialize array elements
    vector<X2> v{1, 2, 3, 4}; // initialize vector elements
}

struct Y2_2 : X2 {
    X2 m;

    // Y2_2(int a) : X2(a), m = a {}; // Syntax Error: can't use = for member initialization
    Y2_2(int a) : X2(a), m(a) {};
};

X2 g2(1); // initialize global variable

void f2_2(int a) {
    X2 def();                    // function returning an X2
    X2 *p{nullptr};              // initialize local variable
    X2 var = 2;                  // initialize local variable
    // p = new X2 = 4;           // Syntax Error: can't use = for new
    // X2 b[](1, 2, 3);          // Error: can't use () for array initialization
    // vector<X2> v(1, 2, 3, 4); // Error: can't use () for list elements
}

struct S {
    S(const char *) {}

    S(double *) {}
};

S s1{"Napier"};         // S::S(const char*)
S s2{new double {1.0}}; // S::S(double *)
// S s3{nullptr};       // ambiguous: S::S(const char*) or S::S(double*)?

void execute2() {
    f2_1(1);
    f2_2(1);
}

//===--------------------------------------------------------------===//
// 17.3.2.1 initialization by constructors
//===--------------------------------------------------------------===//

struct S1 {
    int a, b; // no constructor
};

struct S2 {
    int a, b;

    S2(int aa = 0, int bb = 0) : a(aa), b(bb) {} // constructor
};

// S1 x11(1, 2); // Error: no constructor
S1 x12{1, 2};    // OK: memberwize initialization

// S1 x13(1);    // Error: no constructor
S1 x14{1};       // OK: x14.b becomes 0

S2 x21(1);       // OK: use constructor
S2 x22{1, 2};    // OK: use constructor

S2 x23(1);       // OK: use constructor and one default argument
S2 x24{1};       // OK: use constructor and one default argument

vector<int> v1{77}; // one element with value 77
vector<int> v2(77); // 77 elements with the default value 0

vector<string> v3{77}; // 77 elements with the default value ""
vector<string> v4(77); // 77 elements with the default value ""

vector<string> v5{"Booh!"};    // one element with value "Booh!"
                               //(vector<str ing>(std::initializer_list<str ing>) doesn’t accept {77}
// vector<string> v6("Booh!"); // Error: no constructor takes a string argument

vector<int *> v7{100, 0}; // 100 int*s initialized to nullptr (100 is not an int*)
vector<int *> v8{0, 0};   // 2 int*s initialized to nullptr
vector<int *> v9(0, 0);   // empty vector (v9.size() == 0)
vector<int *> v10;        // empty vector (v10.size() == 0)

//===--------------------------------------------------------------===//
// 17.3.3 default constructor
//===--------------------------------------------------------------===//

class Vector {
public:
    Vector() {} // default constructor: no parameter
    // ...
};

Vector v3_1;   // OK
Vector v3_2{}; // OK

class String {
public:
    String(const char *p = "") {} // default constructor: empty string
    // ...
};

String s3_1;   // OK
String s3_2{}; // OK

void f3_1() {
    int a0;      // uninitialized
    // int a1(); // function declaration(intended?)

    int a{};     // a becomes 0
    double d{};  // d becomes 0.0
    char *p{};   // p becomes nullptr

    int *p1 = new int;   // uninitialized int
    int *p2 = new int {}; // int is initialized to 0
}

template<typename T>
struct Handle {
    T *p;

    Handle(T *pp = new T{}) : p{pp} {}
    // ...
};

Handle<int> px; // generate int{}

int glob{9};

struct X3 {
    const int a1{7}; // OK
    const int a2;    // Error: requires a user-defined constructor

    const int &r{9}; // OK

    int &r1{glob};   // OK
    int &r2;         // Error: requires a user-defined constructor
};

struct S3 {
    S3() {} // has default constructor
};

struct S4 {
    S4(string s) {} // no default constructor
};

S3 a3_1[10];    // OK: 10 default elements
// S4 a3_2[10]; // Error: can't initialize elements

vector<S3> v3_3(10);    // OK: 10 default elements
// vector<S4> v3_4(10); // Error: cant' initialize elements

//===--------------------------------------------------------------===//
// 17.3.4 initializer-list constructor
//===--------------------------------------------------------------===//

vector<double> v = {1, 2, 3.456, 99.99};

list<pair<string, string>> languages = {
        {"Nygaard",  "Simula"},
        {"Richards", "BCPL"},
        {"Ritchie",  "C"}
};

map<vector<string>, vector<int>> years = {
        {{"Maurice", "Vincent", "Wilkes"},  {1913, 1945, 1951, 1967, 2000}},
        {{"Martin",  "Richards"},           {1982, 2003, 2007}},
        {{"David",   "John",    "Wheeler"}, {1927, 1947, 1951, 2004}}
};

void f4(initializer_list<int> l) {}

void execute4() {
    f4({1, 2});
    f4({23, 345, 4567, 56789});
    f4({}); // empty list

    // f4{1, 2}; // Error: function call () missing

    years.insert({{"Bjarne", "Stroustrup"},
                  {1950,     1975, 1985}});
}

//===--------------------------------------------------------------===//
// 17.3.4.1 initializer-list constructor disambiguation
//===--------------------------------------------------------------===//

struct X4 {
    X4(initializer_list<int> l) {}

    X4() {}

    X4(int i) {}
};

X4 x4_0{};  // empty list: default constructor or initializer-list constructor? (the default constructor)
X4 x4_1{1}; // one integer: an int argument or a list of one element? (the initializer-list constructor)

vector<int> v4_1{1};       // one element
vector<int> v4_2{1, 2};    // two elements
vector<int> v4_3{1, 2, 3}; // three elements

vector<string> vs1{"one"};
vector<string> vs2{"one", "two"};
vector<string> vs3{"one", "tow", "three"};

vector<int> v4_1_1(1);    // one element with the default value (0)
vector<int> v4_1_2(1, 2); // one element with the value 2

//===--------------------------------------------------------------===//
// 17.3.4.2 use of initializer-list
//===--------------------------------------------------------------===//

void f4_2_1(initializer_list<int> args) {
    for (int i = 0; i != args.size(); ++i)
        cout << args.begin()[i] << endl;
}

void f4_2_2(initializer_list<int> args) {
    for (auto x : args)
        cout << x << endl;
}

int f4_2_3(initializer_list<int> x, int val) {
    // *x.begin() = val; // Error: attempt to change the value of an initializer-list element
    return *x.begin();   // OK;
}

void f4_2_4() {
    for (int i = 0; i != 10; i++)
        cout << f4_2_3({1, 2, 3}, i) << " ";
    cout << endl;
}

template<typename E>
class Vector4 {
public:
    Vector4(initializer_list<E> s); // initializer-list constructor
    // ...
private:
    int sz;
    E *elem;
};

template<typename E>
Vector4<E>::Vector4(initializer_list<E> s)
        : sz{s.size()} { // set vector size
    // reserve(sz);                               // get the right amount of space
    uninitialized_copy(s.begin(), s.end(), elem); // initialize elements in elem[0:s.size())
}

void execute4_2() {
    cout << "-----17.3.4.2 use of initializer-list-----" << endl;
    f4_2_1({1, 3, 5, 7});
    cout << endl;
    f4_2_2({2, 4, 6, 8});
    cout << endl;
    f4_2_4();
}

//===--------------------------------------------------------------===//
// 17.3.4.3 direct and copy initialization
//===--------------------------------------------------------------===//

vector<vector<double>> vs4_3 = {
        {10, 11, 12, 13}, // OK: vector of four elements
        {10},             // OK: vector of one element
        // 10,            // Error: vector<double>(int) is explicit

        vector<double>{10, 11, 12, 13}, // OK: vector of four elements
        vector<double>{10},             // OK: vector of one element with value 10.0
        vector<double>(10)              // OK: vector of one element with value 0.0
};

vector<double> v4_3_1(7);     // OK: v4_3_1 has 7 elements; note: uses () rather than {}
// vector<double> v4_3_2 = 9; // Error: no conversion from int to vector

void f4_3_1(const vector<double> &v) {}

void f4_3_2() {
    // v4_3_1 = 9; // Error: no conversion from int to vector
    // f4_3_1(9);  //Error: no conversion from int to vector
}

vector<double> v4_3_3{7};   // OK: v4_3_3 has one element (with the value 7)
vector<double> v4_3_4 = {9}; // OK: v4_3_4 has one element (with the value 9)

void f4_3_3() {
    v4_3_1 = {9}; // OK: v4_3_3 now has one element (with the value 9)
    f4_3_1({9});  // OK: f4_3_1 is called with the list {9}
}

//===--------------------------------------------------------------===//

int main() {
    execute2();
    execute4();
    execute4_2();
    return 0;
}
