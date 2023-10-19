#include <math.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int N = 2e4 + 5;
const int M = 1e5 + 5;

int n, m;
int h[N], e[2 * M], ne[2 * M], idx;
int dfn[N], low[N];
int time_stamp;
vector<int> ans;
stack<int> sta;
int dcc_cnt;
vector<int> dcc[N];

void add(int u, int v) { e[idx] = v, ne[idx] = h[u], h[u] = idx++; }

void dfs(int u, int fa) {
  dfn[u] = low[u] = ++time_stamp;
  sta.push(u);
  int cnt = 0;
  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if (!dfn[j]) {
      dfs(j, u);
      if (low[j] >= dfn[u]) {
        cnt++;
        dcc_cnt++;
        int y;
        do {
          y = sta.top();
          sta.pop();
          dcc[dcc_cnt].push_back(y);
        } while (y != j);
        dcc[dcc_cnt].push_back(u);
      } else
        low[u] = min(low[u], low[j]);
    } else {
      low[u] = min(low[u], dfn[j]);
    }
  }
  if (cnt > 1) {
    ans.push_back(u);
  } else if (~fa && cnt == 1) {
    ans.push_back(u);
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> m;
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    add(x, y);
    add(y, x);
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      dfs(i, -1);
    }
  }
  cout << ans.size() << endl;
  sort(ans.begin(), ans.end());
  for (auto v : ans) {
    cout << v << " ";
  }
  puts("");
  cout << dcc_cnt << endl;
  for (int i = 1; i <= dcc_cnt; i++) {
    for (auto j : dcc[i]) {
      cout << j << " ";
    }
    puts("");
  }
  return 0;
}