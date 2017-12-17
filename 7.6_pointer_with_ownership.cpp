#include <iostream>

//===--------------------------------------------------------------===//
// 7.6 pointer with ownership
//===--------------------------------------------------------------===//

void confused(int *p) {
    // delete p ?
}

int global{7};

void execute() {
    std::cout << "------7.6 pointer with ownership-----" << std::endl;
    int *pn = new int {7};

    int i{7};
    int *q = &i;

    confused(pn);
    confused(q);
    confused(&global);
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}
