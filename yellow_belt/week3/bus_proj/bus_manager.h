#pragma once
#include<iostream>
#include<vector>
#include "responses.h"
#include<map>


using namespace std;

class BusManager {
public:
    void AddBus(const string& bus, const map<string,vector<string>>& stops);
    BusesForStopResponse GetBusesForStop(const string& stop) const;
    StopsForBusResponse GetStopsForBus(const string& bus) const;
    AllBusesResponse GetAllBuses() const;
    map<string, vector<string>> buses_to_stops, stops_to_buses;
    vector<string> busnames;
};
