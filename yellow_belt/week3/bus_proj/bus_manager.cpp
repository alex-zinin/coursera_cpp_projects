#include "bus_manager.h"
#include<algorithm>
#include "responses.h"
#include<iostream>

void  BusManager::AddBus(const string& bus, const map<string,vector<string>>& stops) {
        //buses_to_stops[bus]
        // cout << bus << " " << stops << endl;
        busnames.push_back(bus);
        for(int i = 0; i < (stops.at(bus)).size(); i++)
        {
            (buses_to_stops[bus]).push_back((stops.at(bus))[i]);
        }
        //cout << buses_to_stops[bus];
        for(int i = 0; i < (stops.at(bus)).size(); i++)
        {
            (stops_to_buses[(stops.at(bus))[i]]).push_back(bus);
        }
        sort(busnames.begin(),busnames.end());

    }

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const { // маршруты проходящие через данную останв
        BusesForStopResponse buss;//cout << "func-GetBusesforStop"<< stop <<endl;
        //cout << stops_to_buses.count(stop) <<endl;cout << "sew";

        if(stops_to_buses.count(stop) != 0) {
            buss.flag = true;
            buss.name = stop;
            for (int i = 0;
                 i < ((stops_to_buses.at(stop))).size(); i++)//NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
            {          // cout<< "norm" <<"lol";                                           //NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
                buss.buses.push_back(
                        (stops_to_buses.at(stop))[i]);//(stops_to_buses.at(stop))[i];//BUSES_FOR_STOP Vnukovo
            }
        } else
            buss.flag = false;
        return buss;
    }

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {//  вывести названия всех остановок маршрута bus
        // со списком автобусов, на которые можно пересесть на каждой из остановок.
        StopsForBusResponse stops;
        //cerr << "aaaaa";


        if(buses_to_stops.count(bus) == 0)
        {  //cerr<< "put_down";
            stops.flag = false;
            return stops;
        }
        stops.name = bus;
        for(int i = 0; i < buses_to_stops.at(bus).size(); i++)
        {
            //auto b = GetBusesForStop(bus);
            (stops.names).push_back((buses_to_stops.at(bus))[i]);//
            //auto fgh = BusManager::GetBusesForStop(bus);
            vector<string> busss = GetBusesForStop((buses_to_stops.at(bus))[i]).buses;
            vector<string> namebus = (buses_to_stops.at(bus));//вектор ост. для данного автобуса.
            string namest = namebus[i];//имя i остановки
            (stops.stop)[namest] = busss;
        }                                                    //маршруты через данную ост.
        return stops;
    }

AllBusesResponse BusManager::GetAllBuses() const {//вывести список всех маршрутов с остановками.
        AllBusesResponse obj;
        if(busnames.size() == 0)
            obj.flag = false;
        for(int i = 0; i < busnames.size(); i++)
        {
            obj.busnam.push_back(busnames[i]);
            vector<string> stopps = buses_to_stops.at(busnames[i]);
            string bsnm = busnames[i];
            (obj.stops)[bsnm] = stopps;
        }
        return obj;
    }
