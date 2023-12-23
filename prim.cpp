#include <cstring>
#include <iostream>

using namespace std;

const int N = 505;

int n, m;
int a[N][N], dist[N];
bool st[N];
int res;

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> m;
  memset(a, 0x3f, sizeof a);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    a[u][v] = min(a[u][v], w);
    a[v][u] = min(a[v][u], w);
  }
  memset(dist, 0x3f, sizeof dist);
  dist[1] = 0;
  for (int i = 1; i <= n; i++) {
    int min_value = 0x3f3f3f3f;
    int choice = -1;
    for (int i = 1; i <= n; i++) {
      if (!st[i] && dist[i] < min_value) {
        min_value = dist[i];
        choice = i;
      }
    }
    if (choice == -1) {
      puts("impossible");
      return 0;
    }
    res += min_value;
    st[choice] = true;
    for (int i = 1; i <= n; i++) {
      if (!st[i] && dist[i] > a[choice][i]) {
        dist[i] = a[choice][i];
      }
    }
  }
  cout << res << endl;
  return 0;
}