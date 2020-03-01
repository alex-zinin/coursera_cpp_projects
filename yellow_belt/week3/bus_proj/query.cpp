//
// Created by alexzinin on 05.04.19.
//
#include "query.h"

istream& operator >> (istream& is, Query& q) {// ввод запроса
    QueryType typeq;
    string typestr;
    is >> typestr;  //cout << typestr << "typest"<<endl;
    if(typestr == "NEW_BUS")
        typeq = QueryType::NewBus;
    if(typestr == "BUSES_FOR_STOP")
    {typeq = QueryType::BusesForStop;}// cout << "<<Busesforstop"<< endl;}
    if(typestr == "STOPS_FOR_BUS")
        typeq = QueryType::StopsForBus;
    if(typestr == "ALL_BUSES")
        typeq = QueryType::AllBuses;

    switch (typeq) {
        case QueryType::NewBus: {
            q.type = QueryType::NewBus;
            is >> q.bus;
            int count = 0;
            is >> count;
            string stop;
            for (int i = 0; i < count; i++) {
                cin >> stop;
                (q.stops[q.bus]).push_back(stop);
            }
            break;}
        case QueryType::BusesForStop: {
            q.type = QueryType::BusesForStop;
            is >> q.stop; //cout << q.stop;
            break;}
        case QueryType::StopsForBus: {
            q.type = QueryType::StopsForBus;
            is >> q.bus;
            break;}
        case QueryType::AllBuses: {
            q.type = QueryType::AllBuses;
            break;}
    }
    return is;
}