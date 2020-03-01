#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;





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
    Rational rac;

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

class Rational {
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

  Rational(): numerator(0), denominator(1)
  {}

  Rational(int numerat, int denomin) {
    int q = 0;
      for(int i = numerator; i > 0; i--)
    {
        if(numerator % i == 0 && denominator % i == 0)
        {
            q = i;
            break;
        }
    }
      numerator = numerat/q;
      denominator = denomin/q;
      if((numerator > 0 && denominator < 0) || (numerator < 0 && denominator < 0))
      {
          numenator = -numenator;
          denominator = -denominator;
      }
  }

  int Numerator() const {
  }

  int Denominator() const {
  }
  int numerator;
  int denominator;
};

Rational crrat(int p, int q)
{
    Rational rat(p,q);
    return(rat);
}

void All_tests()
{
    AssertEqual(crrat(-10,-1), crrat(10,1), "Minus!");
    AssertEqual(crrat(10,5), crrat(2,1), "No reduction!");
    AssertEqual(crrat(), crrat(0,1), "No default!");
    AssertEqual(crrat(0,10), crrat(0,1), "No one!");



}


int main() {
  TestRunner runner;
  runner.RunTest( AssertEqual(), "First");
  // добавьте сюда свои тесты
  return 0;
}
