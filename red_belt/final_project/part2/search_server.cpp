#include "search_server.h"
#include "iterator_range.h"
#include"parse.h"
#include<string_view>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include<future>

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

vector<string_view> Split(string_view str) {
    vector<string_view> result;
    while (!str.empty() && isspace(str.back()))
        str.remove_suffix(1);
    while (!str.empty()) {
        while (!str.empty() && isspace(str.front()))
            str.remove_prefix(1);

        size_t pos = str.find(' ');
        result.push_back(str.substr(0, pos));
        str.remove_prefix(pos != str.npos ? pos + 1 : str.size());
    }
    return result;
}

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void UpdateDocumentThread(istream& document_input, Synchronized<InvertedIndex>& synchronized_index)
{
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); ) {
        // cout << current_document << endl;
        new_index.Add(move(current_document));
    }
    //index.Lock();
    //lock_guard<mutex> g(index_mutex);
    auto access = synchronized_index.GetAccess();
    swap(access.ref_to_value, new_index);
    //  index = move(new_index);
    //index.Unlock();
}


void SearchServer::UpdateDocumentBase(istream& document_input) {
   future<void>(async(UpdateDocumentThread, ref(document_input), ref(index)));

}

void AddQueriesThread(istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& synchronized_index)
{
    size_t size = synchronized_index.GetAccess().ref_to_value.Get_Size();

   // vector<pair<size_t , size_t>> docid_count(size);

    vector<size_t> docid_count(size);
    // index.Lock();
   // lock_guard<mutex> g(index_mutex);

    for (string current_query; getline(query_input, current_query);) {
       // cout << current_query << endl;
        vector<pair<size_t, size_t>> search_results;
        search_results.reserve(size);
        for (const auto &word : Split(current_query)) {
            auto docids = synchronized_index.GetAccess().ref_to_value.Lookup(word);
            for (auto it = docids.begin(); it < docids.end(); it++)
                docid_count[it->doc_id] += it->hitcount;

        }


        size_t min = 0;
        for (auto it = docid_count.begin(); it < docid_count.end(); it++) {
            if (*it != 0 && (*it >= min || search_results.size() <= 5)) {
                if (*it <= min)
                    min = *it;
                search_results.emplace_back(make_pair(it - docid_count.begin(), *it));
            }
            *it = 0;
        }
     //   cout << docid_count.size() << endl;
        //cout << search_results << endl;
      //  for(auto& x: search_results)
         //   cout << x.first << " " << x.second << endl;
        partial_sort(
                begin(search_results), Head(search_results, 5).end(),
                end(search_results),
                [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                    int64_t lhs_docid = lhs.first;
                    auto lhs_hit_count = lhs.second;
                    int64_t rhs_docid = rhs.first;
                    auto rhs_hit_count = rhs.second;
                    return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                }
        );

     //   search_results_output << "jldskegdhjgjhgdjhfjk"<< endl;

        search_results_output << current_query << ':';
        for (auto[docid, hitcount] : Head(search_results, 5)) {
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';

    }


}


void SearchServer::AddQueriesStream(
        istream& query_input, ostream& search_results_output
) {

    ft.push_back(async(launch::async, AddQueriesThread, ref(query_input), ref(search_results_output), ref(index)));
   // cout << search_results_output.str() << endl;
}

void InvertedIndex::Add(string document) {
    docs.push_back(move(document));

    const size_t docid = docs.size() - 1;
    for (auto word : Split(docs.back())) {
        auto ind = &index[word];
        if(ind->empty()) {
            ind->push_back({docid, 1});
            continue;
        }
        //auto ind = &index[word];
        auto end_it = ind->end();
        for(auto it = ind->begin(); it < end_it; it++)
        {
            if(it->doc_id == docid)
            {
                (it->hitcount)++;
                break;
            }
            if(it + 1 == end_it)
                ind->push_back({docid, 1});
        }
    }
}

const vector<InvertedIndex::Index_Data>& InvertedIndex::Lookup(string_view word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty_list;
    }
}