#include <iostream>

using namespace std;

//===--------------------------------------------------------------===//
// 17.1 introduction
//===--------------------------------------------------------------===//

string ident(string arg) { // by value (copy to arg)
    return arg; // return string (move arg value to caller outside ident())
}

void execute() {
    string s1{"Adams"};     // initialize string (construct s1)
    s1 = ident(s1);         // copy s1 to ident()
                            // move ident(s1) result to s1
                            // s1 value becomes "Adams'
    cout << s1 << endl;
    cout << endl;

    string s2{"Pratchett"}; // initialize string (construct s2)
    s1 = s2;                // copy s2 value to s1
                            // s1 and s2 values become "Pratchett"
    cout << s1 << endl;
    cout << s2 << endl;
}

class X {
public:
    X(int);                  // "normal constructor" : construct object
    X();                     // default constructor
    X(const X &);            // copy constructor
    X(X &&);                 // move constructor
    X &operator=(const X &); // copy assignment: copy after clean up the assignment destination
    X &operator=(X &&);      // move assignment: move after clean up the assignment destination
    ~X();                    // destructor: cleanup
    // ...
};

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}
