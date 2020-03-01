#pragma once
#include<iostream>
#include<vector>
#include<map>

using namespace std;

enum class QueryType { // тип запроса
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query { // запрос
    QueryType type;
    string bus;
    string stop;
    map <string, vector<string>> stops;
};

istream& operator >> (istream& is, Query& q);