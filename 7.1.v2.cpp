#include <iostream>
#include <queue>
#include <set>

using namespace std;

const int N = 105;

int n;
int a[N][N];
int res = 0x3f3f3f3f;

struct Item {
  int x;          // 节点编号
  int cost;       // 花费
  set<int> path;  // 路径
  vector<int> note;

  bool operator<(const Item& b) const { return cost > b.cost; }
};

queue<Item> que;

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  que.push({1, 0, {1}, {1}});
  while (!que.empty()) {
    auto t = que.front();
    auto path = t.path;
    que.pop();
    // cout << "path: ";
    // for (auto i : t.note) {
    //   cout << i << " ";
    // }
    // cout << endl;
    // cout << "cost: " << t.cost << endl;
    vector<int> ext;
    if (t.cost >= res) continue;
    if (path.size() == n) {
      int cost = t.cost + a[t.x][1];
      res = min(res, cost);
    }
    for (int i = 1; i <= n; i++) {
      if (path.count(i)) continue;
      auto ne = t;
      ne.x = i;
      ne.cost += a[t.x][i];
      ne.path.insert(i);
      ne.note.push_back(i);
      que.push(ne);
      ext.push_back(i);
      cout << ne.cost << endl;
    }
  }
  return 0;
}