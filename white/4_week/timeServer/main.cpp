#include <iostream>
#include <exception>
#include <string>
#include <system_error>

using namespace std;

string AskTimeServer() {
}

class TimeServer {
public:
    string GetCurrentTime() {
        try {
            LastFetchedTime = AskTimeServer();
        } catch (system_error& ex) {
            return LastFetchedTime;
        } catch (exception& ex) {
            throw domain_error(ex.what());
        }
        return LastFetchedTime;
    }

private:
    string LastFetchedTime = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}