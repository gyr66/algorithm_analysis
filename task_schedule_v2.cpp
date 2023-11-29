#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1e5 + 5;

struct Item {
  int val;
  int ddl;
};

int n, f[N];
Item a[N];
long long sum = 0;

int getfa(int x) {
  if (x == f[x]) return x;
  return f[x] = getfa(f[x]);
}

void _merge(int u, int v) {
  int fu = getfa(u), fv = getfa(v);
  if (fu != fv) f[fu] = fv;
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].val >> a[i].ddl;
  sort(a + 1, a + 1 + n,
       [](const Item& x, const Item& y) { return x.val > y.val; });
  for (int i = 1; i <= n; i++) f[i] = i;
  for (int i = 1; i <= n; i++) {
    int t = min(n, a[i].ddl);
    int fa = getfa(t);
    if (fa) {
      sum += a[i].val;
      _merge(fa, fa - 1);
    }
  }
  cout << sum << endl;
  return 0;
}