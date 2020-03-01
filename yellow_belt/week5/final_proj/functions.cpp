#include<iostream>
#include<vector>
#include"functions.h"

using namespace std;

template<class T>
void VisitPlaces( T& t, const vector<string> &places)
{
    for (auto& p : places)
    {
        t.Walk(p);
    }
}

