#include <iostream>
#include "json.h"

using namespace std;

namespace Json {

    Document::Document(Node root) : root(move(root)) {
    }

    const Node& Document::GetRoot() const {
        return root;
    }

    Node LoadNode(istream& input);

    Node LoadArray(istream& input) {
        vector<Node> result;

        for (char c; input >> c && c != ']'; ) {
            if (c != ',') {
                input.putback(c);
            }
            result.push_back(LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadDouble(istream& input) {
        double result = 0;

        bool is_negative = input.peek() == '-';
        if (is_negative)
            input.ignore();
        while (isdigit(input.peek())) {
            result *= 10;
            result += input.get() - '0';
        }
        double fraction = 0, divide = 1;
        if (input.peek() == '.') {
            input.ignore();
            while (isdigit(input.peek())) {
                divide *= 10;
                fraction *= 10;
                fraction += input.get() - '0';
            }
        }
        return Node(result + fraction / divide);
    }

    Node LoadBool(istream& input) {
        string line;
        getline(input, line, 'e');
        if (line == "tru")
            return Node(true);
        return Node(false);
    }

    Node LoadString(istream& input) {
        string line;
        getline(input, line, '"');
        return Node(move(line));
    }

    Node LoadDict(istream& input) {
        map<string, Node> result;

        for (char c; input >> c && c != '}'; ) {
            if (c == ',') {
                input >> c;
            }

            string key = LoadString(input).AsString();
            input >> c;
            result.emplace(move(key), LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNode(istream& input) {
        char c;
        input >> c;

        if (c == '[') {
            return LoadArray(input);
        } else if (c == '{') {
            return LoadDict(input);
        } else if (c == '"') {
            return LoadString(input);
        } else if (c == 't' || c == 'f') {
          input.putback(c);
            return LoadBool(input);
        } else {
            input.putback(c);
            return LoadDouble(input);
        }
    }

    Document Load(istream& input) {
        return Document{LoadNode(input)};
    }

}