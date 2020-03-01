#include <iostream>
#include<vector>

using namespace std;
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
    vector<pair<char, int>> v;
    for(int  i = 0; i < n; i++)
    {
        cin >> c >> a;
        v.push_back(make_pair(c,a));
    }
    for(int i = 0; i < n-1; i++)
    {
        cout << "(";
    }
    cout << "(" << k << ") ";
    for(int i = 0; i < n; i++)
    {
        if(i != n-1)
            cout << (v[i]).first << " " << (v[i]).second << ") ";
        else
            cout << (v[i]).first << " " << (v[i]).second << endl;
    }
    return 0;
}
