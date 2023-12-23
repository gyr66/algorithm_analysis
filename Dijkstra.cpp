#include <cstring>
#include <iostream>

using namespace std;

const int N = 505;
const int INF = 0x3f3f3f3f;

int n, m, res;
int w[N][N];
int dist[N];
bool st[N];

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> m;
  memset(w, 0x3f, sizeof w);
  for (int i = 1; i <= m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    w[u][v] = min(w[u][v], c);
  }
  memset(dist, 0x3f, sizeof dist);
  dist[1] = 0;
  for (int i = 1; i <= n; i++) {
    int min_value = INF, choice = -1;
    for (int i = 1; i <= n; i++) {
      if (!st[i] && dist[i] < min_value) {
        min_value = dist[i];
        choice = i;
      }
    }
    if (choice == -1) {
      puts("-1");
      return 0;
    }
    if (choice == n) {
      cout << dist[n] << endl;
      return 0;
    }
    st[choice] = true;
    for (int i = 1; i <= n; i++) {
      if (!st[i] && dist[i] > dist[choice] + w[choice][i]) {
        dist[i] = dist[choice] + w[choice][i];
      }
    }
  }
  cout << dist[n] << endl;
  return 0;
}