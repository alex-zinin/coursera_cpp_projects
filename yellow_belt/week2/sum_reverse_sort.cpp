#include<algorithm>
#include <string>
#include <vector>
#include<iostream>
#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y)
{
    return(x+y);
}

string Reverse(string s)
{
    string str;
//    for(int i = 0; i < s.size(); i++)
//    {
//        str[i] = s[s.size()-1-i];
//        //cout << str[3] << i;
//    }
    str = s;
    reverse(begin(str), end(str));
    return str;
}
void Sort(vector<int>& nums)
{
    sort(nums.begin(), nums.end());
}

