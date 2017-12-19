#include <iostream>

//===--------------------------------------------------------------===//
// 11.1.2 bitwise logical operation
//===--------------------------------------------------------------===//

void f2_1() {
    auto state = std::ios_base::badbit;
    if (state & (std::ios_base::badbit | std::ios_base::failbit)) {
        std::cout << "stream is not good" << std::endl;
    }
}

constexpr unsigned short middle(int a) {
    static_assert(sizeof(int) == 4, "unexpected int size");
    static_assert(sizeof(short) == 2, "unexpected short size");

    return static_cast<unsigned short>((a >> 8) & 0xFFFF);
}

void execute2() {
    std::cout << "-----11.1.2 bitwise logical operation-----" << std::endl;

    f2_1();

    int x = 0xFF00FF00;  // assume that sizeof(int) == 4
    short y = middle(x); // y = 0x00FF
    std::cout << std::hex << y << std::endl;
}

//===--------------------------------------------------------------===//
// 11.1.3 conditional expression
//===--------------------------------------------------------------===//

void f3_1() {
    int a = 1;
    int b = 10;

    int max;
    if (a <= b)
        max = b;
    else
        max = a;
    std::cout << std::dec << max << std::endl;

    max = (a <= b) ? b : a;
    std::cout << std::dec << max << std::endl;
}

void fct(int *p) {
    int i = (p) ? *p : throw std::runtime_error{"unexpected nullptr"};
    std::cout << i << std::endl;
}

void execute3() {
    std::cout << "-----11.1.3 conditional expression-----" << std::endl;

    f3_1();

    int x = 5;
    fct(&x);
}

//===--------------------------------------------------------------===//
// 11.1.4 increment, decrement
//===--------------------------------------------------------------===//

void f4_1() {
    int x = 1;
    int y1 = ++x; // y = (x = x + 1);
    int y2 = x++; // y = (t = x, x = x + 1, t);
    std::cout << y1 << std::endl;
    std::cout << x << std::endl;
    std::cout << y2 << std::endl;
}

void cpy0(char *p, const char *q) {
    int length = static_cast<int>(strlen(q));
    for (int i = 0; i <= length; i++)
        p[i] = q[i];
}

void cpy0_1(char *p, const char *q) {
    int i;
    for (i = 0; q[i] != 0; i++)
        p[i] = q[i];
    p[i] = 0; // 0 for end
}

void cpy0_2(char *p, const char *q) {
    while (*q != 0) {
        *p++ = *q++;
    }
    *p = 0; // 0 for end
}

void cpy0_3(char *p, const char *q) {
    while ((*p++ = *q++) != 0) {}
}

void cpy(char *p, const char *q) {
    while ((*p++ = *q++));
}

void execute4() {
    std::cout << "-----11.1.4 increment, decrement-----" << std::endl;

    f4_1();

    char p[5];
    char q[] = "Test";
    cpy(p, q);
    std::cout << p << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute2();
    execute3();
    execute4();
    return 0;
}
