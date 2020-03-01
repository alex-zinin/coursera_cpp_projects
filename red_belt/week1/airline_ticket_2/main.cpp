#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

bool operator<(Date lhs, Date rhs)
{
    int date1 = lhs.year*10000+lhs.month*100+lhs.day;
    int date2 = rhs.year*10000+rhs.month*100+rhs.day;
    return date1 < date2;
}

bool operator<(Time lhs, Time rhs)
{
    return lhs.hours*100+lhs.minutes < rhs.hours*100+rhs.minutes;
}

bool operator==(Date lhs, Date rhs)
{
    int date1 = lhs.year*10000+lhs.month*100+lhs.day;
    int date2 = rhs.year*10000+rhs.month*100+rhs.day;
    return date1 == date2;
}

bool operator==(Time lhs, Time rhs)
{
    return lhs.hours*100+lhs.minutes == rhs.hours*100+rhs.minutes;
}

ostream& operator<<(ostream &os, Date d)
{
    os << d.year << "-" << d.month << "-" << d.day;
    return os;
}

ostream& operator<<(ostream &os, Time t)
{
    os << t.hours << ":" << t.minutes;
    return os;
}

istream& operator>>(istream &is, Date& d)
{
    char tr;
    is >> d.year >> tr;
    is >> d.month >> tr;
    is >> d.day;
    return is;
}

istream& operator>>(istream &is, Time& t)
{
    char tr;
    is >> t.hours;
    is >> tr >> t.minutes;
    return is;
}

#define UPDATE_FIELD(ticket, field, values) \
if (values.find(#field) != values.end()) {                   \
    istringstream is((values.find(#field))->second);           \
    is >> ticket.field;                     \
}                                           \

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
            {"price", "12550"},
            {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);

}