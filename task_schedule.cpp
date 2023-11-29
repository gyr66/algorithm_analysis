#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1e5 + 5;

struct Item {
  int val;
  int ddl;
};

int n, J[N];
Item a[N];
long long sum = 0;

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].val >> a[i].ddl;
  sort(a + 1, a + 1 + n,
       [](const Item& x, const Item& y) { return x.val > y.val; });
  J[1] = 1;
  int k = 1;
  for (int i = 2; i <= n; i++) {
    int r = k;
    while (r && a[i].ddl < a[J[r]].ddl && a[J[r]].ddl != r) r--;
    if (a[i].ddl >= a[J[r]].ddl && a[i].ddl > r) {
      for (int j = k; j > r; j--) J[j + 1] = J[j];
      J[r + 1] = i;
      k++;
    }
  }
  for (int i = 1; i <= n; i++) {
    sum += a[J[i]].val;
  }
  cout << sum << endl;
  return 0;
}