#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//class Rational {
//public:
//    // Вы можете вставлять сюда различные реализации,
//    // чтобы проверить, что ваши тесты пропускают корректный код
//    // и ловят некорректный
//
//    Rational(): numerator(0), denominator(1)
//    {}
//
//    Rational(int numerat, int denomin) {
//        int q = 1;
//        int num = abs(numerat), den = abs(denomin);
//        for(int i = num; i > 0; i--)
//        {
//            if(num % i == 0 && den % i == 0)
//            {
//               // cout << "break" << numerator % i << denominator % i<< numerator<< "  " << denominator<<  endl;
//                q = i;
//                break;
//            }
//        }//cout << "="<< numerat << " "<< denomin << " " <<q << " " << numerator << " "<< denominator<<"sksksks";
//        if(numerat < 0)
//            numerator = -num/q;
//        else
//            numerator = num/q;
//        if(denomin < 0)
//            denominator = -den/q;
//        else
//            denominator = den/q;
//        if((numerator > 0 && denominator < 0) || (numerator < 0 && denominator < 0))
//        {
//            numerator = -numerator;
//            denominator = -denominator;
//        }
//        if(numerat == 0)
//            denominator = 1;
//    }
//
//    int Numerator() const {
//        return numerator;
//    }
//
//    int Denominator() const {
//        return denominator;
//    }
//    int numerator;
//    int denominator;
//};

bool operator!=(const Rational &lhs, const Rational &rhs)
{
    if(lhs.Numerator() != rhs.Numerator() || lhs.Denominator() != rhs.Denominator())
        return true;
    else
        return false;
}

ostream& operator<<(ostream& stream, const Rational &rat)
{
    stream << rat.Numerator() << "," << rat.Denominator();
    return stream;
}


template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {


    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

Rational crrat()
{
    Rational rat;//cout << "["<< p<< " " << q << "qq"<< rat.Numerator() << " " << rat.Denominator() << endl;
    return(rat);
}

Rational crrat(int p, int q)
{
    Rational rat(p,q);//cout << "["<< p<< " " << q << "qq"<< rat.Numerator() << " " << rat.Denominator() << endl;
    return(rat);
}

void All_tests()
{
    AssertEqual(crrat(-10,-1), crrat(10,1), "Minus!");
    AssertEqual(crrat(10,5), crrat(2,1), "No reduction!");
    AssertEqual(crrat(0,1), crrat(0,1), "No default!");
    AssertEqual(crrat(0,10), crrat(0,1), "No one!");
    AssertEqual(crrat(-10,-5),crrat(2,1), "Error");
    AssertEqual(crrat(0,-5),crrat(0,1), "Error2");
    AssertEqual(crrat(-10,5),crrat(-2,1), "Error3");
    AssertEqual(crrat(), crrat(0,1), "Error4");
}


int main() {
    TestRunner runner;
    //All_tests();
    runner.RunTest(All_tests, "AllTests");
    // добавьте сюда свои тесты
    return 0;
}
