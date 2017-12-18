#include <iostream>

//===--------------------------------------------------------------===//
// 10.3 operator overview
//===--------------------------------------------------------------===//

void execute() {
    int x, y, z;
    bool b1 = not(x or y) and z;
    bool b2 = !(x || y) && z;

    int x1, x2, x3;
    int x4_1 = compl(x1 bitor x2) bitand x3;
    int x4_2 = -(x1 | x2) & x3;
}

//===--------------------------------------------------------------===//
// 10.3.1 calculation results
//===--------------------------------------------------------------===//

void f1_1(int x, int y) {
    int j = x = y;
    std::cout << x << std::endl; // 3
    std::cout << j << std::endl; // 3

    int *p = &++x;               // p points to x
    // int *q = &(x++);          // Error: x++ is not lvalue
    int *p2 = &(x > y ? x : y);  // address of the larger int value
    // int &r = (x < y) ? x : 1; // Error: 1 is not lvalue

    std::cout << &x << std::endl;
    std::cout << p << std::endl;
    std::cout << p2 << std::endl;
}

void execute1() {
    std::cout << "-----10.3.1 calculation results-----" << std::endl;
    f1_1(1, 3);
}

//===--------------------------------------------------------------===//
// 10.3.2 order of evaluation
//===--------------------------------------------------------------===//
void f2_1(int x, int y) {
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

void f2_2(int x) {
    std::cout << x << std::endl;
}

void execute2() {
    std::cout << "-----10.3.2 order of evaluation-----" << std::endl;

    int v[]{1, 3, 5, 7};
    int i = 1;
    v[i] = i++; // undefined result
    for (int j = 0; j != 4; ++j)
        std::cout << v[j] << ' ';
    std::cout << std::endl;

    std::cout << "v[i] = " << v[i] << std::endl;
    std::cout << "i = " << i << std::endl;
    f2_1(v[i], i++); // undefined eval order

    std::cout << "i = " << i << std::endl;
    std::cout << "v[i] = " << v[i] << std::endl;
    f2_2((v[i], i++)); // eval is i++
}

//===--------------------------------------------------------------===//
// 10.3.3 operator precedence
//===--------------------------------------------------------------===//

void execute3() {
    std::cout << "-----10.3.3 operator precedence-----" << std::endl;
    int a;
    int b = (a = 2, a + 1); // b == 3
    std::cout << b << std::endl;

    int mask = 0;

    int i = 1;
    if (i & mask == 0) { // == i & (mask == 0)
        std::cout << "i & (mask == 0)" << std::endl;
    }

    int x = 10;
    if (0 <= x <= 99) { // (0 <= x) <= 99; == (true <= 99); == (1 <= 99) == always true
        std::cout << "always true" << std::endl;
    }
}

//===--------------------------------------------------------------===//
// 10.3.4 temporary object
//===--------------------------------------------------------------===//

void f4_1(std::string &s1, std::string &s2, std::string &s3) {
    const char *cs = (s1 + s2).c_str(); // (s1 + s2).c_str() is temporary object
    std::cout << cs << std::endl;
    if (8 < strlen(cs = (s2 + s3).c_str()) && cs[0] == 'a') {
        std::cout << cs << std::endl;
    }
}

void f4_2(std::string &s1, std::string &s2, std::string &s3) {
    std::cout << s1 + s2 << std::endl;
    std::string s = s2 + s3;
    if (8 < s.length() && s[0] == 'a') {
        std::cout << s << std::endl;
    }
}

void g4(const std::string &s1, const std::string &s2) {
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}

void f4_3(std::string &s1, std::string s2) {
    const std::string &s = s1 + s2;
    std::string ss = s1 + s2;

    g4(s, ss); // can use s and ss
}


void execute4() {
    std::cout << "-----10.3.4 temporary object-----" << std::endl;

    std::string s1{"string1"};
    std::string s2{"as"};
    std::string s3{"string3"};
    f4_1(s1, s2, s3);
    f4_2(s1, s2, s3);

    f4_3(s1, s3);
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    execute3();
    execute4();

    return 0;
}
