#include <cstring>
#include <iostream>

using namespace std;

const int N = 105;
int n;
int a[N], b[N];
int w[N][N], dp[N][N];

void debug() {
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j <= n; j++) {
      cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 0; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n + 1; i++) w[i][i - 1] = a[i - 1];
  memset(dp, 0x3f, sizeof dp);
  for (int i = 1; i <= n + 1; i++) dp[i][i - 1] = 0;
  for (int len = 1; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      w[l][r] = w[l][r - 1] + b[r] + a[r];
      for (int k = l; k <= r; k++) {
        dp[l][r] = min(dp[l][r], dp[l][k - 1] + dp[k + 1][r] + w[l][r]);
      }
    }
  }
  // debug();
  cout << dp[1][n] << endl;
  return 0;
}