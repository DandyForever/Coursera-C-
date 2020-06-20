#include <iostream>
#include <queue>
#include <string>

//#include "to_str.cpp"

using namespace std;

struct Member {
    char op;
    int value;
};

int main() {
    int top = 0;
    cin >> top;
    queue <Member> q;
    q.push({' ', top});
    int n = 0;
    cin >> n;
    string ans;
    for (int i = 0; i < n; i++) {
        char op = ' ';
        int val = 0;
        cin >> op >> val;
        q.push({op, val});
//        ans.push_back('(');
    }
    bool balance = false;
    int brackets = 0;
    while (!q.empty()) {
        Member current = q.front();
        if (current.op == ' ')
            ans += to_string(current.value);
        else if ((current.op == '*' || current.op == '/') && balance) {
            ans += ") " + string{current.op} + " ";
//            if (current.value < 0)
//                ans += "(" + to_string(current.value) + ")";
//            else
                ans += to_string(current.value);
            brackets++;
            balance = false;
        }
        else {
            ans += " " + string{current.op} + " ";
//            if (current.value < 0)
//                ans += "(" + to_string(current.value) + ")";
//            else
                ans += to_string(current.value);
            if (current.op == '+' || current.op == '-')
                balance = true;
        }
        q.pop();
    }
    string brs(brackets, '(');
    cout << brs << ans;
    return 0;
}