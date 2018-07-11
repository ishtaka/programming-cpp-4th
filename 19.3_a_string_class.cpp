#include <iostream>
#include <string>
#include <vector>

using namespace std;

//===--------------------------------------------------------------===//
// 19.3 a String class
//===--------------------------------------------------------------===//

class String {
public:
    String();               // default constructor: x{""}

    String(const char *p);  // constructor from C-style string: x{"Euler"}

    String(const String &);            // copy constructor
    String &operator=(const String &); // copy assignment

    String(String &&x);                // move constructor
    String &operator=(String &&x);     // move assignment

    ~String() { if (short_max < sz) delete[] ptr; }

    char &operator[](int n) { return ptr[n]; } // unchecked element access

    char operator[](int n) const { return ptr[n]; }

    char &at(int n) const { // range-checked element access
        check(n);
        return ptr[n];
    }

    String &operator+=(char c);                 // add c at end

    char *c_str() { return ptr; }               // C-style string access
    const char *c_str() const { return ptr; }

    int size() const { return sz; }             // number of elements

    int capacity() const {                      // elements plus available space
        return (sz <= short_max) ? short_max : sz + space;
    }

    int hash(const String &s) {
        if (s.size() == 0) return 0;
        int h{s[0]};                 // unchecked access to s
        for (int i{1}; i < s.size(); ++i) {
            h ^= s[i] >> 1;
        }
        return h;
    }

    void print_in_order(const String &s, const vector<int> &index) {
        for (auto x: index)
            cout << s.at(x) << '\n'; // checked access to s
    }

private:
    static const int short_max = 15;
    int sz;     // number of characters
    char *ptr;
    union {
        int space;              // unused allocated space
        char ch[short_max + 1]; // leave space for terminating 0
    };

    void check(int n) const {
        if (n < 0 || sz <= n)
            throw ::out_of_range("String::at()");
    }

    // ancillary member functions:
    void copy_from(const String &x);

    void move_from(String &x);
};

//===--------------------------------------------------------------===//
// 19.3.3.1 ancillary functions
//===--------------------------------------------------------------===//

char *expand(const char *ptr, int n) { // expand into free store
    char *p = new char[n];
    strcpy(p, ptr);
    return p;
}

void String::copy_from(const String &x) { // make *this a copy of x
    if (x.sz <= short_max) { // copy *this
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    } else {
        ptr = expand(x.ptr, x.sz + 1);
        sz = x.sz;
        space = 0;
    }
}

void String::move_from(String &x) {
    if (x.sz <= short_max) { // copy *this
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    } else {                 // grab the elements
        ptr = x.ptr;
        sz = x.sz;
        space = x.space;
        x.ptr = x.ch;
        x.sz = 0;
        x.ch[0] = 0;
    }
}

//===--------------------------------------------------------------===//
// 19.3.4 member functions
//===--------------------------------------------------------------===//

String::String()           // default constructor: x{""}
        : sz{0}, ptr{ch} { // ptr points to elements, ch is an initial location
    ch[0] = 0;
}

String::String(const char *p) :
        sz{static_cast<int>(strlen(p))},
        ptr{(sz <= short_max) ? ch : new char[sz + 1]},
        space{0} {
    strcpy(ptr, p); // copy characters into ptr from p
}

String::String(const String &x) { // copy constructor
    copy_from(x);
}

String::String(String &&x) {      // move constructor
    move_from(x);
}

String &String::operator=(const String &x) {
    if (this == &x) return *this; // deal with self-assignment
    char *p = (short_max < sz) ? ptr : 0;
    copy_from(x);
    delete[] p;
    return *this;
}

String &String::operator=(String &&x) {
    if (this == &x) return *this;     // deal with self-assignment(x = move(x) is insanity)
    if (short_max < sz) delete[] ptr; // delete target
    move_from(x);                     // does not throw
    return *this;
}

String &String::operator+=(char c) {
    if (sz == short_max) {   // expand to long string
        int n = sz + sz + 2; // double the allocation (+ 2 because of the terminating 0)
        ptr = expand(ptr, n);
        space = n - sz - 2;
    } else if (short_max < sz) {
        if (space == 0) {        // expand in free store
            int n = sz + sz + 2; // double the allocation (+ 2 because of the terminating 0)
            char *p = expand(ptr, n);
            delete[] ptr;
            ptr = p;
            space = n - sz - 2;
        } else {
            --space;
        }
    }

    ptr[sz] = c;   // add c at end
    ptr[++sz] = 0; // increase size and set terminator
    return *this;
}

//===--------------------------------------------------------------===//
// 19.3.5 helper functions
//===--------------------------------------------------------------===//

ostream &operator<<(ostream &os, const String &s) {
    return os << s.c_str();
}

istream &operator>>(istream &is, String &s) {
    s = "";   // clear the target string
    is >> ws; // skip whitespace
    char ch = '\0';
    while (is.get(ch) && !isspace(ch))
        s += ch;
    return is;
}

bool operator==(const String &a, const String &b) {
    if (a.size() != b.size())
        return false;

    for (int i = 0; i != a.size(); ++i) {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

bool operator!=(const String &a, const String &b) {
    return !(a == b);
}

char *begin(String &x) { // C-string-style access
    return x.c_str();
}

char *end(String &x) {
    return x.c_str() + x.size();
}

const char *begin(const String &x) {
    return x.c_str();
}

const char *end(const String &x) {
    return x.c_str() + x.size();
}

String &operator+=(String &a, const String &b) { // concatenation
    for (auto x: b)
        a += x;
    return a;
}

String operator+(const String &a, const String &b) { // concatenation
    String res{a};
    res += b;
    return res;
}

String operator "" _s(const char *p, size_t) {
    return String{p};
}

//===--------------------------------------------------------------===//

int main() {
    String s("abcdefghij");
    cout << s << endl;
    s += 'k';
    s += 'l';
    s += 'm';
    s += 'n';
    cout << s << endl;

    String s2 = "Hell";
    s2 += " and high water";
    cout << s2 << endl;

    String s3 = "qwerty";
    s3 = s3;
    String s4 = "the quick brown fox jumped over the lazy dog";
    s4 = s4;
    cout << s3 << " " << s4 << endl;
    cout << s + ". " + s3 + String(". ") + "Horsefeathers\n";

    String buf;
    while (cin >> buf && buf != "quit")
        cout << buf << " " << buf.size() << " " << buf.capacity() << endl;

    return 0;
}
