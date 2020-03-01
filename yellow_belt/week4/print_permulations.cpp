#include <iostream>
#include<algorithm>
#include<vector>
#include<math.h>

using namespace std;

template<typename T>
ostream& operator<<(ostream& stream, const vector<T>& vectr)
{

    for(const auto& i: vectr)
    {
        if(i != *(end(vectr)-1))
            stream << i << " ";
        else
            stream << i;
    }
    cout << endl;
    return stream;
}



bool operator==(const vector<int>& lhs, const vector<int>& rhs)
{
    bool flag = true;
    //cout << "jwskdj";
    for(int i = 0; i < lhs.size(); i++)
    {
        if(lhs[i] != rhs[i])
            flag = false;
    }
    return flag;
}


bool comp(const vector<int>& lhs, const vector<int>& rhs)
{
    bool flag;
    int vect1 = 0, vect2 = 0;
    //cout << "jwskdj";
    for(int i = lhs.size()-1; i >= 0; i--)
    {
        vect1 = vect1 + lhs[i]*pow(10,lhs.size()-1-i);
    }
    for(int i = rhs.size()-1; i >= 0; i--)
    {
        vect2 = vect2 + rhs[i]*pow(10,rhs.size()-1-i);
    }

    if(vect1 < vect2)
        flag = false;
    else
        flag = true;
    return flag;
}

size_t fact(int n)
{
    int s = 1;
    for(int i = n; i > 0; i--)
        s = s*i;
    return s;
}


int main() {
    int n = 0;
    cin >> n;
    vector<int> vect;

    if(vect > vect)
        cout << "kkl";
    for(int i = 1; i <= n; i++)
        vect.push_back(i);

    int stat = 1;
    int j = 0;
    vector<int> v[fact(n)];
    for(int i = 0; i < fact(n); )
    {
        random_shuffle(begin(vect),end(vect));
        //cout << vect;
        for(j = 0; j < i; j++)
        {
            if (vect == v[j]) {
                stat = 0;
                break;
            }
        }
        if(stat == 0)
        {
            stat = 1;
        }
        else
        {
            v[i] = vect;
            i++;
        }

    }
    vector<vector<int>> vc;
    for(int i = 0; i < fact(n); i++)
    {
        //cout << v[i] << endl;
        vc.push_back(v[i]);
    }
    sort(begin(vc), end(vc), comp);
    for(int i = 0; i < fact(n); i++)
    {
        cout << vc[i];
    }

    return 0;
}
