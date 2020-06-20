#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

void updateServer(istream& document_input, Synchronized<InvertedIndex>& current);
void SearchQuery (istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index);

vector<string_view> SplitIntoWordsView(const string& s) {
    string_view str = s;
    vector<string_view> result;
    while(true) { size_t space = str.find(' '); if (space && str[0]) result.push_back(str.substr(0, space));
        if (space == str.npos) { break; } else { str.remove_prefix(space + 1); }
    }
    return result;
}


SearchServer::SearchServer(istream& document_input) {
  updateServer(document_input, index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    tasks.push_back(async(updateServer, ref(document_input), ref(index)));
}

void updateServer(istream& document_input, Synchronized<InvertedIndex>& current) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(current_document);
    }
    swap(current.GetAccess().ref_to_value, new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    tasks.push_back(async(SearchQuery, ref(query_input), ref(search_results_output), ref(index)));
}

void SearchQuery (istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index) {
    vector<size_t> docid_count;
    for (string current_query; getline(query_input, current_query); ) {
        auto words = SplitIntoWordsView(current_query);
        size_t size = 0;
        {
            auto access = index.GetAccess();
            size = access.ref_to_value.GetSize();
            docid_count.assign(size, 0);

            for (auto word : words) {
                for (const auto &docid : access.ref_to_value.Lookup(word)) {
                    docid_count[docid.first] += docid.second;
                }
            }
        }
        vector<pair<size_t, size_t>> search_results(size);
        for (int i = 0; i < size; i++) {
            search_results[i] = {i, docid_count[i]};
        }
        partial_sort(
                begin(search_results),
                begin(search_results) + min<size_t>(5, search_results.size()),
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
            if (hitcount)
                search_results_output << " {"
                                      << "docid: " << docid << ", "
                                      << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(string& document) {
  docs.push_back(move(document));

  const size_t docid = docs.size() - 1;
  for (string_view word : SplitIntoWordsView(docs.back())) {
      auto& docids = index[word];
      if (!docids.empty() && docids.back().first == docid ) {
          docids.back().second++;
      } else {
          docids.push_back({docid, 1});
      }
  }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(string_view word) const {
    static vector<pair<size_t, size_t>> result;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return result;
    }
}
