#include <iostream>
#include <cmath>

//===--------------------------------------------------------------===//
// 10.4 constant expression
//===--------------------------------------------------------------===//

int x1 = 7;
constexpr int x2 = 7;

// constexpr int x3 = x1; // Error: initializer is not constexpr
constexpr int x4 = x2;    // OK

void f1() {
    // constexpr int y3 = x1; // Error: initializer is not constexpr
    constexpr int y4 = x2;    // OK
}

constexpr int isqrt_helper(int sq, int d, int a) {
    return sq <= a ? isqrt_helper(sq + d, d + 2, a) : d;
}

constexpr int isqrt(int x) {
    return isqrt_helper(1, 3, x) / 2 - 1;
}

constexpr int s1 = isqrt(9);    // s1 = 3
constexpr int s2 = isqrt(1234);

void execute() {
    std::cout << "-----10.4 constant expression-----" << std::endl;

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}

//===--------------------------------------------------------------===//
// 10.4.2 const in constant expression
//===--------------------------------------------------------------===//

const int x_2 = 7;
const std::string s_2 = "asdf";
const int y_2 = static_cast<const int>(sqrt(x_2));

constexpr int xx = x_2;            // OK;
// constexpr std::string ss = s_2; // Error: s_2 is not constexpr
// constexpr int yy = y_2;         // Error: sqrt(x) is not constexpr

//===--------------------------------------------------------------===//
// 10.4.3 literal type
//===--------------------------------------------------------------===//

struct Point {
    int x, y, z;

    constexpr Point up(int d) const { return {x, y, z + d}; }

    constexpr Point move(int dx, int dy) const { return {x + dx, y + dy}; }
    // ...
};

constexpr Point origo{0, 0};
constexpr int z = origo.x;

constexpr Point a[] = {
        origo, Point{1, 1}, Point{2, 2}, origo.move(3, 3)
};

constexpr int p = a[1].x;          // x = 1;
// constexpr Point xy{0, sqrt(2)}; // Error: sqrt(2) is not constexpr

constexpr int square(int x) {
    return x * x;
}

constexpr int radial_distance(Point p) {
    return isqrt(square(p.x) + square(p.y) + square(p.z));
}

constexpr Point p1{10, 20, 30}; // default constructor is constexpr
constexpr Point p2{p1.up(20)};  // Point::up() is constexpr
constexpr int dist = radial_distance(p2);

void execute3() {
    std::cout << "-----10.4.3 literal type-----" << std::endl;
    std::cout << p1.x << ' ' << p1.y << ' ' << p1.z << std::endl;
    std::cout << p2.x << ' ' << p2.y << ' ' << p2.z << std::endl;
    std::cout << dist << std::endl;
}

//===--------------------------------------------------------------===//
// 10.4.5 address constant expression
//===--------------------------------------------------------------===//

constexpr const char *ptr1 = "asdf";
constexpr const char *ptr2 = ptr1;        // OK
// constexpr const char *ptr2 = ptr1 + 2; // Error: compiler don't know p1's value
constexpr char c = ptr1[2];               // OK: c == 'd'

void execute5() {
    std::cout << "-----10.4.5 address constant expression-----" << std::endl;
    std::cout << c << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute3();
    execute5();
    return 0;
}
