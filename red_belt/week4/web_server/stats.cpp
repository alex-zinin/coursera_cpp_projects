#include"stats.h"
#include<iostream>

using namespace std;

Stats::Stats(): MethodStats(), UriStats()
{
    MethodStats = {{"GET", 0}, {"PUT", 0}, {"POST", 0}, {"DELETE", 0}, {"UNKNOWN", 0}};
    UriStats = {{"/", 0}, {"/order", 0}, {"/product", 0}, {"/basket", 0}, {"/help", 0}, {"unknown", 0}};
}
void Stats::AddMethod(string_view method)
{
    auto it = MethodStats.find(method);
    if(it == MethodStats.end())
        MethodStats.at("UNKNOWN")++;
    else
        MethodStats.at(method)++;
}


void Stats::AddUri(string_view uri)
{
    auto it = UriStats.find(uri);
    if(it == UriStats.end())
        UriStats.at("unknown")++;
    else
        UriStats.at(uri)++;
}

const map<string_view, int>& Stats::GetMethodStats() const
{
    return MethodStats;
}

const map<string_view, int>& Stats::GetUriStats() const
{
    return UriStats;
}


HttpRequest ParseRequest(string_view line)
{
    HttpRequest http_request;
    size_t posb = 0;
    for(auto itr = line.begin(); itr < line.end(); itr++)
    {
        if(*itr != ' ')
            break;
        posb++;
    }
    auto it = line.find(' ', posb);
    auto it2 = line.find(' ', it + 1);
    if(it <= line.size())
        http_request.uri = line.substr(it + 1, it2-it - 1);
    else
        http_request.uri = line.substr(line.size()-2);
    if(posb < line.size())
        http_request.method = line.substr(posb, it-posb);
    else
        http_request.method = line.substr(line.size() - 2);
    if(it2 + 1 < line.size())
        http_request.protocol = line.substr(it2 + 1);
    else
        http_request.protocol = line.substr(line.size()-1);

    return http_request;
}