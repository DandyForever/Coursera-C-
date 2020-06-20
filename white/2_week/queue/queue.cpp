#include <iostream>
#include <vector>

using namespace std;

int main (){
    int n = 0;
    cin >> n;
    vector <bool> state;
    string current;
    int command = 0;
    int worried = 0;
    for (int i = 0; i < n; i++){
        cin >> current;
        if (current == "COME"){
            cin >> command;

            if (command > 0) for (int j = 0; j < command; j++) state.push_back(0);
            else for (int j = 0; j < -command; j++){
                if (state[state.size() - 1] == 1) worried--;
                state.pop_back();
            }
        } else if (current == "WORRY"){
            cin >> command;
            state[command] = 1;
            worried++;
        }
        else if (current == "QUIET"){
            cin >> command;
            if (state[command] == 1) worried--;
            state[command] = 0;
        }
        else if (current == "WORRY_COUNT")
            cout << worried << endl;
    }
    return 0;
}
