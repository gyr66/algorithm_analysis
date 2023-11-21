#include <cstring>
#include <iostream>

using namespace std;

const int N = 105;
const int M = 105;

int n, m;
int res = 1e9;
bool matrix[N][M];
bool path[N][M], ans[N][M];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

void mark(int x, int y) {
  matrix[x][y] = true;
  for (int i = 0; i < 4; i++) {
    int xx = x + dx[i], yy = y + dy[i];
    if (xx >= 1 && xx <= n && yy >= 1 && yy <= m) {
      matrix[xx][yy] = true;
    }
  }
}

void refresh_matrix(int x, int y) {
  memset(matrix, false, sizeof matrix);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      if (path[i][j]) {
        mark(i, j);
      }
  }
}

pair<int, int> inline get_next(int x, int y) {
  if (y == m)
    return make_pair(x + 1, 1);
  else
    return make_pair(x, y + 1);
}

bool check() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!matrix[i][j]) return false;
    }
  }
  return true;
}

void dfs(int x, int y, int cnt) {
  if (cnt >= res) return;
  if (x == n + 1) {
    if (check()) {
      res = cnt;
      memcpy(ans, path, sizeof path);
    }
    return;
  }
  auto ne = get_next(x, y);
  path[x][y] = true;
  refresh_matrix(x, y);
  dfs(ne.first, ne.second, cnt + 1);
  path[x][y] = false;
  refresh_matrix(x, y);
  if (x == 1 || matrix[x - 1][y]) {
    dfs(ne.first, ne.second, cnt);
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> m;
  dfs(1, 1, 0);
  cout << res << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (ans[i][j])
        cout << "X ";
      else
        cout << "O ";
    }
    cout << endl;
  }
  return 0;
}
/*
input:
3 5
output:
4
O O X O O
X O O O X
O O X O O
*/