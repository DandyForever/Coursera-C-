#include "stats.h"

Stats::Stats() {
    method_stats_["GET"] = 0;
    method_stats_["POST"] = 0;
    method_stats_["PUT"] = 0;
    method_stats_["DELETE"] = 0;
    method_stats_["UNKNOWN"] = 0;

    uri_stats_["/"] = 0;
    uri_stats_["/order"] = 0;
    uri_stats_["/product"] = 0;
    uri_stats_["/basket"] = 0;
    uri_stats_["/help"] = 0;
    uri_stats_["unknown"] = 0;
}

void Stats::AddMethod(string_view method) {
    if (method == "GET") method_stats_["GET"]++;
    else if (method == "POST") method_stats_["POST"]++;
    else if (method == "PUT") method_stats_["PUT"]++;
    else if (method == "DELETE") method_stats_["DELETE"]++;
    else method_stats_["UNKNOWN"]++;
}

void Stats::AddUri(string_view uri) {
    if (uri == "/") uri_stats_["/"]++;
    else    if (uri == "/order") uri_stats_["/order"]++;
    else if (uri == "/product") uri_stats_["/product"]++;
    else if (uri == "/basket") uri_stats_["/basket"]++;
    else if (uri == "/help") uri_stats_["/help"]++;
    else uri_stats_["unknown"]++;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest request;
    size_t space = line.find(' ');
    while (line.substr(0, space) == "") {
        line.remove_prefix(space + 1);
        space = line.find(' ');
    }
    request.method  = line.substr (0, space);
    line.remove_prefix (space + 1);
    space = line.find(' ');
    request.uri  = line.substr (0, space);
    line.remove_prefix (space + 1);
    space = line.find(' ');
    request.protocol = line.substr (0, space);
    return request;
}