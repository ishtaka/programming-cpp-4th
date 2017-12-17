#include <iostream>

//===--------------------------------------------------------------===//
// 7.5 pointer with const
//===--------------------------------------------------------------===//

const int model = 90; // model is const
const int v[] = {1, 2, 3, 4}; // v[i] is const
// const int x; // Error: lack of initializer

void f() {
    // model = 200; Error
    // v[2] = 3; Error
}

void f1(char *p) {
    char s[] = "Gorm";

    const char *pc = s; // pointer to const
    //pc[3] = 'g';      // Error: pc points const
    std::cout << pc << std::endl;
    pc = p; // OK
    std::cout << pc << std::endl;

    char *const cp = s; // const pointer
    cp[3] = 'a'; // OK
    // cp = p; // Error: cp is const
    std::cout << cp << std::endl;
    std::cout << s << std::endl;

    const char *const cpc = s; // const pointer to const
    // cpc[3] = 'a'; // Error: cpc points const
    // cpc = p       // Error: cpc is const
}

void f2() {
    int a = 1;
    const int c = 2;

    const int *p1 = &c; // OK
    const int *p2 = &a; // OK
    int *p3 = &a;       // OK
    // int *p3 = &c;    // Error: initialize int* by const int*
    *p3 = 7;

    std::cout << a << std::endl;
}

void execute() {
    std::cout << "-----7.5 pointer with const-----" << std::endl;
    char c[] = "Test";
    f1(c);
    f2();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}
