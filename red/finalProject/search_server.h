#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <future>
#include <string>
#include "synchronized.h"
using namespace std;

class InvertedIndex {
public:
  void Add(string& document);
    const vector<pair<size_t, size_t>>& Lookup(string_view word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

  size_t GetSize () const { return docs.size(); }

    auto GetIndex () const {return index;}

private:
  map<string_view, vector<pair<size_t, size_t>>> index;
  deque<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> tasks;
};
