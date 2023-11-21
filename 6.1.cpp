#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 105;
const int M = 105;

int n, m, d;
int h[N], e[M], w[M], ne[M], idx;
int deg[N], topo_order[N], p;
int res = 0x3f3f3f3f;
bool path[N], ans[N];
int dp[N];
queue<int> que;

void add(int u, int v, int c) {
  e[idx] = v, w[idx] = c, ne[idx] = h[u], h[u] = idx++;
}

int get_left_dist(int level) {
  memset(dp, 0x3f, sizeof dp);
  dp[topo_order[1]] = 0;
  for (int i = 1; i < level; i++) {
    int j = topo_order[i];
    if (path[j]) dp[j] = d;
    for (int k = h[j]; ~k; k = ne[k]) {
      int l = e[k];
      dp[l] = min(dp[l], dp[j] - w[k]);
    }
  }
  return dp[topo_order[level]];
}

void dfs(int level, int cnt) {
  if (cnt >= res) return;
  if (level == n) {
    res = cnt;
    memcpy(ans, path, sizeof path);
    return;
  }
  int cur = topo_order[level];
  int dist = get_left_dist(level);
  bool flag = true;
  for (int i = h[cur]; ~i; i = ne[i]) {
    if (w[i] > dist) {
      flag = false;
      break;
    }
  }
  // 可以不在cur上放置增压器
  if (flag) dfs(level + 1, cnt);
  path[cur] = true;
  dfs(level + 1, cnt + 1);  // 在cur上放置增压器
  path[cur] = false;
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> m >> d;
  memset(h, -1, sizeof h);
  for (int i = 1; i <= m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    add(u, v, c);
    deg[v]++;
  }
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 0) {
      que.push(i);
    }
  }
  while (!que.empty()) {
    int cur = que.front();
    que.pop();
    topo_order[++p] = cur;
    for (int i = h[cur]; i != -1; i = ne[i]) {
      int j = e[i];
      deg[j]--;
      if (deg[j] == 0) {
        que.push(j);
      }
    }
  }
  dfs(1, 0);
  cout << res << endl;
  for (int i = 1; i <= n; i++) {
    if (ans[i]) cout << i << " ";
  }
  return 0;
}