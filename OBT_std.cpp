#include <cstring>
#include <iostream>

using namespace std;

const int N = 105;
int n;
int a[N], b[N];
int w[N][N], m[N][N];

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 0; i <= n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) {
    w[i + 1][i] = a[i];
    m[i + 1][i] = 0;
  }
  for (int r = 0; r < n; r++) {
    for (int i = 1; i <= n - r; i++) {
      int j = i + r;
      w[i][j] = w[i][j - 1] + b[j] + a[j];
      m[i][j] = m[i + 1][j];
      for (int k = i + 1; k <= j; k++) {
        int t = m[i][k - 1] + m[k + 1][j];
        if (t < m[i][j]) m[i][j] = t;
      }
      m[i][j] += w[i][j];
    }
  }
  cout << m[1][n] << endl;
  return 0;
}