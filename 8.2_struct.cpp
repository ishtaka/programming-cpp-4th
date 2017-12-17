#include <iostream>
#include <vector>

//===--------------------------------------------------------------===//
// 8.2 struct
//===--------------------------------------------------------------===//

struct Address {
    const char *name;   // "Jim Dandy"
    int number;         // 61
    const char *street; // "South St"
    const char *town;   // "New Providence"
    char state[2];      // 'N' 'J'
    const char *zip;    // "07974"
};

void f() {
    Address jd{};
    jd.name = "Jim Dandy";
    jd.number = 61;
}

void print_addr(const Address *p) {
    std::cout << p->name << '\n'
              << p->number << ' ' << p->street << '\n'
              << p->town << '\n'
              << p->state[0] << p->state[1] << ' ' << p->zip << std::endl;
}

void print_addr2(const Address &r) {
    std::cout << r.name << '\n'
              << r.number << ' ' << r.street << '\n'
              << r.town << '\n'
              << r.state[0] << r.state[1] << ' ' << r.zip << std::endl;
}

Address current;

Address set_current(Address next) {
    Address prev = current;
    current = next;

    return prev;
}

void execute() {
    std::cout << "-----8.2 struct-----" << std::endl;

    f();
    Address jd = {
            "Jim Dandy",
            61,
            "South St",
            "New Providence",
            {'N', 'J'},
            "07974"
    };

    print_addr(&jd);
    print_addr2(jd);

    set_current(jd);
}

//===--------------------------------------------------------------===//
// 8.2.1 struct's layout
//===--------------------------------------------------------------===//

struct Readout {
    char hour; // [0:23]
    int value;
    char seq;  // ['a':'z']

    /*
     hour  -***
     value ----
     seq   -***
    */
};

struct Readout2 {
    int value;
    char hour; // [0:23]
    char seq;  // ['a':'z']

    /*
     value      ----
     (hour,seq) --**
    */
};

void execute1() {
    std::cout << "-----8.2.1 struct's layout-----" << std::endl;

    Readout r{};   // sizeof(r) == 12
    Readout2 r2{}; // sizeof(r2) == 8
    std::cout << sizeof(r) << std::endl;
    std::cout << sizeof(r2) << std::endl;

    Readout ra[10];   // sizeof(ra) == 10 * sizeof(r) = 120
    Readout2 ra2[10]; // sizeof(ra2) == 10 * sizeof(r2) = 80
    std::cout << sizeof(ra) << std::endl;
    std::cout << sizeof(ra2) << std::endl;
}

//===--------------------------------------------------------------===//
// 8.2.2 struct's name
//===--------------------------------------------------------------===//

struct List; // struct name declaration , definition will be done late

struct Link {
    Link *previours;
    Link *successor;
    List *member_of;
    int data;
};

struct No_good {
    // No_good member; // Error: redefined
};

struct List {
    Link *head;
};

//===--------------------------------------------------------------===//
// 8.2.3 struct and class
//===--------------------------------------------------------------===//

struct Point {
    int x, y;
};

struct Points {
    std::vector<Point> elem;

    Points(Point p0) {
        elem.push_back(p0);
    }

    Points(Point p0, Point p1) {
        elem.push_back(p0);
        elem.push_back(p1);
    }
};

void execute3() {
    // Points x0; // Error: No default constructor
    Points x1{Point{100, 200}};
    Points x2{Point{100, 200}, Point{300, 400}};

    Point p1{};     // default {{}, {}} is {0,0}
    Point p2{1};    // {1, {}} is {1, 0}
    Point p3{1, 2}; // {1, 2}
}

//===--------------------------------------------------------------===//
// 8.2.4 struct and array
//===--------------------------------------------------------------===//

struct Array {
    Point elem[3];
};

Array shift(Array a, Point p) {
    for (int i = 0; i != 3; ++i) {
        a.elem[i].x += p.x;
        a.elem[i].y += p.y;
    }

    return a;
}

void execute4() {
    std::cout << "-----8.2.4 struct and array-----" << std::endl;

    Point points[3]{{1, 2},
                    {3, 4},
                    {5, 6}};
    int x2 = points[2].x;
    std::cout << x2 << std::endl; // 5

    Array points2{Point{1, 2},
                  Point{3, 4},
                  Point{5, 6}};
    int y2 = points2.elem[2].y;
    std::cout << y2 << std::endl; // 6

    Array ax = shift(points2, {10, 20});
    std::cout << ax.elem[1].x << std::endl; // 13
    std::cout << ax.elem[1].y << std::endl; // 24
}

//===--------------------------------------------------------------===//
// 8.2.5 type equality
//===--------------------------------------------------------------===//

struct S5_1 {
    int a;
};

struct S5_2 {
    int a;
};

void execute5() {
    S5_1 x;
    // S5_2 y = x; // Error: type not match
    // int i = x;  // Error: type not match
}

//===--------------------------------------------------------------===//
// 8.2.6 POD
//===--------------------------------------------------------------===//

// POD
struct S0 {
};

// POD
struct S1 {
    int a;
};

// not POD(no default constructor)
struct S2 {
    int a;

    S2(int aa) : a(aa) {}
};

// not POD(default constructor by user defined)
struct S3 {
    int a;

    S3(int aa) : a(aa) {}

    S3() {}
};

// POD
struct S4 {
    int a;

    S4(int aa) : a(aa) {}

    S4() = default;
};

// not POD(has virtual function)
struct S5 {
    virtual void f();
};

// POD
struct S6 : S1 {
};

// POD
struct S7 : S0 {
    int b;
};

// not POD(contain data both S1 and S8)
struct S8 : S1 {
    int b;
};

// POD
struct S9 : S0, S1 {

};

//===--------------------------------------------------------------===//
// 8.2.7 bit-field
//===--------------------------------------------------------------===//

struct PPN {
    unsigned int PFN : 22;
    int : 3;               // unused;
    unsigned int CCA :3;
    bool nonreachable : 1;
    bool dirty : 1;
    bool valid : 1;
    bool global : 1;
};

void part_of_VM_system(PPN *p) {
    if (p->dirty) {
        p->dirty = 0;
    }
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    execute1();
    execute3();
    execute4();
    execute5();
    return 0;
}
