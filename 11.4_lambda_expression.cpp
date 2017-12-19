#include <iostream>
#include <vector>
#include <map>
#include <future>

//===--------------------------------------------------------------===//
// 11.4.1 implementation model
//===--------------------------------------------------------------===//

void print_modulo(const std::vector<int> &v, std::ostream &os, int m) {
    std::for_each(begin(v), end(v),
                  [&os, m](int x) { if (x % m == 0) os << x << std::endl; });
}

class Modulo_print {
    std::ostream &os;
    int m;
public:
    Modulo_print(std::ostream &s, int mm) : os(s), m(mm) {} // capture
    void operator()(int x) const {
        if (x % m == 0)
            os << x << std::endl;
    }
};

void print_modulo1(const std::vector<int> &v, std::ostream &os, int m) {
    std::for_each(begin(v), end(v), Modulo_print{os, m});
}

void execute1() {
    std::cout << "-----11.4.1 implementation model-----" << std::endl;
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    print_modulo(v, std::cout, 2);
    print_modulo1(v, std::cout, 3);
}

//===--------------------------------------------------------------===//
// 11.4.2 transformation to lambda expression
//===--------------------------------------------------------------===//

void print_modulo2_1(const std::vector<int> &v, std::ostream &os, int m) {
    class Modulo_print {
        std::ostream &os;
        int m;
    public:
        Modulo_print(std::ostream &s, int mm) : os(s), m(mm) {} // capture
        void operator()(int x) const {
            if (x % m == 0)
                os << x << std::endl;
        }
    };

    std::for_each(begin(v), end(v), Modulo_print{os, m});
}

void print_modulo2_2(const std::vector<int> &v, std::ostream &os, int m) {
    auto Modulo_print = [&os, m](int x) { if (x % m == 0) os << x << std::endl; };

    std::for_each(begin(v), end(v), Modulo_print);
}

template<typename C, typename Fct>
void print_modulo2_3(const C &v, std::ostream &os, int m, Fct f) {
    for (auto x : v)
        if (f(x) % m == 0) os << f(x) << std::endl;
};

void f2_1(std::vector<int> &v, std::map<std::string, int> &m) {
    print_modulo2_3(v, std::cout, 2, [](int x) { return x; });
    print_modulo2_3(m, std::cout, 2, [](std::pair<const std::string, int> &x) { return x.second; });
}

void execute2() {
    std::cout << "-----11.4.2 transformation to lambda expression-----" << std::endl;
    std::vector<int> v = {1, 2, 3, 4};
    std::map<std::string, int> m = {
            {"test1", 1},
            {"test2", 2},
            {"test3", 3},
            {"test4", 4}
    };

    f2_1(v, m);
}

//===--------------------------------------------------------------===//
// 11.4.3.3 lambda expression with this
//===--------------------------------------------------------------===//

class Request {
    std::function<std::map<std::string, std::string>(const std::map<std::string, std::string> &)> oper;

    std::map<std::string, std::string> values;
    std::map<std::string, std::string> results;
public:
    Request(const std::string &s);

    std::future<void> execute() {
        return std::async([this]() { results = oper(values); });
    }
};

//===--------------------------------------------------------------===//
// 11.4.4 lambda expression and return
//===--------------------------------------------------------------===//

void f4(double y) {};

void f4_1(double y) {
    auto z0 = [&] { f4(y); };                             // return type is void
    auto z1 = [=](int x) { return x + y; };               // return type is double
    // auto z2 = [y] { if (y) return 1; else return 2; }; // Error:
    auto z3 = [y]() { return (y) ? 1 : 2; };              // return type is int
    auto z4 = [y]() -> int { if (y) return 1; else return 2; }; // OK: explicit return
}

void execute4() {
    f4_1(1.2);
}
//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute2();
    execute4();

    return 0;
}
