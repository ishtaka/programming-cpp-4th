#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 14.4.1 convenience and safety
//===--------------------------------------------------------------===//

namespace X1 {
    int i, j, k;
}

int k;

void f1_1() {
    int i = 2;
    using namespace X1; // make name in X1 accessible
    i++;                // local i
    j++;                // X1::j
    // k++;             // Error: k is ambiguous whether X1::k or ::k
    ::k++;              // global k
    X1::k++;            // X1's k

    std::cout << i << std::endl;
    std::cout << ::k << std::endl;
}

void f1_2() {
    int i = 5;
    // using X1::i; // Error: the second declaration of i in f1_2()
    using X1::j;
    using X1::k;    // hides global k

    i++;
    j++; // X1::j
    k++; // X1::k

    std::cout << i << std::endl;
    std::cout << ::k << std::endl;
}

void execute1() {
    std::cout << "-----14.4.1 convenience and safety-----" << std::endl;
    f1_1();
    std::cout << std::endl;
    f1_2();
}

//===--------------------------------------------------------------===//
// 14.4.2 namespace aliases
//===--------------------------------------------------------------===//

namespace A { // there is possibility of clash because namespace is a short name
    // ...
}

namespace American_Telephone_and_Telegraph { // too long
    class String {
        std::string str;
    public:
        explicit String(const std::string &str) : str{str} {}
    };
    // ...
}

American_Telephone_and_Telegraph::String s2_1{"Grieg"};
American_Telephone_and_Telegraph::String s2_2{"Nielsen"};

// use namespace aliases to give a short name
namespace ATT = American_Telephone_and_Telegraph;
ATT::String s2_3{"Grieg"};
ATT::String s2_4{"Nielsen"};

//===--------------------------------------------------------------===//
// 14.4.3 namespace composition
//===--------------------------------------------------------------===//

namespace His_string {
    class String {
        std::string str;
    public:
        explicit String(const std::string &str) : str{str} {}
    };

    String operator+(const String &, const String &);

    String operator+(const String &, const char *);

    void fill(char);
// ...
}

namespace Her_vector {
    template<typename T>
    class Vector {
    };
    // ...
}

namespace My_lib {
    using namespace His_string;
    using namespace Her_vector;

    void my_fct(String &);
}

void f3_1() {
    My_lib::String s{"Byron"}; // My_lib::His_string::String can be found
    // ...
}

using namespace My_lib;

void f3_2(Vector<String> &vs) {
    // ...
    String s{""};
    my_fct(s);
    // ...
}

// void My_lib::fill(char c ) {}  // Error: fill() is not declared in My_lib::
void His_string::fill(char c) {}  // OK: fill() is declared in His_string::
void My_lib::my_fct(String &v) {} // OK: String is My_lib::String == His_string::String

//===--------------------------------------------------------------===//
// 14.4.4 composition and selection
//===--------------------------------------------------------------===//

namespace His_lib {
    class String {
    };

    template<typename T>
    class Vector {
    };
    // ...
}

namespace Her_lib {
    template<typename T>
    class Vector {
    };

    class String {
    };
}

namespace My_lib4 {
    using namespace His_lib; // all declarations of His_lib
    using namespace Her_lib; // all declarations of Her_lib

    using His_lib::String;  // prioritize His_lib to avoid name clash
    using Her_lib::Vector;  // prioritize Her_lib to avoid name clash

    template<typename T>
    class List {            // add
    };
    // ...
}

namespace My_lib4_2 {
    using namespace His_lib; // all declarations of His_lib
    using namespace Her_lib; // all declarations of Her_lib

    using His_lib::String;  // prioritize His_lib to avoid name clash
    using Her_lib::Vector;  // prioritize Her_lib to avoid name clash

    using Her_string = Her_lib::String; // name alias
    template<typename T>
    using His_vec = His_lib::Vector<T>; // name alias

    template<typename T>
    class List {            // add
    };
    // ...
}

//===--------------------------------------------------------------===//
// 14.4.5 namespace and overload
//===--------------------------------------------------------------===//

#include <algorithm>

namespace Estd {
    using namespace std;

    template<typename C>
    void sort(C &c) { std::sort(c.begin(), c.end()); }

    template<typename C, typename P>
    void sort(C &c, P p) { std::sort(c.begin(), c.end(), p); };
}

using namespace Estd;

template<typename T>
void print(const vector<T> &v) {
    for (auto &x : v)
        cout << x << ' ';
    cout << endl;
}

void f5() {
    vector<int> v{7, 3, 9, 4, 0, 1};

    sort(v);
    print(v);
    sort(v, [](int x, int y) { return x > y; });
    print(v);

    cout << endl;

    sort(v.begin(), v.end());
    print(v);
    sort(v.begin(), v.end(), [](int x, int y) { return x > y; });
    print(v);
}

void execute5() {
    std::cout << "-----14.4.5 namespace and overload-----" << std::endl;
    f5();
}

//===--------------------------------------------------------------===//
// 14.4.6 version control
//===--------------------------------------------------------------===//

namespace Popular {
    inline namespace V3_2 { // default
        double f6(double);

        int f6(int i) {
            std::cout << "V3_2::f6(int) is called" << std::endl;
            return i;
        }

        template<typename T>
        class C {
        };
    }

    namespace V3_0 {
        double f6(double d) {
            std::cout << "V3_0::f6(double) is called" << std::endl;
            return d;
        }
        // ...
    }

    namespace V2_4_2 {
        double f6(double d) {
            std::cout << "V2_4_2::f6(double) is called" << std::endl;
            return d;
        }

        template<typename T>
        class C {
        };
    }
}

using namespace Popular;

void f6_1() {
    f6(1);         // Popular::V3_2::f6(int);
    V3_0::f6(1);   // Popular::V3_0::f6(double);
    V2_4_2::f6(1); // Popular::V2_4_2::f6(double);
}

void execute6() {
    std::cout << "-----14.4.6 version control-----" << std::endl;
    f6_1();
}

//===--------------------------------------------------------------===//
// 14.4.7 nested namespace
//===--------------------------------------------------------------===//

namespace X7 {
    // ...all my declaration...
}

void h7();

namespace X7 {
    void g7();
    // ...
    namespace Y7 {
        void f7() {}

        void ff7();
        // ...
    }
}

void X7::Y7::ff7() {
    f7();
    g7();
    h7();
}

void X7::g7() {
    // f7();  // Error: f7() is not in X7
    Y7::f7(); // OK
}

void h7() {
    // f7();      // Error: f7() is not in global
    // Y7::f7();  // Error: Y7 is not in global
    // X7::f7();  // Error: f7() is not in X7
    X7::Y7::f7(); // OK
}

//===--------------------------------------------------------------===//
// 14.4.8 anonymous namespace
//===--------------------------------------------------------------===//

namespace { // implicit using directive
    int a;

    int f8() {
        std::cout << "f8() is called";
    }

    int g8() {}
}

void execute8() {
    std::cout << "-----14.4.8 anonymous namespace-----" << std::endl;
    f8();
}

//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute5();
    execute6();
    execute8();
    return 0;
}
