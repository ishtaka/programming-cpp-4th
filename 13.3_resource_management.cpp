#include <iostream>

//===--------------------------------------------------------------===//
// 13.3 resource management
//===--------------------------------------------------------------===//

void use_file1(const char *fn) {
    FILE *f = fopen(fn, "r");

    // use f

    fclose(f);
}

void use_file2(const char *fn) { // poor code
    FILE *f = fopen(fn, "r");

    try {
        // use f
    } catch (...) {
        fclose(f);
        throw;
    }

    fclose(f);
}

void acquire() {
    // acquire resource 1
    // ...
    // acquire resource n

    // use resources

    // free resource n
    // ...
    // free resource 1
}

class File_ptr {
    FILE *p;
public:
    File_ptr(const char *n, const char *a) // open file n
            : p{fopen(n, a)} {
        if (p == nullptr)
            throw std::runtime_error{"File_ptr: Can't open file"};
    }

    File_ptr(const std::string &n, const char *a) // open file n
            : File_ptr{n.c_str(), a} {}

    explicit File_ptr(FILE *pp) // assume pp's ownership
            : p{pp} {
        if (p == nullptr)
            throw std::runtime_error{"File_ptr: nullptr"};
    }

    // ... suitable move and copy ...

    ~File_ptr() {
        fclose(p);
    }

    operator FILE *() {
        return p;
    }
};

void use_file3(const char *fn) {
    File_ptr f(fn, "r");

    // use f
}

class X {
    std::unique_lock<std::mutex> lck;
    File_ptr p;
public:
    X(const char *file, std::mutex &m)
            : lck{m},          // acquire 'm'
              p{file, "rw"} {} // acquire 'file'
    // ...
};

void execute() {
    use_file1("test.txt");
    use_file2("test.txt");
    use_file3("test.txt");
}

//===--------------------------------------------------------------===//
// 13.3.1 finally
//===--------------------------------------------------------------===//

template<typename F>
struct Final_action {
    Final_action(F f) : clean{f} {}

    ~Final_action() { clean(); }

    F clean;

    Final_action &operator=(const Final_action &) = delete;
};

template<typename F>
Final_action<F> finally(F f) {
    return Final_action<F>(f);
}

void f_1() {
    int *p = new int[7];                          // better to use unique_ptr
    int *buf = (int *) malloc(100 * sizeof(int)); // C style allocate

    auto act1 = finally([&] {
        delete p;
        free(buf);  // C style
        std::cout << "Goodbye, Cruel world" << std::endl;
    });

    int var = 0;
    std::cout << "var = " << var << std::endl;

    {
        var = 1;
        auto act2 = finally([&] {
            std::cout << "finally!" << std::endl;
            var = 7;
        });
        std::cout << "var = " << var << std::endl;
    } // act2 is called here

    std::cout << "var = " << var << std::endl;
} // act1 is called here

void execute_1() {
    std::cout << "-----13.3.1 finally-----" << std::endl;
    f_1();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute_1();
    return 0;
}
