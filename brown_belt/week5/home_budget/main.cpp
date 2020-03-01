#include <iostream>
#include <ctime>
#include"test_runner.h"
#include<stdio.h>
#include<unordered_map>
using namespace std;

struct Date
{
public:
    Date(): year_(0), month_(0), day_(0) {}
    Date(int year, int month, int day): year_(year), month_(month), day_(day) {}
    int  year_, month_, day_;
    time_t AsTimestamp() const;
};




bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.year_ == rhs.year_ && lhs.month_ == rhs.month_ && lhs.day_ == rhs.day_;
}

bool operator!=(const Date& lhs, const Date& rhs)
{
    return lhs.year_ != rhs.year_ || lhs.month_ != rhs.month_ || lhs.day_ != rhs.day_;
}

struct Date_Hasher
{
    size_t operator()(const Date& date) const
    {
        size_t year = ihash(date.year_);
        size_t  month = ihash(date.month_);
        size_t day = ihash(date.day_);
            return year*month*day;
    }

    hash<int> ihash;

};
ostream& operator<<(ostream& os, const Date& date)
{
    os << date.year_<< '-';
    if(date.month_ < 10)
        os << "0";
    os << date.month_ << '-';
    if(date.day_ < 10)
        os << "0";
    os << date.day_;

    return os;
}

Date Next_Date(const Date& date)
{
    int end_m;
    if(date.month_ == 2)
    {
        if(date.year_% 4 == 0)
            end_m = 29;
        else
            end_m = 28;
    }
    else
    {
        if(date.month_ == 1 || date.month_ == 3 || date.month_ == 5 || date.month_ == 7 || date.month_ == 8 || date.month_ == 10 || date.month_ == 12)
            end_m = 31;
        else
            end_m = 30;
    }
    if(date.month_ == 12 && date.day_ == end_m)
        return Date(date.year_+1, 1, 1);
    if(date.day_ == end_m)
        return Date(date.year_, date.month_ + 1, 1);
    return Date(date.year_, date.month_, date.day_ + 1);

}

time_t Date::AsTimestamp() const
{
    std::tm t;
    t.tm_sec   = 0;
    t.tm_min   = 0;
    t.tm_hour  = 0;
    t.tm_mday  = day_;
    t.tm_mon   = month_ - 1;
    t.tm_year  = year_ - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
}

int Compute_Index(const Date& date)
{
    int index = 0;
    int y = date.year_;
    int m = date.month_;
    int d = date.day_;
    if(date.year_ % 4 == 0)
    {
        if(y == 2000)
            index += 0;
        else
            index += ((y - 2000) - (((y-2000)-(y-2000)%4)/4) - 1)*365 + (((y-2000)-(y-2000)%4)/4 + 1) * 366;
        //cout << index << endl;
        if(m > 2)
            index += ((m-m%2)/2)*31 + 29 + (((m-1)-(m-1)%2)/2 -1)*30;
        else
            index += ((m-m%2)/2)*31;
        index += d - 1;
    }
    else
    {
        if(y == 2000)
            index += 0;
        else
            index += ((y - 2000) - (((y-2000)-(y-2000)%4)/4) - 1)*365 + (((y-2000)-(y-2000)%4)/4 + 1) * 366;
        if(m > 2)
            index += ((m-m%2)/2)*31 + 28 + (((m-1)-(m-1)%2)/2 -1)*30;
        else
            index += ((m-m%2)/2)*31;
        index += d - 1;
    }

    return index;
}


double ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

Date Read_Date(istream& is)
{
    Date date(0,0,0);
    char c;
    is >> date.year_ >> c >> date.month_ >> c >> date.day_;
    return date;
}


class Budget_Handler
{
public:

    Budget_Handler(): data(), sum(0), rsum(0), num_tax(0) {}

    long double ComputeIncome(const Date& from, const Date& to)
    {
        long double res = 0;
        for(auto dat = from; dat != Next_Date(to) ; dat = Next_Date(dat))
            res = res + data[dat];
        return res;
    }


    void Earn(const Date& from, const Date& to, double value)
    {
        int j = 0;
        long double val = (value)/(ComputeDaysDiff(to, from) +  1);
        for(auto dat = from; dat != Next_Date(to) ; dat = Next_Date(dat))
        {
            data[dat] = data[dat] + val;
            sum += val;
        }
    }

    void PayTax(const Date& from, const Date& to)
    {
        int j = 0;
        num_tax++;
        for(auto dat = from; dat != Next_Date(to) ; dat = Next_Date(dat))
        {
            rsum += data[dat] * 0.13;
            data[dat] = data[dat] * 0.87;
        }
    }

public:
    unordered_map<Date, double, Date_Hasher> data;
    long double sum;
    long double rsum;
    int num_tax;

};


void Test_Compute_Index()
{
    ASSERT_EQUAL(0, Compute_Index(Date(2000,1,1)));
    ASSERT_EQUAL(31, Compute_Index(Date(2000,2,1)));
    ASSERT_EQUAL(59, Compute_Index(Date(2000,2,29)));
    ASSERT_EQUAL(60, Compute_Index(Date(2000,3,1)));
    ASSERT_EQUAL(365, Compute_Index(Date(2000,12,31)));
    ASSERT_EQUAL(366, Compute_Index(Date(2001,1,1)));
    ASSERT_EQUAL(367, Compute_Index(Date(2001,1,2)));
    ASSERT_EQUAL(397, Compute_Index(Date(2001,2,1)));
    ASSERT_EQUAL(425, Compute_Index(Date(2001,3,1)));
    ASSERT_EQUAL(456, Compute_Index(Date(2001,4,1)));
    ASSERT_EQUAL(486, Compute_Index(Date(2001,5,1)));
    ASSERT_EQUAL(517, Compute_Index(Date(2001,6,1)));
    ASSERT_EQUAL(730, Compute_Index(Date(2001,12,31)));
    ASSERT_EQUAL(731, Compute_Index(Date(2002,1,1)));
    ASSERT_EQUAL(733, Compute_Index(Date(2002,1,3)));



    {
        Budget_Handler bd;
        bd.Earn(Date(2000,1,1), Date(2021, 1,1), 367);
        bd.Earn(Date(2000,1,1), Date(2000,1,1), 3580);
        bd.PayTax(Date(2000,1,1), Date(2000,1,1));
        bd.PayTax(Date(2000,1,1), Date(2000,1,1));
        bd.PayTax(Date(2000,1,1), Date(2000,1,1));
        bd.PayTax(Date(2000,1,1), Date(2000,1,1));
        ASSERT_EQUAL( (int) bd.ComputeIncome(Date(2000,1,1), Date(2000,1,1)), (int) 2051.0085);
    }


}





int main() {
    TestRunner tr;
    RUN_TEST(tr, Test_Compute_Index);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(25);
    cerr.precision(25);
    Budget_Handler bd;


    int query_count;
    cin >> query_count;
    int sum = 0;
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        Date from = Read_Date(cin);
        Date to = Read_Date(cin);
        if(query_type == "ComputeIncome")
        {
            cout << bd.ComputeIncome(from, to) << endl;
        }else
            if(query_type == "Earn")
            {
                double value;
                cin >> value;
                sum += value;
                bd.Earn(from, to, value);
            }else
                if(query_type == "PayTax")
                {
                    bd.PayTax(from, to);
                }
    }

    return 0;
}