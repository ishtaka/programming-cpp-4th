#include <iostream>
#include <list>

using namespace std;

//===--------------------------------------------------------------===//
// 20.2 derived class
//===--------------------------------------------------------------===//

struct Employee {
    string first_name, family_name;
    char middle_initial;
    string hiring_date;
    short department;
    // ...
};

/*
struct Manager {
    Employee emp;
    list<Employee*> group;
    short level;
};
*/

struct Manager : public Employee {
    list<Employee *> group;
    short level;
    // ...
};

void f(Manager m1, Employee e1) {
    list<Employee *> elist{&m1, &e1};
    // ...
}

void g(Manager mm, Employee ee) {
    Employee *pe = &mm;   // OK: every Manager is an Employee
    // Manager *pm = &ee; // Error: not every Employee is a Manger

    // pm->level = 2; // disaster: ee doesn't have a level

    auto pm = static_cast<Manager *>(pe);  // brute force: works because pe points to the Manager mm
    pm->level = 2;                         // fine: pm points to the Manager mm that has a level
}

void execute() {
    Manager m{};
    Employee e{};
    f(m, e);
    g(m, e);
}

class Employee1;                         // declaration only, no definition
// class Manager1 : public Employee1 {}; // Error: Employee1 not defined

//===--------------------------------------------------------------===//
// 20.2 member functions
//===--------------------------------------------------------------===//

class Employee2 {
public:
    void print() const {
        cout << full_name() << endl;
    }

    string full_name() const {
        return first_name + ' ' + middle_initial + ' ' + family_name;
    }
    // ...
private:
    string first_name, family_name;
    char middle_initial;
    // ...
};

class Manager2 : public Employee2 {
public:
    void print() const;

private:
    short level;
};

void Manager2::print() const {
    cout << "name is" << full_name() << endl;    // OK
    // cout << "name is" << family_name << endl; // Error!

    Employee2::print();
    cout << level;

    print(); // oops! print Manager2-specific information
}

//===--------------------------------------------------------------===//

int main() {
    execute();
    return 0;
}

