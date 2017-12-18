#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 9.5.1 range-based for statement
//===--------------------------------------------------------------===//

int sum(std::vector<int> &v) {
    int s = 0;
    for (int x: v)
        s += x;

    return s;
}

int sum2(std::vector<int> &v) {
    int s = 0;
    for (auto p = begin(v); p != end(v); ++p)
        s += *p;

    return s;
}

void incr(std::vector<int> &v) {
    for (int &x : v)
        ++x;
}

template<typename T>
T accume(std::vector<T> &v) {
    T sum = 0;
    for (const T &x : v)
        sum += x;

    return sum;
}

void print1(const std::vector<int> &v) {
    for (auto &x : v)
        std::cout << x << ' ';
    std::cout << std::endl;
}

void execute1() {
    std::cout << "-----9.5.1 range-based for statement-----" << std::endl;

    std::vector<int> v{1, 2, 3, 4};
    std::cout << sum(v) << std::endl;
    std::cout << sum2(v) << std::endl;

    incr(v);
    print1(v);

    std::cout << accume<int>(v) << std::endl;
}

//===--------------------------------------------------------------===//
// 9.5.2 for statement
//===--------------------------------------------------------------===//

void print2(const int *v, int size) {
    for (int i = 0; i != size; ++i)
        std::cout << v[i] << ' ';
    std::cout << std::endl;
}

void f2_1(int v[], int max) {
    for (int i = 0; i != max; ++i)
        v[i] = i * i;

    print2(v, max);
}

void f2_2(int v[], int max) {
    int i = 0;
    while (i != max) {
        v[i] = i * i;
        ++i;
    }

    print2(v, max);
}

void execute2() {
    std::cout << "-----9.5.2 for statement-----" << std::endl;

    int v[] = {1, 2, 3, 4};
    f2_1(v, 4);
    f2_2(v, 4);
}

//===--------------------------------------------------------------===//
// 9.5.3 while statement
//===--------------------------------------------------------------===//

template<typename Iter, typename Value>
Iter find(Iter first, Iter last, Value val) {
    while (first != last && *first != val)
        ++first;

    return first;
};

//===--------------------------------------------------------------===//
// 9.5.4 do statement
//===--------------------------------------------------------------===//

void print_backwards(char a[], int i) { // i must be plus
    std::cout << '{';

    do {
        std::cout << a[--i];
    } while (i);

    std::cout << '}' << std::endl;
}

void execute4() {
    std::cout << "-----9.5.4 do statement-----" << std::endl;

    char str[] = {"Test"};
    std::cout << str << std::endl;
    print_backwards(str, static_cast<int>(strlen(str)));
}

//===--------------------------------------------------------------===//
// 9.5.5 end of loop
//===--------------------------------------------------------------===//

void f5_1(std::vector<std::string> &v, std::string terminator) {
    char c;
    std::string s;
    while (std::cin >> c) {
        // ...
        if (c == '\n')
            break;
        std::cout << c;
        // ...
    }
}

bool prime(std::string s) {
    return s == "prime";
}

std::string find_prime(std::vector<std::string> &v) {
    for (int i = 0; i != v.size(); ++i) {
        if (!prime(v[i]))
            continue;

        return v[i];
    }
}

std::string find_prime2(std::vector<std::string> &v) {
    for (int i = 0; i != v.size(); ++i) {
        if (prime(v[i]))
            return v[i];
    }
}

void execute5() {
    std::cout << "-----9.5.5 end of loop-----" << std::endl;

    std::vector<std::string> v{"one", "two", "prime", "end"};
    std::cout << find_prime(v) << std::endl;
    std::cout << find_prime2(v) << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute1();
    execute2();
    execute4();
    execute5();
    return 0;
}
