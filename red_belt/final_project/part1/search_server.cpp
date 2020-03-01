#include "search_server.h"
#include "iterator_range.h"
#include"parse.h"

#include<string_view>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

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

void SearchServer::UpdateDocumentBase(istream& document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(
        istream& query_input, ostream& search_results_output
) {
    LOG_DURATION("ADD");
    vector<size_t> docid_count(index.Get_Size());

    for (string current_query; getline(query_input, current_query); ) {

        vector<pair<size_t, size_t>> search_results;
        search_results.reserve(index.Get_Size());
        for(const auto& word : Split(current_query)) {
            auto docids = index.Lookup(word);
            for(auto it = docids.begin(); it < docids.end(); it++)
                docid_count[it->doc_id] += it->hitcount;

        }


       // vector<pair<size_t, size_t>> search_results; // рейтинг документов
      //  search_results.reserve(index.Get_Size());
        size_t min = 0;
        for(auto it = docid_count.begin(); it < docid_count.end(); it++)
        {
            if(*it != 0 && (*it >= min || search_results.size() <= 5))
            {
                if(*it <= min)
                    min = *it;
                search_results.emplace_back(make_pair(it - docid_count.begin(), *it));
            }
            *it = 0;
        }
//        vector<pair<size_t, size_t>> search_results(
//                docid_count.begin(), docid_count.end()
//        );
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

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5)) {
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(string document) {
    docs.push_back(move(document));
    //cout << "ok"<< endl;
  //  LOG_DURATION("Adding");
    const size_t docid = docs.size() - 1;
    for (auto word : Split(docs.back())) {
        //cout << "ok"<< endl;
        if(index[word].empty()) {
            index[word].push_back({docid, 1});
            continue;
        }
        auto end_it = index[word].end();
        for(auto it = index[word].begin(); it < end_it; it++)
        {//cout << "ok"<< endl;
            if(it->doc_id == docid)
            {//cout << "ok"<< endl;
                (it->hitcount)++;
                break;
            }
            if(it + 1 == end_it)
                index[word].push_back({docid, 1});
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