#include "responses.h"
#include "bus_manager.h"
#include<map>
#include<vector>
#include<iostream>

using namespace std;



ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.flag == false) {
        os << "No stop";
        return os;
    }
    else
    {
        //os  << "Stop " << r.name<<": ";
        for(int i = 0; i < r.buses.size(); i++)
            os << r.buses[i] << " ";
    }
    //os << endl;
    return os;
}




ostream& operator << (ostream& os, const StopsForBusResponse& r)
{
    if(r.flag == false)
    {
        os << "No bus";
        return os;
    }
    for (int i = 0; i < r.names.size(); i++)
    {
        string str = r.names[i];
        if (r.stop.at(str).size() == 1 )
        {
            os << "Stop " << r.names[i] << ":" << " no interchange";
            if (i < r.names.size() - 1)
                os << endl;
        }
        else
        {
            for (int j = 0; j < r.stop.at(str).size(); j++)
            {
                if (j == 0)
                    os << "Stop " << r.names[i] << ": ";
                if ((r.stop.at(str))[j] == r.name) {
                    if(j == r.stop.at(str).size()-1 && i != r.names.size()-1 )
                        os << endl;
                } else{
                    os << (r.stop.at(str))[j] << " ";
                    if(j == r.stop.at(str).size()-1 && i != r.names.size()-1 )
                        os << endl;
                }

            }
        }

    }
    return os;
}




ostream& operator << (ostream& os, const AllBusesResponse& r)
{

    if(r.flag == false)
        os << "No buses";
    for(int i = 0; i < r.busnam.size(); i++)
    {
        os << "Bus " << r.busnam[i] << ": ";


        for(int k = 0; k < (r.stops.at(r.busnam[i])).size(); k++)
        {
            os << (r.stops.at(r.busnam[i]))[k] << " ";
        }
        //os << r.stops.at(r.busnam[i])<< " ";
        if(i != r.busnam.size()-1)
            os << endl;
    }

    return os;
}