#pragma once
#include<iostream>
#include<vector>
#include<map>

using namespace std;

struct BusesForStopResponse {
    bool flag = false;
    string name = "foooo";
    vector<string> buses;
};
struct StopsForBusResponse {
    bool flag = true;
    string name;
    vector<string> names;
    map<string,vector<string>> stop;
};


struct AllBusesResponse {
    bool flag = true;
    vector<string> busnam;
    map<string, vector<string>> stops;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);
struct StopsForBusResponse;
ostream& operator << (ostream& os, const StopsForBusResponse& r);
struct AllBusesResponse;
ostream& operator << (ostream& os, const AllBusesResponse& r);