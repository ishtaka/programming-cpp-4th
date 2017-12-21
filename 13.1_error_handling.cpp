#include <iostream>
#include <random>

//===--------------------------------------------------------------===//
// 13.1.1 exception
//===--------------------------------------------------------------===//

std::random_device rnd;
std::uniform_int_distribution<int> rand_int{0, 1};

int do_task() {
    int result = rand_int(rnd);

    if (result)
        return result;
    else
        throw std::exception{};
}

void taskmaster() {
    try {
        auto result = do_task();
        // use result
        std::cout << result << std::endl;
    } catch (std::exception &e) {
        // do_task is failed: dealing with the problem
        std::cout << "Exception" << std::endl;
    }
}

struct Range_error {
};

void f1(int n) {
    const int max = 3;
    if (n < 0 || max < n)
        throw Range_error{};

    std::cout << n << std::endl;
}

void f2() {
    try {
        f1(2);
        f1(3);
        f1(4);
    } catch (Range_error) {
        std::cout << "Range_error" << std::endl;
    }
}

void execute() {
    taskmaster();
    std::cout << std::endl;
    f2();
}

//===--------------------------------------------------------------===//
// 13.1.2 conventional error handling
//===--------------------------------------------------------------===//

// terminate program
void f2_1() {
    int something_wrong = rand_int(rnd);
    std::cout << "something wrong = " << something_wrong << std::endl;
    if (something_wrong)
        exit(1);
}

// return error value
int f2_2() {
    int something_wrong = rand_int(rnd);
    if (something_wrong)
        return -1;

    return 1;
}

void f2_3() {
    std::cout << f2_2() << std::endl;
}

// Return a valid value, leave the program in error state
void f2_4() {
    double d = sqrt(-1.0);
    std::cout << d << std::endl; // nan
    d = sqrt(4.0);
    std::cout << d << std::endl; // 2
}

// call error handling function
void something_handler() {
    std::cout << "handling something " << std::endl;
}

void f2_5() {
    int something_wrong = 1;
    if (something_wrong)
        something_handler();
}

void execute2() {
    std::cout << "-----13.1.2 conventional error handling-----" << std::endl;
    f2_1();
    std::cout << std::endl;
    f2_3();
    std::cout << std::endl;
    f2_4();
    std::cout << std::endl;
    f2_5();
}

//===--------------------------------------------------------------===//
// 13.1.5 when an exception can not be used
//===--------------------------------------------------------------===//

class my_vector {
    int x;
public:
    my_vector(int n) : x{n} {}

    int invalid() {
        return x <= 0;
    }
};

void f5_1(int n) {
    my_vector x(n);
    if (x.invalid())
        std::cout << "error handling" << std::endl;
    else
        std::cout << "OK" << std::endl;
}

template<typename Value, typename Error_code>
std::pair<Value, Error_code> make_vector(int n) {
    auto error = static_cast<Error_code>(n <= 0);
    return std::pair<Value, Error_code>{n, error};
}

void f5_2(int n) {
    auto v = make_vector<int, int>(n); // return pair
    if (v.second) {
        std::cout << "error handling" << std::endl;
    }

    auto val = v.first;
    std::cout << val << std::endl;
}

void execute5() {
    std::cout << "-----13.1.5 when an exception can not be used-----" << std::endl;
    f5_1(1);
    f5_1(0);
    std::cout << std::endl;

    f5_2(1);
    f5_2(0);
    std::cout << std::endl;
}

//===--------------------------------------------------------------===//
// 13.1.6 hierarchical error handling
//===--------------------------------------------------------------===//

#define E_CFCTBLEWIT 1
#define E_CPLPLFCTBLEWIT 1

struct C_blewit {
    int error;

    C_blewit(int x) : error{x} {}
};

struct C_PLPL_blewit {
};

void c_function() {
    errno = E_CFCTBLEWIT;
}

void c_plus_plus_function() {
    throw C_PLPL_blewit{};
}

void callC() { // call C function form C++: convert errno to throw
    errno = 0;
    c_function();
    if (errno) {
        // if it is possible and necessary, local error handling
        throw C_blewit(errno);
    }
}

extern "C" void call_from_C() noexcept { // call C++ function from C: convert throw to errno
    try {
        c_plus_plus_function();
    } catch (...) {
        // if it is possible and necessary, local error handling
        errno = E_CPLPLFCTBLEWIT;
    }
}

void f6_1() {
    try {
        callC();
    } catch (...) {
        std::cout << "callC throw error" << std::endl;
    }
}

void f6_2() {
    call_from_C();
    if (errno)
        std::cout << "errno " << errno << std::endl;
}

void execute6() {
    std::cout << "-----13.1.6 hierarchical error handling-----" << std::endl;

    f6_1();
    std::cout << std::endl;
    f6_2();
}

//===--------------------------------------------------------------===//
// 13.1.7 exception and efficiency
//===--------------------------------------------------------------===//

bool f7_1(int x) noexcept {
    return static_cast<bool>(x);
}

bool f7_2(const char *c) noexcept {
    return static_cast<bool>(c);
}

bool f7_3() {
    char *s = "Test";

    if (f7_1(1)) {
        if (f7_2(s)) {
            // free(s);
            return true;
        } else {
            // free(s);
            return false;
        }
    } else {
        // free(s);
        return false;
    }
}

void execute7() {
    std::cout << "-----13.1.7 exception and efficiency-----" << std::endl;
    std::cout << std::boolalpha << f7_3() << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute2();
    execute5();
    execute6();
    execute7();
    return 0;
}
