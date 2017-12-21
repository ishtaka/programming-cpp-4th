#include <iostream>

//===--------------------------------------------------------------===//
// 12.6 macro
//===--------------------------------------------------------------===//

#define NAME rest of line
/*
 named = NAME

 named = rest of line
*/

#define MAC(x, y) argument1: x argument2: y
/*
 expanded = MAC(foo bar, yuk yu)

 expanded = argument1: foo bar argument2: yuk yuk
*/

#define PRINT(a, b) std::cout << (a) << (b)
#define PRINT(a, b, c) std::cout << (a) << (b) << (c) // wrong? not overloading but second definition

#define FAC(n) (n > 1) ? n * FAC(n - 1) : 1 // wrong: recursive macro

#define CASE break;case
#define FOREVER for(;;)

#define SQUARE(a) a*a
#define INCR_xx (xx)++

int xx = 0;

void f1(int xx) {
    int y = SQUARE(xx + 2); // y = xx + 2 * xx + 2 : y = xx + (2 * xx) + 2
    INCR_xx;                // increment argument xx, not global xx;
    std::cout << y << std::endl;
    std::cout << xx << std::endl;
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void f2() {
    int x = 1;
    int y = 10;
    int z = MIN(x++, y++); // x = 3, y = 11

    std::cout << x << std::endl; // 3
    std::cout << y << std::endl; // 11
    std::cout << z << std::endl; // 2
}

#define M2(a) something(a) /* properly thought-out comments */

const int answer = 42;

template<typename T>
inline const T &min(const T &a, const T &b) {
    return (a < b) ? a : b;
}

#define NAME2(a, b) a##b

int NAME2(hack, cah)() {
    std::cout << "hackcah" << std::endl;
    return 1;
}

#define printx(x) std::cout << #x " = " << x << std::endl;

int a = 7;
std::string str1 = "asdf";

void f3() {
    printx(a);    // std::cout <<  "a" " = " << a << std::endl;
    printx(str1); // std::cout <<  "str1" " = " << str1 << std::endl;
}

#undef X


#define EMPTY() std::cout << "empty" << std::endl;

void f4() {
    EMPTY(); // std::cout << "empty" << std::endl;
    //EMPTY  // Error
}

#define err_print(...) fprintf(stderr, "error: %s %d\n", __VA_ARGS__)

void execute() {
    std::cout << "-----12.6 macro-----" << std::endl;

    f1(2);
    std::cout << xx << std::endl;
    std::cout << std::endl;

    f2();
    std::cout << std::endl;

    std::cout << hackcah() << std::endl;
    std::cout << std::endl;

    f3();
    std::cout << std::endl;

    f4();
    std::cout << std::endl;

    err_print("The answer", 54);
}

//===--------------------------------------------------------------===//
// 12.6.1 conditional compilation
//===--------------------------------------------------------------===//

#ifdef IDENTIFIER
#endif

#define arg_two x

int f1_1(int a
#ifdef arg_two
        , int b
#endif
) {
    std::cout << a << std::endl;
#ifdef arg_two
    std::cout << b << std::endl;
#endif
}

struct Call_info {
    int *arg_one;
    int *arg_two; // confusion
};

void execute1() {
    std::cout << "-----12.6.1 conditional compilation-----" << std::endl;
    f1_1(1, 2);

}

//===--------------------------------------------------------------===//
// 12.6.2 predefined macros
//===--------------------------------------------------------------===//

void execute2() {
    std::cout << "-----12.6.2 predefined macros-----" << std::endl;

    std::cout << __func__ << "() in file"
              << __FILE__ << " on line "
              << __LINE__ << std::endl;
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();
    return 0;
}
