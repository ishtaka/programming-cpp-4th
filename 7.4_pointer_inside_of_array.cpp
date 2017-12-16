#include <iostream>

//===--------------------------------------------------------------===//
// 7.4 pointer inside of array
//===--------------------------------------------------------------===//

void f() {
    int v[] = {1, 2, 3, 4};
    int *p1 = v;
    int *p2 = &v[0];
    int *p3 = v + 4;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    int *p4 = v - 1; // undefined
    int *p5 = v + 7; // undefined
}

void f2() {
    char v[] = "Annemarie";
    char *p = v; // implicit type conversion char[] to char*
    std::cout << strlen(p) << std::endl;
    std::cout << strlen(v) << std::endl; // implicit type conversion char[] to char*

    // v = p; // Error: cannot assign
}

void execute() {
    std::cout << "-----7.4 pointer inside of array-----" << std::endl;
    f();
    f2();
};

//===--------------------------------------------------------------===//
// 7.4.1 operation of array
//===--------------------------------------------------------------===//

void f1_1(char v[]) {
    for (int i = 0; v[i] != 0; ++i)
        std::cout << v[i];

    std::cout << std::endl;
}

void f1_2(char v[]) {
    for (char *p = v; *p != 0; ++p)
        std::cout << *p;

    std::cout << std::endl;
}

template<typename T>
int byte_diff(T *p, T *q) {
    return static_cast<int>(reinterpret_cast<char *>(q) - reinterpret_cast<char *>(p));
}

void diff_test() {
    int vi[10];
    short vs[10];

    std::cout << vi << ' ' << &vi[1] << ' ' << &vi[1] - &vi[0] << ' ' << byte_diff(&vi[0], &vi[1]) << std::endl;
    std::cout << vs << ' ' << &vs[1] << ' ' << &vs[1] - &vs[0] << ' ' << byte_diff(&vs[0], &vs[1]) << std::endl;
}

void f1_3() {
    int v1[10];
    int v2[10];

    auto i1 = static_cast<int>(&v1[5] - &v1[3]); // i1 = 2;
    auto i2 = static_cast<int>(&v1[5] - &v2[3]); // undefined
    std::cout << i1 << std::endl;
    std::cout << i2 << std::endl;

    int *p1 = v2 + 2; // p1 = &v2[2]
    std::cout << &v2[2] << std::endl;
    std::cout << p1 << std::endl;

    int *p2 = v2 - 2; // undefined
    std::cout << v2 << std::endl;
    std::cout << p2 << std::endl;
}

void f1_4(char v[], int size) {
    for (int i = 0; i != size; ++i)
        std::cout << v[i];
    std::cout << std::endl;

    /*
    for (int x : v) // Error, is not a valid range type
        std::cout << x;
    */

    const int N = 7;
    char v2[N];
    for (int i = 0; i != N; ++i) {
        v2[i] = 'a';
        std::cout << v2[i];
    }
    std::cout << std::endl;

    for (int x : v2)
        std::cout << x << ' '; // range based for loop works for arrays with a known number of elements
    std::cout << std::endl;
}

void execute1() {
    std::cout << "-----7.4.1 operation of array-----" << std::endl;
    char v1[] = "Test";
    f1_1(v1);
    f1_2(v1);

    diff_test();

    f1_3();

    f1_4(v1, 4);
}

//===--------------------------------------------------------------===//
// 7.4.2 multidimensional array
//===--------------------------------------------------------------===//

int ma[3][5];

void init_ma() {
    for (int i = 0; i != 3; ++i)
        for (int j = 0; j != 5; ++j)
            ma[i][j] = 10 * i + j;
}

void print_ma() {
    for (int i = 0; i != 3; ++i)
        for (int j = 0; j != 5; ++j)
            std::cout << ma[i][j] << "\t";
    std::cout << std::endl;
}

void f2_1() {
    // int bad[3, 5]; // Error: , cannot use
    int good[3][5];
    // int ouch = good[1, 4]; // Error: int initialized by int*
    int nice = good[1][4];
}

void execute2() {
    std::cout << "-----7.4.2 multidimensional array-----" << std::endl;
    init_ma();
    print_ma();
    f2_1();
}

//===--------------------------------------------------------------===//
// 7.4.3 array passing
//===--------------------------------------------------------------===//

void comp(double arg[10]) { // arg is double*
    for (int i = 0; i != 10; ++i)
        arg[i] += 99;
}

void f3_1() {
    double a1[10];
    double a2[5];
    double a3[100];

    comp(a1);
    comp(a2); // danger
    comp(a3);
}

void print_m35(int m[3][5]) {
    std::cout << "print_m35" << std::endl;
    for (int i = 0; i != 3; ++i)
        for (int j = 0; j != 5; ++j)
            std::cout << m[i][j] << "\t";
    std::cout << std::endl;
}

void print_mi5(int m[][5], int dim1) {
    std::cout << "print_mi5" << std::endl;
    for (int i = 0; i != dim1; ++i)
        for (int j = 0; j != 5; ++j)
            std::cout << m[i][j] << "\t";
    std::cout << std::endl;
}

void print_mij(int *m, int dim1, int dim2) {
    std::cout << "print_mij" << std::endl;
    for (int i = 0; i != dim1; ++i)
        for (int j = 0; j != dim2; ++j)
            std::cout << m[i * dim2 + j] << "\t";
    std::cout << std::endl;
}


void execute3() {
    std::cout << "-----7.4.3 array passing-----" << std::endl;
    f3_1();

    int v[3][5] = {
            {0,  1,  2,  3,  4},
            {10, 11, 12, 13, 14},
            {20, 21, 22, 23, 24}
    };

    print_m35(v);
    print_mi5(v, 3);
    print_mij(&v[0][0], 3, 5);
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute3();

    return 0;
}
