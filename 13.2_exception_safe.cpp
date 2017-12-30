#include <iostream>

//===--------------------------------------------------------------===//
// 13.2 guarantee of exception-safe
//===--------------------------------------------------------------===//

struct Bad {
};

void f(int i) {
    int *p = new int[10];
    // ...
    if (i < 0) {
        delete[] p; // delete before throw or leak
        throw Bad();
    }
    // ...
}

//===--------------------------------------------------------------===//

int main() {

    return 0;
}
