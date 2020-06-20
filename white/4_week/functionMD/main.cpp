#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FunctionPart {
public:
    FunctionPart (char operation1, double part1) {
        operation = operation1;
        part = part1;
    }
    double Apply (double value) const {
        if (operation == '*')
            return value * part;
        else if (operation == '/')
            return value / part;
        else if (operation == '+')
            return value + part;
        else if (operation == '-')
            return value-part;
    }
    void Invert () {
        if (operation == '*')
            operation = '/';
        else if (operation == '/')
            operation = '*';
        else if (operation == '+')
            operation = '-';
        else if (operation == '-')
            operation = '+';
    }
private:
    char operation;
    double part;
};

class Function {
public:
    void AddPart (char operation, double part) {
        parts.push_back({operation, part});
    }
    double Apply (double param) const {
        for (const auto& part : parts) {
            param = part.Apply(param);
        }
        return param;
    }

    void Invert () {
        for (auto& part : parts) {
            part.Invert();
        }
        reverse (begin(parts), end(parts));
    }

private:
    vector <FunctionPart> parts;
};
