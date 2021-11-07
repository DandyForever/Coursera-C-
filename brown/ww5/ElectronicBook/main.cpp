#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager() : users_on_page(MAX_PAGE_NUMBER_ + 1, 0) {}

  void Read(int user_id, int page_count) {
    if (!user_page.count(user_id)) {
        user_page[user_id] = page_count;
        for (int i = 1; i <= page_count; i++)
            users_on_page[i]++;
    }
    int old_page = user_page[user_id];
    user_page[user_id] = page_count;
    for (int i = old_page + 1; i <= page_count; i++) {
        users_on_page[i]++;
    }
  }

  double Cheer(int user_id) const {
    if (!user_page.count(user_id))
        return 0;
    if (user_page.size() == 1)
        return 1;

    return 1.0 * (users_on_page[1] - users_on_page[user_page.at(user_id)]) / (user_page.size() - 1);
  }

private:
  static const int MAX_PAGE_NUMBER_ = 1000;

  map<int, int> user_page;
  vector<int> users_on_page;
};


int main() {
  // Р”Р»СЏ СѓСЃРєРѕСЂРµРЅРёСЏ С‡С‚РµРЅРёСЏ РґР°РЅРЅС‹С… РѕС‚РєР»СЋС‡Р°РµС‚СЃСЏ СЃРёРЅС…СЂРѕРЅРёР·Р°С†РёСЏ
  // cin Рё cout СЃ stdio,
  // Р° С‚Р°РєР¶Рµ РІС‹РїРѕР»РЅСЏРµС‚СЃСЏ РѕС‚РІСЏР·РєР° cin РѕС‚ cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}