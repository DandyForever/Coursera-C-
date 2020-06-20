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
    double Apply () const {
        if (operation == '+')
            return part;
        else
            return (-part);
    }
    void Invert () {
        if (operation == '+')
            operation = '-';
        else
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
            param += part.Apply();
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
