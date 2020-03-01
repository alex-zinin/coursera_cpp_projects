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

string gen_random(const int len) {

    string s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "/ .';!@#$%^&*()_+<>?][{}|\|~`"
            " ";

    for (int i = 0; i < len; ++i) {
        s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }

    s[len] = 0;

    return s;
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

bool IsPalindroma(const string& str) {

    int size = str.size();
    //cout << size << " " << str[0] << endl;
    bool flag = true;
    if(size == 0 || size == 1)
    {
        return flag;
    }

    for(int  i = 0; i < (size+1)/2; i++)
    {
        if(str[i] != str[size-i-1])
        {
          return false;
        }

    }
  return flag;
}


bool IsPalindromq(const string& str) {

    int size = str.size();
    //cout << size << " " << str[0] << endl;
    bool flag = true;
    if(size == 0 || size == 1)
    {
        return flag;
    }

    for(int  i = 0; i < (size+1)/2; i++)
    {
        if(str[i] != str[size-i-1])
        {
            return false;
        }

    }
    return flag;
}

void AllTests()
{
    AssertEqual(IsPalindrom("asdsa"), true, "Error1");
    AssertEqual(IsPalindrom("as d sa"), true, "Error2");
    AssertEqual(IsPalindrom("Mad daM"), true, "Error3");
    AssertEqual(IsPalindrom("asds"), false, "Error4");
    AssertEqual(IsPalindrom(" "), true, "Error5");
    AssertEqual(IsPalindrom("a"), true, "Error6");
    AssertEqual(IsPalindrom("asdsaa"), false, "Error7");
    AssertEqual(IsPalindrom(""), true, "Error8");
    AssertEqual(IsPalindrom("////"), true, "Error9");
    AssertEqual(IsPalindrom("as ;l;a'lx;alx"), false, "Error10");
    AssertEqual(IsPalindrom("as;aa;sa"), true, "Error11");
    AssertEqual(IsPalindrom("as ;aa;sa"), false, "Error12");
    AssertEqual(IsPalindrom("as;aa;saq"), false, "Error13");
    AssertEqual(IsPalindrom("qas;aa;sa"), false, "Error14");
    AssertEqual(IsPalindrom("  as;aa;sa"), false, "Error15");
    AssertEqual(IsPalindrom("as;aa;sa "), false, "Error16");
    AssertEqual(IsPalindrom("as;aa;sa;"), false, "Error17");
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), true, "Error");
    AssertEqual(IsPalindrom("wa           sit       '''    acaro   ''''''  ra'cati;saw"), false, "Error");
    AssertEqual(IsPalindrom(" 1/wa;  sitacaroracatis  ;aw/1 "), true, "Error");
    AssertEqual(IsPalindrom("asdfghjklqweelkjhgfdsa"), false, "Error");
    AssertEqual(IsPalindrom("asdfghjkiokjhgfdsa"), false, "Error");
    AssertEqual(IsPalindrom("asdfsa"), false, "Error");
    AssertEqual(IsPalindrom("aa"), true, "Error");
    AssertEqual(IsPalindrom("aaa"), true, "Error");
    AssertEqual(IsPalindrom("a"), true, "Error");
    AssertEqual(IsPalindrom("asdfghjklakjhgfdsa"), false, "Error");
    AssertEqual(IsPalindrom("asdfsa1"), false, "Error");
    AssertEqual(IsPalindrom("1asdfsa"), false, "Error");
    AssertEqual(IsPalindrom("=asdfsa-"), false, "Error");
    AssertEqual(IsPalindrom("asdfs%a"), false, "Error");
    AssertEqual(IsPalindrom("asdfsa}"), false, "Error");
    AssertEqual(IsPalindrom("a?sdfsa"), false, "Error");


    for(int j = 0; j < 50; j++)
    {
        for(int i = 0; i < 15; i++)
        {
            string stri;
            stri = gen_random(i);
            
            AssertEqual(IsPalindrom(stri), IsPalindroma(stri), "Error");
        }
    }





}

int main() {
  TestRunner runner;
  //string str = {"as d sa"};
  //cin >> str;
//  if(IsPalindrom(str) == true)
//    cout << "Palindrom";
//  else
//    cout << "no";
  runner.RunTest(AllTests,"Tests");
  return 0;
}
