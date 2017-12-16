#include <iostream>

void f() {
    char c = 'a';
    char *p = &c; // p hold c address : & is address operator
    char c2 = *p; // c2 == 'a' : * is dereferencing operator
    std::cout << c2 << std::endl;
}

void execute() {
    std::cout << "-----7.2 pointer-----" << std::endl;
    f();
}

//===--------------------------------------------------------------===//
// 7.2.1 void*
//===--------------------------------------------------------------===//

void f1_1(int *pi) {
    void *pv = pi; // OK: implicit conversion from int* to void*
    // *pv; // Error: void* cannot dereference
    // ++pv; // Error: void* cannot increment

    int *pi2 = static_cast<int *>(pv);
    std::cout << *pi2 << std::endl;

    // double *pd1 = pv; // Error
    // double *pd2 = pi; // Error
    double *pd3 = static_cast<double *>(pv); // cast is not safe
    std::cout << *pd3 << std::endl;
}

void execute1() {
    std::cout << "-----7.2.1 void*-----" << std::endl;
    int i = 5;
    f1_1(&i);
}

//===--------------------------------------------------------------===//
// 7.2.2 nullptr
//===--------------------------------------------------------------===//

void f2_1() {
    int *pi = nullptr;
    double *pd = nullptr;
    // int i = nullptr; // Error: i is not pointer
}

void f2_2() {
    int *np1 = 0; // np1 become nullptr value
    std::cout << std::boolalpha << (np1 == nullptr) << std::endl;

    int *np2 = NULL; // use macro
    std::cout << std::boolalpha << (np2 == nullptr) << std::endl;
}

void execute2() {
    std::cout << "-----7.2.2 nullptr-----" << std::endl;
    f2_1();
    f2_2();
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute2();

    return 0;
}
