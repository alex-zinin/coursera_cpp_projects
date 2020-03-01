#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include<algorithm>

using namespace std;


//ostream& operator<<(ostream& stream, vector<string> v)
//{
//    for(int i = 0; i < v.size(); i++)
//    {
//        stream << v[i] << " ";
//    }
//    return stream;
//}
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
    map<string, vector<string>> stops;
};

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

    //cout << (int)(typeq)<<endl;
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
            q.type = QueryType::BusesForStop;//cout << "eeee";
            is >> q.stop; //cout << q.stop;
            break;}
       case QueryType::StopsForBus: {
            q.type = QueryType::StopsForBus;//cout << "stopbus";
            is >> q.bus;
            break;}
        case QueryType::AllBuses: { //cout << "allbus";
           q.type = QueryType::AllBuses;
           break;}
    }
//cerr<< "HEY";cout <<"ZEW"<< (int)typeq <<endl;
    return is;
}

struct BusesForStopResponse {
    bool flag = false;
    string name = "foooo";
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
   // cerr << "aaaaaaaaaaaaa";
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

struct StopsForBusResponse {
    bool flag = true;
    string name;
    vector<string> names;
    map<string,vector<string>> stop;
};

//ostream& operator << (ostream& os, const StopsForBusResponse& r) {
//
//
//    if(r.flag == false)
//        os << "No bus";
//    else {
//        for (int i = 0; i < r.names.size(); i++) {
//            string str = r.names[i];
//            if (r.stop.at(str).size() == 1) {
//                os << "Stop " << r.names[i] << ":" << " no interchange";
//                if (i < r.names.size() - 1)
//                    os << endl;
//            }
//            else
//                {
//                for (int j = 0; j < r.stop.at(str).size(); j++) {
//
//                    if (j == 0)
//                        os << "Stop " << r.names[i] << ": ";
//
//                    if ((r.stop.at(str))[j] == r.name) {
//                        if(j == r.stop.at(str).size()-1 && i != r.names.size()-1 )
//                            os << endl;
//
//                    } else
//                    {
//                        os << (r.stop.at(str))[j] << " ";
//                    if(j == r.stop.at(str).size()-1 && i != r.names.size()-1 )
//                        os << endl;
//                    }
//                }
////
//
//            }
//
//        }
//    }
//    return os;
//}




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


struct AllBusesResponse {
    bool flag = true;
    vector<string> busnam;
    map<string, vector<string>> stops;
};

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

class BusManager {
public:

    BusManager(){}
    void AddBus(const string& bus, const map<string,vector<string>>& stops) {
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
        BusesForStopResponse GetBusesForStop(const string& stop) const { // маршруты проходящие через данную останв
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

        StopsForBusResponse GetStopsForBus(const string& bus) const {//  вывести названия всех остановок маршрута bus
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

        AllBusesResponse GetAllBuses() const {//вывести список всех маршрутов с остановками.
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
public:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
    vector<string> busnames;
    };

 //Не меняя тела функции main, реализуйте функции и классы выше

//    int main() {
//        int query_count;
//
//        Query a;
//        cin >> query_count;
//
//        //cout << "l";
//        BusManager bm;
//        for (int i = 0; i < query_count; i++) {
//            auto q = a;
//            //sort(bm.busnames.begin(),bm.busnames.end());
//            cin >> q;
//            //cout << "For" << (int)q[i].type << q[i].stop<< endl<<endl<<endl;
//           // cout << "vseok"<<endl;
//            int as = (int)q.type;
//            switch (as) {
//                case 0: {//cout <<"newbus";
//                    bm.AddBus(q.bus, q.stops);
//                    break;}
//                case 1:  { //cout << endl;//cout << "st";// cout << q[i].stop;
//                    cout << bm.GetBusesForStop(q.stop)<< endl;
//                    break;}
//                case 2: {
//                    cout << bm.GetStopsForBus(q.bus) << endl;
//                    break;}
//                case 3: {
//                    cout << bm.GetAllBuses() << endl;
//                    break;}
//            }
//        }
//       //sort(bm.busnames.begin(),bm.busnames.end());
//   // cout <<bm.busnames<<endl;
//        return 0;
//    }



int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) <<endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
