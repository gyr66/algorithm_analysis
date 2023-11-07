#include <iostream>

using namespace std;

const int N = 1e5 + 5;
const int M = 1e6 + 5;

int n, a[N], b[N], dp[M];
int sum_a;

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum_a += a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = sum_a; j >= 0; j--) {
      dp[j] += b[i];
      if (j >= a[i]) dp[j] = min(dp[j], dp[j - a[i]]);
    }
  }
  // for (int i = 0; i <= sum_a; i++) {
  //   cout << dp[i] << endl;
  // }
  int res = sum_a;
  for (int i = 0; i <= sum_a; i++) {
    res = min(res, max(i, dp[i]));
  }
  cout << res << endl;
  return 0;
}
/*
6
2 5 7 10 5 2
3 8 4 11 3 4
*/