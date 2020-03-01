#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include<mutex>
#include <string>
#include<string_view>
#include<deque>
#include"profile.h"
#include<unordered_map>
#include<future>
#include"synchronised.h"

using namespace std;

class InvertedIndex {
public:

    struct Index_Data{
        size_t doc_id;
        size_t hitcount;
    };
    InvertedIndex(): empty_list(), index(), docs() {   docs.reserve(50001);}
    InvertedIndex(InvertedIndex&& other): empty_list(other.empty_list),
                                          index(move(other.index)),
                                          docs(move(other.docs)) {}

    InvertedIndex& operator=(InvertedIndex&& other)
    {
        empty_list = other.empty_list;
        index = move(other.index);
        docs = move(other.docs);
        return *this;
    }
    void Add(string document);
    const vector<Index_Data>& Lookup(string_view word) const;

    const string& GetDocument(size_t id) const {
        return docs[id];
    }

    int Get_Size() const {
        return docs.size();
    }
   // void Unlock() { g_lock.unlock();}
  //  void Lock() { g_lock.lock();}

public:
    vector<Index_Data> empty_list;
    unordered_map<string_view, vector<Index_Data>> index;
    vector<string> docs;

};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    std::mutex index_mutex;
    Synchronized<InvertedIndex> index;
    vector<future<void>> ft;
};