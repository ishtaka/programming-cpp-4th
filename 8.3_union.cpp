#include <iostream>
#include <vector>
#include <complex>

//===--------------------------------------------------------------===//
// 8.3 union
//===--------------------------------------------------------------===//

enum Type {
    str, num
};

union Value {
    char *s;
    int i;
};

struct Entry {
    char *name;
    Type t;
    Value v;
};

void f(Entry *p) {
    if (p->t == str)
        std::cout << p->v.s << std::endl;
}

union Fudge {
    int i;
    int *p;
};

int *cheat(int i) {
    Fudge a;
    a.i = i;
    return a.p; // bad
}

int *cheat2(int i) {
    return reinterpret_cast<int *>(i); // ugliness and danger
}

//===--------------------------------------------------------------===//
// 8.3.1 union and class
//===--------------------------------------------------------------===//

void f1_1(Entry a) {
    Entry b = a;
}

union U {
    int m1;
    std::complex<double> m2; // std::complex has constructor
    std::string m3;          // std::string has constructor
};

void f1_2(U x) {
    // U u;                  // Error: which default constructor?
    // U u2 = x;             // Error: which copy constructor?
    // u.m1 = 1;             // assignment to int member
    // std::string s = u.m3; // disaster
    // return;
}

union U2 {
    int a;
    const char *p{""};
};

U2 x1;    // x1.p == "" by default initialization

//===--------------------------------------------------------------===//
// 8.3.2 anonymous union
//===--------------------------------------------------------------===//

class Entry2 {
private:
    enum class Tag {
        number, text
    };
    Tag type;

    union { // anonymous union
        int i;
        std::string s;
    };
public:
    struct Bad_entry { // using as exception
    };

    std::string name;

    ~Entry2();

    Entry2 &operator=(const Entry2 &);

    Entry2(const Entry2 &);

    int number() const;

    std::string text() const;

    void set_number(int n);

    void set_text(const std::string &);
};

int Entry2::number() const {
    if (type != Tag::number)
        throw Bad_entry{};

    return i;
}

std::string Entry2::text() const {
    if (type != Tag::text)
        throw Bad_entry{};

    return s;
}

void Entry2::set_number(int n) {
    if (type == Tag::text) {
        s.~basic_string();
        type = Tag::number;
    }

    i = n;
}

void Entry2::set_text(const std::string &ss) {
    if (type == Tag::text)
        s = ss;
    else {
        new(&s) std::string{ss}; // placement syntax
        type = Tag::text;
    }
}

Entry2 &Entry2::operator=(const Entry2 &e) {
    if (type == Tag::text && e.type == Tag::text) {
        s = e.s;
        return *this;
    }

    if (type == Tag::text)
        s.~basic_string();

    switch (e.type) {
        case Tag::number:
            i = e.i;
            break;
        case Tag::text:
            new(&s) std::string{e.s}; // placement syntax
            type = e.type;
    }

    return *this;
}

Entry2::~Entry2() {
    if (type == Tag::text)
        s.~basic_string();
}

//===--------------------------------------------------------------===//

int main() {
    return 0;
}
