#include <iostream>

using namespace std;

const int N = 105;
const int INF = 1e9;

int n, t[N];
int status[4];
int res = INF;
int path[N], ans[N];

// 当前为第cur个任务安排机器，完成之前的任务所需的时间为cost
void dfs(int cur, int cost) {
  if (cost >= res) return;
  if (cur == n + 1) {
    res = cost;
    memcpy(ans, path, sizeof path);
    return;
  }
  for (int i = 1; i <= 4; i++) {
    path[cur] = i;  // 第cur个任务安排到第i台机器
    status[i] += t[cur];
    int c = 0;
    for (int j = 1; j <= 4; j++) {
      c = max(c, status[j]);
    }
    dfs(cur + 1, c);
    status[i] -= t[cur];
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> t[i];
  dfs(1, 0);
  cout << res << endl;
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}