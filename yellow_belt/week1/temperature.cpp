#include <iostream>

using namespace std;

int main() {
    int64_t n = 0, i = 0;
    int64_t a[1000000], sr = 0, number = 0;
    cin >> n;
    for ( i = 0; i < n; i++)
    {
        cin >> a[i];
        sr = sr + a[i];
        //cout << i << " ";
    }
    sr = sr/(n);
    for(i = 0; i < n; i++)
    {
        if(a[i] > sr)
        {//cout << a[i] << endl;
            number = number+ 1;
        }
    }
    //cout<< n<< endl;
    cout << number << endl;
    for(i = 0; i < n; i++)
    {
        if(a[i] > sr)
        {
            cout << i << " ";
        }
    }

    return 0;
}
