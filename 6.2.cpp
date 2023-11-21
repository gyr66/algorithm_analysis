#include <cstring>
#include <iostream>

using namespace std;

const int N = 105;
const int INF = 1e9;

int n, a[N];
int cost[N][N];
int path[N], ans[N];
int res = INF;

// 当前给第cur个人分配工作，前cur-1个人花费为cc
void dfs(int cur, int cc) {
  if (cc >= res) return;
  if (cur == n + 1) {
    res = cc;
    memcpy(ans, path, sizeof path);
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (path[i]) continue;
    path[i] = cur;  // 将第i个工作分配给cur
    dfs(cur + 1, cc + cost[i][cur]);
    path[i] = 0;
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> cost[i][j];
    }
  }
  dfs(1, 0);
  cout << res << endl;
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}