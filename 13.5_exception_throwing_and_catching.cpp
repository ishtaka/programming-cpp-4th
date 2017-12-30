#include <iostream>
#include <vector>
#include <future>

//===--------------------------------------------------------------===//
// 13.5.1 throwing exception
//===--------------------------------------------------------------===//

class No_copy {
    No_copy(const No_copy &) = delete;
};

class My_error {
};

void f1_1(int n) {
    switch (n) {
        case 0: throw My_error{};   // OK
        // case 1: throw No_copy{}; // Error: can't copy No_copy
        // case 2: throw My_error;  // Error: My_error is not object but type
    }
}

void f1_2() {
    std::string s = "not";
    throw My_error{};
    std::string s2 = "at all";
}

void f1_3() {
    std::string s = "excess";
    {
        std::string s = "or";
        f1_2();
    }
}

void f1_4() {
    std::string name{"Byron"};
    try {
        std::string s = "in";
        f1_3();
    } catch (My_error) {
        std::cout << "deleted in the order of ";
        std::cout << "'not, or, excess, in'" << std::endl;
    }
}

struct Some_error {
};

void f1_5() {
    // ...
    bool something_wrong = true;
    if (something_wrong)
        throw Some_error{};
}

struct My_error2 : std::runtime_error {
    My_error2(const std::string &s) : runtime_error(s) {}

    const char *what() const noexcept { return "My_error2"; }
};

void f1_6(int n) { // throw some exceptions
    if (n)
        throw std::runtime_error{"I give up!"};
    else
        throw My_error2{"Test"};
}

void f1_7(int n) {
    try {
        f1_6(n);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void execute1() {
    std::cout << "-----13.5.1 throwing exception-----" << std::endl;

    try {
        f1_1(0);
    } catch (My_error) {
    }
    std::cout << std::endl;

    f1_4();
    std::cout << std::endl;

    try {
        f1_5();
    } catch (Some_error) {
        std::cout << "It is possible to understand Error only by name" << std::endl;
    }
    std::cout << std::endl;

    f1_7(1);
    f1_7(0);
}

//===--------------------------------------------------------------===//
// 13.5.1.1 noexcept function
//===--------------------------------------------------------------===//

double compute(double) noexcept; // don't throw exception

double compute(double x) noexcept {
    std::string s = "Courtney and Anya";
    std::vector<double> tmp(10); // possibility of throwing exception
    // ...
    return x;
}

//===--------------------------------------------------------------===//
// 13.5.1.2 noexcept operator
//===--------------------------------------------------------------===//

template<typename T>
constexpr bool Is_pod() {
    return true;
}

template<typename T>
void my_fct(T &x) noexcept(Is_pod<T>());

template<typename T>
constexpr T f1_2_1(T t) noexcept {
    return t;
}

template<typename T>
void call_f1_2_1(std::vector<T> &v) noexcept(noexcept(f1_2_1(v[0]))); // don't valid noexcept()

//===--------------------------------------------------------------===//
// 13.5.1.3 exception specification
//===--------------------------------------------------------------===//

struct Bad {
};
struct Worse {
};

void f1_3_1(int n) throw(Bad, Worse) { // exceptions are limited to Bad or Worse
}

void f1_3_2() throw() { // don't throw exception == noexcept
}

//===--------------------------------------------------------------===//
// 13.5.2 catching exception
//===--------------------------------------------------------------===//

struct Error {
};

void f2_1() {
    int x1{};

    try {
        int x2 = x1;
        throw Error{};
    } catch (Error) {
        ++x1;    // OK
        // ++x2; // Error: x2 is not in scope
        int x3 = 7;
        // ...
    } catch (...) {
        // ++x3; // Error: x3 is not in scope
        // ...
    }

    ++x1;    // OK
    // ++x2; // Error: x2 is not in scope
    // ++x3; // Error: x3 is not in scope

    std::cout << x1 << std::endl;
}

void execute2() {
    std::cout << "-----13.5.2 catching exception-----" << std::endl;
    f2_1();
}

//===--------------------------------------------------------------===//
// 13.5.2.1 rethrow
//===--------------------------------------------------------------===//

struct Rethrow : std::runtime_error {
    Rethrow(const std::string &s) : runtime_error(s) {}
};

void f2_1_1() {
    bool can_handle_it_completely = false;

    try {
        throw Rethrow{"Rethrow Exception"};
    } catch (std::exception &err) {
        if (can_handle_it_completely) {
            // ... handle it
            return;
        } else {
            // ... do something that can do here
            throw; // rethrow exception
        }
    }
}

void execute2_1() {
    std::cout << "-----13.5.2.1 rethrow-----" << std::endl;
    try {
        f2_1_1();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

//===--------------------------------------------------------------===//
// 13.5.2.2 catching all exceptions
//===--------------------------------------------------------------===//

void f2_2_1() {
    try {
        // do something
    } catch (std::exception &err) { // deal with all standard libraries exceptions
        throw;
    }
}

void f2_2_2() {
    try {
        // do something
    } catch (...) { // deal with all exceptions
        throw;
    }
}

//===--------------------------------------------------------------===//
// 13.5.2.3 multiple handlers
//===--------------------------------------------------------------===//

void f2_3_1() {
    try {
        // ...
    } catch (std::ios_base::failure) {
        // deal with every iostream errors
    } catch (std::exception &e) {
        // deal with all standard libraries exceptions
    } catch (...) {
        // deal with all exceptions
    }
}

//===--------------------------------------------------------------===//
// 13.5.2.4 function try block
//===--------------------------------------------------------------===//

void f2_4_1() try {
    // do something
} catch (...) {
    // deal with exceptions
}

class X {
    std::vector<int> vi;
    std::vector<std::string> vs;
    // ...
public:
    X(int, int);
    // ...
};

X::X(int sz1, int sz2) try : vi(sz1), vs(sz2) {
    // ...
} catch (std::exception &err) {
    // ...
}

//===--------------------------------------------------------------===//
// 13.5.2.5 forced termination
//===--------------------------------------------------------------===//

using terminate_handler = void (*)(); // <exception>

[[noreturn]] void my_handler() { // can't return from terminate handler
    // ... do original terminate
}

void dangerous() { // really dangerous!
    terminate_handler old = std::set_terminate(my_handler);
    // ...
    std::set_terminate(old);
}

void execute2_5() {
    dangerous();
}

//===--------------------------------------------------------------===//
// 13.5.3 exception with thread
//===--------------------------------------------------------------===//

std::promise<int> prom{};

void f3_1() {
    try {
        // do something
    } catch (...) {
        prom.set_exception(std::current_exception());
    }
}

//===--------------------------------------------------------------===//

int main() try {
    execute1();
    execute2();
    execute2_1();
    execute2_5();
} catch (const std::range_error &) {
    std::cerr << "range error: Not again!" << std::endl;
} catch (const std::bad_alloc &) {
    std::cerr << "new ran out of memory" << std::endl;
} catch (...) {
    // ...
}
