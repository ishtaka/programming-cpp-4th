#include <iostream>
#include <string>
#include <vector>

//===--------------------------------------------------------------===//
// 16.3 concrete class
//===--------------------------------------------------------------===//
using namespace std;

namespace Chrono {

    enum class Month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    class Date {
    public:                 // public interface
        class Bad_date {    // exception class
        };

        explicit Date(int dd = {}, Month mm = {}, int yy = {});

        int day() const;

        Month month() const;

        int year() const;

        string string_rep() const;              // string

        void char_rep(char s[], int max) const; // C style string

        Date &add_year(int n);  // add n years
        Date &add_month(int n); // add n months
        Date &add_day(int n);   // add n days
    private:
        bool is_valid();        // check if it is a valid date

        int d;                  // internal data representation
        Month m;
        int y;
    };

    bool is_date(int d, Month m, int y); // return true if it is a valid date
    bool is_leapyear(int y);             // return true if it is a leap year

    bool operator==(Date a, Date b);

    bool operator!=(Date a, Date b);

    const Date &default_date();

    ostream &operator<<(ostream &os, const Date &d); // output d to os

    istream &operator>>(istream &is, Date &d);       // input date to d from is
}

using namespace Chrono;

void f1(Date &d) {
    Date lvb_day{16, Month::dec, d.year()};

    if (d.day() == 29 && d.month() == Month::feb) {
        // ...
    }

    // cout << "day after:" << d + 1 << endl;

    Date dd; // initialize by default date
    cin >> dd;
    if (dd == d)
        cout << "Hurray!" << std::endl;
}

//===--------------------------------------------------------------===//
// 16.3.1 member function
//===--------------------------------------------------------------===//

Date::Date(int dd, Month mm, int yy)
        : d{dd}, m{mm}, y{yy} {
    if (y == 0) y = default_date().year();
    if (m == Month{}) m = default_date().month();
    if (d == 0) d = default_date().day();

    if (!is_valid())
        throw Bad_date();
}

void fill(vector<Date> &aa) {
    while (cin) {
        Date d;
        try {
            cin >> d;
        } catch (Date::Bad_date) {
            // .. error handling
            continue;
        }
        aa.push_back(d);
    }
}

bool Date::is_valid() {
    return is_date(d, m, y);
}

inline int Date::day() const {
    return d;
}

Date &Date::add_month(int n) {
    if (n == 0)
        return *this;

    if (n > 0) {
        int delta_y = n / 12;                  // how many years is it
        int mm = static_cast<int>(m) + n % 12; // how many months forward
        if (12 < mm) {                         // december is expressed as 12
            ++delta_y;
            mm -= 12;
        }

        // ... processing when d day does not exist in mm month

        y += delta_y;
        m = static_cast<Month>(mm);
        return *this;
    }

    // ... processing when n is minus

    return *this;
}

//===--------------------------------------------------------------===//
// 16.3.2 helper function
//===--------------------------------------------------------------===//

bool Chrono::is_date(int d, Month m, int y) {
    int ndays;

    switch (m) {
        case Month::feb:
            ndays = 28 + is_leapyear(y);
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            ndays = 30;
            break;
        case Month::jan:
        case Month::mar:
        case Month::may:
        case Month::jul:
        case Month::aug:
        case Month::oct:
        case Month::dec:
            ndays = 31;
            break;
    }

    return 1 <= d && d <= ndays;
}

const Date &Chrono::default_date() {
    static Date d{1, Month::jan, 1970};
    return d;
}

//===--------------------------------------------------------------===//
// 16.3.3 operator overload
//===--------------------------------------------------------------===//

bool Chrono::operator==(Date a, Date b) { // equality
    return a.day() == b.day() && a.month() == b.month() && a.year() == b.year();
}

//===--------------------------------------------------------------===//

int main() {
    return 0;
}
