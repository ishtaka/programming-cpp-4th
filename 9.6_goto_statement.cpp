#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 9.6 goto statement
//===--------------------------------------------------------------===//

void do_something(int n, int m, int a) {

    int nm[2][3] = {{1, 2, 3},
                    {4, 5, 6}};

    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            if (nm[i][j] == a)
                goto found;
        }
    }

    found: // nm[i][j] == a
    std::cout << "found " << a << std::endl;

}

void execute() {
    std::cout << "-----9.6 goto statement-----" << std::endl;
    do_something(2, 3, 5);
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}
