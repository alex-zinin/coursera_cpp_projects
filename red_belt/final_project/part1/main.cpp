#include "search_server.h"
#include "parse.h"
#include "test_runner.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include"profile.h"

using namespace std;

void TestFunctionality(
        const vector<string>& docs,
        const vector<string>& queries,
        const vector<string>& expected
) {
    istringstream docs_input(Join('\n', docs));
    istringstream queries_input(Join('\n', queries));

    SearchServer srv;
    {
        LOG_DURATION("ADD_DOC");
        srv.UpdateDocumentBase(docs_input);
    }
    //srv.UpdateDocumentBase(docs_input);
        ostringstream queries_output;

    srv.AddQueriesStream(queries_input, queries_output);

    const string result = queries_output.str();
    const auto lines = SplitBy(Strip(result), '\n');
    ASSERT_EQUAL(lines.size(), expected.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        ASSERT_EQUAL(lines[i], expected[i]);
    }
}

void TestSerpFormat() {
    const vector<string> docs = {
            "london is the capital of great britain",
            "i am travelling down the river"
    };
    const vector<string> queries = {"london", "the"};
    const vector<string> expected = {
            "london: {docid: 0, hitcount: 1}",
            Join(' ', vector{
                    "the:",
                    "{docid: 0, hitcount: 1}",
                    "{docid: 1, hitcount: 1}"
            })
    };

    TestFunctionality(docs, queries, expected);
}

void TestTop5() {
    const vector<string> docs = {
            "milk a",
            "milk b",
            "milk c",
            "milk d",
            "milk e",
            "milk f",
            "milk g",
            "water a",
            "water b",
            "fire and earth"
    };

    const vector<string> queries = {"milk", "water", "rock"};
    const vector<string> expected = {
            Join(' ', vector{
                    "milk:",
                    "{docid: 0, hitcount: 1}",
                    "{docid: 1, hitcount: 1}",
                    "{docid: 2, hitcount: 1}",
                    "{docid: 3, hitcount: 1}",
                    "{docid: 4, hitcount: 1}"
            }),
            Join(' ', vector{
                    "water:",
                    "{docid: 7, hitcount: 1}",
                    "{docid: 8, hitcount: 1}",
            }),
            "rock:",
    };
    TestFunctionality(docs, queries, expected);
}

void TestHitcount() {
    const vector<string> docs = {
            "the river goes through the entire city there is a house near it",
            "the wall",
            "walle",
            "is is is is",
    };
    const vector<string> queries = {"the", "wall", "all", "is", "the is"};
    const vector<string> expected = {
            Join(' ', vector{
                    "the:",
                    "{docid: 0, hitcount: 2}",
                    "{docid: 1, hitcount: 1}",
            }),
            "wall: {docid: 1, hitcount: 1}",
            "all:",
            Join(' ', vector{
                    "is:",
                    "{docid: 3, hitcount: 4}",
                    "{docid: 0, hitcount: 1}",
            }),
            Join(' ', vector{
                    "the is:",
                    "{docid: 3, hitcount: 4}",
                    "{docid: 0, hitcount: 3}",
                    "{docid: 1, hitcount: 1}",
            }),
    };
    TestFunctionality(docs, queries, expected);
}

void TestRanking() {
    const vector<string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",

 "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockgolm is the capital of sweden",
            "riga is the capital of latvia",
            "tallin is the capital of estonia",
            "warsaw is the capital of poland",
    };

    const vector<string> queries = {"moscow is the capital of russia"};
    const vector<string> expected = {
            Join(' ', vector{
                    "moscow is the capital of russia:",
                    "{docid: 7, hitcount: 6}",
                    "{docid: 14, hitcount: 6}",
                    "{docid: 0, hitcount: 4}",
                    "{docid: 1, hitcount: 4}",
                    "{docid: 2, hitcount: 4}",
            })
    };
    TestFunctionality(docs, queries, expected);
}

void TestBasicSearch() {
    const vector<string> docs = {
            "we are ready to go",
            "come on everybody shake you hands",
            "i love this game",
            "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
            "daddy daddy daddy dad dad dad",
            "tell me the meaning of being lonely",
            "just keep track of it",
            "how hard could it be",
            "it is going to be legen wait for it dary legendary",
            "we dont need no education"
    };

    const vector<string> queries = {
            "we need some help",
            "it",
            "i love this game",
            "tell me why",
            "dislike",
            "about"
    };

    const vector<string> expected = {
            Join(' ', vector{
                    "we need some help:",
                    "{docid: 9, hitcount: 2}",
                    "{docid: 0, hitcount: 1}"
            }),
            Join(' ', vector{
                    "it:",
                    "{docid: 8, hitcount: 2}",
                    "{docid: 6, hitcount: 1}",
                    "{docid: 7, hitcount: 1}",
            }),
            "i love this game: {docid: 2, hitcount: 4}",
            "tell me why: {docid: 5, hitcount: 2}",
            "dislike:",
            "about: {docid: 3, hitcount: 2}",
    };
    TestFunctionality(docs, queries, expected);
}

void RUN_TIME_TEST() {
    const int vald = 2000;
    const int valq = 500;
    const vector<string> doc = {
            "we are ready to go fjkhjs kjlreg jkds vkdsvlj lkdsjg jsd ",
            "come on everybody shake you hands",
            "i love this game wkej;e os,djs fh dsdf hg fd  bg bg ",
            "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
            "daddy daddy daddy dad dad dad",
            "tell me the meaning of being lonely",
            "just keep track of it jdgskljklegwjklre r t fdh hdf",
            "how hard could it be kdsfhj rej jher hg  er re",
            "it is going to be legen wait for it dary legendary",
            "we dont need no education erkjl kr jker rg "
    };

    vector<string> docs;
    for (int i = 0; i < vald; i++) {
        docs.insert(docs.end(), doc.begin(), doc.end());
    }

    const vector<string> querie = {
            "we need some help thr",
            "i love this game dfe",
            "tell me why thr",
            "dislike thr",
            "about thr aqs"
    };

    vector<string> queries;
    for(int i = 0; i < valq; i++)
    {
        queries.insert(queries.end(), querie.begin(), querie.end());
    }


    const vector<string> expected = {
            Join(' ', vector{
                    "we need some help:",
                    "{docid: 9, hitcount: 2}",
                    "{docid: 0, hitcount: 1}"
            }),
            Join(' ', vector{
                    "it:",
                    "{docid: 8, hitcount: 2}",
                    "{docid: 6, hitcount: 1}",
                    "{docid: 7, hitcount: 1}",
            }),
            "i love this game: {docid: 2, hitcount: 4}",
            "tell me why: {docid: 5, hitcount: 2}",
            "dislike:",
            "about: {docid: 3, hitcount: 2}",
    };
    LOG_DURATION("RUN_TIME_TEST")
    TestFunctionality(docs, queries, expected);


}


void Test()
{
    const int vald = 1;
    const int valq = 1;
    const vector<string> doc = {
            "a   b c   d",
            "  a b c d",
            "   c  d e f   ",
            "d  e f    g ",
    };

    vector<string>  docs;

    docs.insert(docs.end(), doc.begin(), doc.end());


    const vector<string> querie = {
            "a",
            "b",
            "c",
            "d",
            "e",
            "f",
            "g",
            "b  c   d  f",
            "cde g",
            "c d",
            "a b",
            "g       ",
    };

    vector<string> queries;
    for(int i = 0; i < valq; i++)
    {
        queries.insert(queries.end(), querie.begin(), querie.end());
    }


    const vector<string> expected = {
            Join(' ', vector{ "a: {docid: 0, hitcount: 1} {docid: 1, hitcount: 1}",
                              "b: {docid: 0, hitcount: 1} {docid: 1, hitcount: 1}",
                              "c: {docid: 0, hitcount: 1} {docid: 1, hitcount: 1} {docid: 2, hitcount: 1}",
                              "d: {docid: 0, hitcount: 1} {docid: 1, hitcount: 1} {docid: 2, hitcount: 1} {docid: 3, hitcount: 1}",
                              "e: {docid: 2, hitcount: 1} {docid: 3, hitcount: 1}",
                              "f: {docid: 2, hitcount: 1} {docid: 3, hitcount: 1}",
                              "g: {docid: 3, hitcount: 1}",
          "b  c   d  f: {docid: 0, hitcount: 3} {docid: 1, hitcount: 3} {docid: 2, hitcount: 3} {docid: 3, hitcount: 2}",
            "cde g: {docid: 3, hitcount: 1}",
            "c d: {docid: 0, hitcount: 2} {docid: 1, hitcount: 2} {docid: 2, hitcount: 2} {docid: 3, hitcount: 1}",
            "a b  : {docid: 0, hitcount: 2} {docid: 1, hitcount: 2}",
            "g    : {docid: 3, hitcount: 1}"
            }),
            };
   // LOG_DURATION("RUN_TIME_TEST")
    TestFunctionality(docs, queries, expected);


}



int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSerpFormat);
    RUN_TEST(tr, TestTop5);
    RUN_TEST(tr, TestHitcount);
    RUN_TEST(tr, TestRanking);
    RUN_TEST(tr, TestBasicSearch);
   // RUN_TEST(tr, Test);
    RUN_TEST(tr, RUN_TIME_TEST);
}