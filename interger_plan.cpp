#include <iostream>

const int N = 1e5 + 5;
const int M = 1e6 + 5;

int n, b, a[N], c[N], dp[M];

using namespace std;

int main() {
  cin >> n;
  cin >> b;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> c[i];
  for (int i = 1; i <= n; i++) {
    for (int j = b; j >= a[i]; j--) {
      dp[j] = max(dp[j], dp[j - a[i]] + c[i]);
      if (j - 2 * a[i] >= 0) dp[j] = max(dp[j], dp[j - 2 * a[i]] + 2 * c[i]);
    }
  }
  cout << dp[b] << endl;
  return 0;
}
