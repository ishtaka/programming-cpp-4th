#include <iostream>
#include <sstream>

//===--------------------------------------------------------------===//
// 13.4 forcing invariant
//===--------------------------------------------------------------===//

int debug_level = 3;
int max = 10;

struct Assert_error {
    std::string msg;
};

void f1(int n) { // n must be [1:max)
    if (2 < debug_level && (n <= 0 || max < n))
        throw Assert_error{"range problem"};
    // ...
}


namespace Assert {
    enum class Mode {
        throw_, terminate_, ignore_
    };

    constexpr Mode CURRENT_MODE = Mode::throw_;
    constexpr int CURRENT_LEVEL = 2;

    constexpr Mode current_mode = CURRENT_MODE;
    constexpr int current_level = CURRENT_LEVEL;
    constexpr int default_level = 1;

    constexpr bool level(int n) {
        return n <= current_level;
    }

    struct Error : std::runtime_error {
        Error(const std::string &p) : runtime_error(p) {}
    };

    // ...
}

namespace Assert {
    std::string compose(const char *file, int line, const std::string &message) {
        std::ostringstream os{"("};
        os << file << "," << line << "):" << message;
        return os.str();
    }

    template<bool condition = level(default_level), typename Except = Error>
    void dynamic(bool assertion, const std::string &message = "Assert::dynamic failed") {
        if (assertion)
            return;
        if (current_mode == Mode::throw_)
            throw Except{message};
        if (current_mode == Mode::terminate_)
            std::terminate();
    }

    template<>
    void dynamic<false, Error>(bool, const std::string &) { // do nothing
    }

    void dynamic(bool b, const std::string &s) { // default dealing
        dynamic<true, Error>(b, s);
    }

    void dynamic(bool b) { // default message
        dynamic<true, Error>(b);
    }
}

void f2(int n) { // n must be [1:max)
    Assert::dynamic<Assert::level(2), Assert::Error>(
            (1 <= n && n < max), Assert::compose(__FILE__, __LINE__, "range problem"));
    // ...
}

void f3(int n) { // n must be [1:max)
    Assert::dynamic((1 <= n && n < max), Assert::compose(__FILE__, __LINE__, "range problem"));
    // ...
}

void f4(int n) {
    Assert::dynamic(1 <= n && n < max);
}

void execute() {
    try {
        //f1(10);
        f1(11);
    } catch (Assert_error e) {
        std::cout << e.msg << std::endl;
    }

    try {
        f2(11);
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    try {
        f3(11);
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    try {
        f4(11);
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}
