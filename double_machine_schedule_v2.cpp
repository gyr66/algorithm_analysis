#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], b[N];

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  vector<pair<int, int>> v;
  v.push_back({0, 0});
  for (int i = 1; i <= n; i++) {
    vector<pair<int, int>> new_v;
    for (auto item : v) {
      new_v.push_back(make_pair(item.first + a[i], item.second));
      new_v.push_back(make_pair(item.first, item.second + b[i]));
    }
    // 去重
    sort(new_v.begin(), new_v.end());
    new_v.erase(unique(new_v.begin(), new_v.end()), new_v.end());
    v.clear();
    for (int i = 0; i < new_v.size(); i++) {
      bool flag = true;
      for (int j = 0; j < new_v.size(); j++) {
        if (j == i) continue;
        if (new_v[j].first <= new_v[i].first &&
            new_v[j].second <= new_v[i].second) {
          flag = false;
          break;
        }
      }
      if (flag) v.push_back(new_v[i]);
    }
    cout << "step " << i << endl;
    cout << "{ ";
    for (auto item : v) {
      cout << "(" << item.first << "," << item.second << "), ";
    }
    cout << "}\n";
  }
  int res = 1e9;
  for (auto item : v) {
    res = min(res, max(item.first, item.second));
  }
  cout << res << endl;
  cout << v.size() << endl;
}