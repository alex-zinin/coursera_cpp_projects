#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include<string_view>
#include<deque>
#include"profile.h"
#include<unordered_map>

using namespace std;

class InvertedIndex {
public:

    struct Index_Data{
        size_t doc_id;
        size_t hitcount;
    };

    void Add(string document);
    const vector<Index_Data>& Lookup(string_view word) const;

    const string& GetDocument(size_t id) const {
        return docs[id];
    }

    int Get_Size() const {
        return docs.size();
    }



private:
    vector<Index_Data> empty_list;
    unordered_map<string_view, vector<Index_Data>> index;
    deque<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
};