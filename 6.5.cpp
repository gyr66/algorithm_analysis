#include <iostream>

using namespace std;

const int N = 105;
const int M = 105;

struct Node {
  int w, c;
} provider[N][M];

int n, m, c;
int res = 1e9;
int path[N], ans[N];

pair<int, int> estimate(int cur) {
  int cw = 0, cc = 0;
  for (int i = 1; i <= cur; i++) {
    cw += provider[i][path[i]].w;
    cc += provider[i][path[i]].c;
  }
  for (int i = cur + 1; i <= n; i++) {
    int minw = 1e9, minc = 1e9;
    for (int j = 1; j <= m; j++) {
      if (provider[i][j].w < minw) {
        minw = provider[i][j].w;
      }
    }
    for (int j = 1; j <= m; j++) {
      if (provider[i][j].c < minc) {
        minc = provider[i][j].c;
      }
    }
    cw += minw;
    cc += minc;
  }
  return make_pair(cw, cc);
}

void dfs(int cur, int cw, int cc) {
  if (cw >= res) return;
  if (cur == n + 1) {
    res = cw;
    memcpy(ans, path, sizeof path);
    return;
  }
  for (int i = 1; i <= m; i++) {
    path[cur] = i;
    auto est = estimate(cur);
    if (est.first >= res) continue;
    if (est.second > c) continue;
    dfs(cur + 1, cw + provider[cur][i].w, cc + provider[cur][i].c);
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> m >> c;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> provider[i][j].w >> provider[i][j].c;
    }
  }
  dfs(1, 0, 0);
  cout << res << endl;
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  return 0;
}