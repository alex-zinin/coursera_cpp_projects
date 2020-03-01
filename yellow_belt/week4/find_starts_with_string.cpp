#include <iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>

using namespace std;

struct st
{
    string pr;
};
//bool cm(const string& lhs, const string& rhs )
//{
//    string str;
//
//    return (lhs < rhs);
//}
bool cmp(const string& lhs, const string& rhs );



bool operator<(const string& lhs, const st& rhs)
{
    //cout << "aaaaaa";
    string str;
    //cout << lhs << " " << rhs.pr << endl;
    if(lhs.size() >= rhs.pr.size())
    {
        str = lhs;
        // cerr << str<<endl;
        str.erase(lhs.size(),lhs.size()-rhs.pr.size());
//        if(str.compare(rhs) == 0)
//        {//cout << "////// "<< lhs <<  " "<<rhs << endl;
//            return 0;}
        //cout << str << " " << rhs.pr << endl;
        if(str.compare(rhs.pr) > 0)
            return false;
        if(str.compare(rhs.pr) < 0)
            return true;
    }
    else
    {
//        if(lhs == "murmansk")
//            cout << "@" << lhs << rhs;

        if(lhs.compare(rhs.pr) > 0)
            return false;
        else
            return true;
    }
}



bool operator<(const st& lhs,const string& rhs)
{
    //cout << "aaaaaa";
    string str;
    //cout << lhs << " " << rhs.pr << endl;
    if(lhs.pr.size() >= rhs.size())
    {
        str = rhs;
        // cerr << str<<endl;
        str.erase(rhs.size(),lhs.pr.size()-rhs.size());
//        if(str.compare(rhs) == 0)
//        {//cout << "////// "<< lhs <<  " "<<rhs << endl;
//            return 0;}
       // cout << str << " " << rhs.pr << endl;
        if(str.compare(lhs.pr) > 0)
            return true;
        if(str.compare(lhs.pr) < 0)
            return false;
    }
    else
    {
//        if(lhs == "murmansk")
//            cout << "@" << lhs << rhs;

        if(rhs.compare(lhs.pr) > 0)
            return true;
        else
            return false;
    }
}

bool cmp(const string& lhs, const string& rhs)
{
    string str;
    //cout << lhs << " " << rhs << endl;
    if(lhs.size() >= rhs.size())
    {
        str = lhs;
       // cerr << str<<endl;
        str.erase(rhs.size(),lhs.size()-rhs.size());
//        if(str.compare(rhs) == 0)
//        {//cout << "////// "<< lhs <<  " "<<rhs << endl;
//            return 0;}
        cout << str << " " << rhs << endl;
        if(str.compare(rhs) > 0)
            return false;
        if(str.compare(rhs) < 0)
            return true;
    }
    else
    {
//        if(lhs == "murmansk")
//            cout << "@" << lhs << rhs;

        if(lhs.compare(rhs) > 0)
            return false;
        else
            return true;
    }
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix)
{
    st stre;
    stre.pr = prefix;
    return (equal_range(range_begin, range_end, prefix,   [&prefix](string str1, string str2)
    {
        if(str1.compare(0,prefix.size(),str2.substr(0,prefix.size())) < 0)
            return true;
        else
            return false;

    } ));
}

void func(vector<string> sorted_strings, string S, int T, int U)
{
    const auto mt_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), S);
    if((mt_result.first - begin(sorted_strings)) != T  || (mt_result.second - begin(sorted_strings)) != U )
    {
        int a = (mt_result.first - begin(sorted_strings)), b = (mt_result.second - begin(sorted_strings));
        cerr << "test failed " << S << " " << T << " " << U << " " << a << " " << b << endl;
    }

}

void Alltest(vector<string> sorted_strings)
{
    func(sorted_strings, "mo", 0, 2);
    func(sorted_strings, "mos", 0, 1);
    func(sorted_strings, "mur", 2, 3);
    func(sorted_strings, "moscowasedr", 1, 1);
    func(sorted_strings, " ", 0, 0);
    func(sorted_strings, "", 0, 0);
    func(sorted_strings, "wur", 3, 3);
    func(sorted_strings, "motovilikhas", 2, 2);
}
