#include <iostream>

using namespace std;

const int N = 105;

int n, m, k, ans;
int a[N][N], color[N];

void dfs(int cur) {
  if (cur == n + 1) {
    ans++;
    for (int i = 1; i <= n; i++) {
      cout << color[i] << " ";
    }
    cout << endl;
    return;
  }
  for (int i = 1; i <= k; i++) {
    bool flag = true;
    for (int j = 1; j <= n; j++) {
      if (a[cur][j] && color[j] == i) {
        flag = false;
        break;
      }
    }
    if (!flag) continue;
    color[cur] = i;
    dfs(cur + 1);
    color[cur] = 0;
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    a[u][v] = 1;
    a[v][u] = 1;
  }
  dfs(1);
  cout << ans << endl;
  return 0;
}