#include <iostream>
#include<vector>
#include<deque>
#include<string>

using namespace std;

int priority(char c)
{
    if(c == '+' || c == '-')
        return 1;
    if(c == '*' || c == '/')
        return 2;
}
int main() {
    int k,n = 0;
    cin >> k;
    cin >> n;
    if(n == 0)
    {
        cout << k;
        return 0;
    }
    char c;
    int a = 0;
    int pr = 0;
    string str;
    deque<string> d;
    if(k < 0)
    {

        d.push_back((to_string(k)));
    }
    else
    d.push_back((to_string(k)));
    for(int  i = 0; i < n; i++)
    {
        cin >> c >> a;
        if(i != 0 && priority(c) > pr)
        {
            d.push_front("(");
            d.push_back(")");
            d.push_back(" ");
            str.push_back(c);
            d.push_back(str);
            str.clear();
            d.push_back(" ");
            if(a < 0)
            {
                d.push_back((to_string(a)));
            }
            else
            d.push_back((to_string(a)));
            pr = priority(c);
        }
        else
        {
            pr = priority(c);
            d.push_back(" ");
            str.push_back(c);
            d.push_back(str);
            str.clear();
            d.push_back(" ");
            d.push_back((to_string(a)));
        }
    }

    for(int i = 0; i < d.size(); i++)
    {
        cout << d[i];
    }

    return 0;
}
