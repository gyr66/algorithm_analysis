#include <iostream>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], b[N];

void merge_sort(int l, int r) {
  if (l >= r) return;
  int mid = l + r >> 1;
  merge_sort(l, mid);
  merge_sort(mid + 1, r);
  int i = l, j = mid + 1, k = l;
  while (i <= mid && j <= r) {
    if (a[i] < a[j]) {
      b[k] = a[i];
      i++;
      k++;
    } else {
      b[k] = a[j];
      j++;
      k++;
    }
  }
  for (int t = i; t <= mid; t++) {
    b[k] = a[t];
    k++;
  }
  for (int t = j; t <= r; t++) {
    b[k] = a[t];
    k++;
  }
  for (int i = l; i <= r; i++) {
    a[i] = b[i];
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  merge_sort(1, n);
  for (int i = 1; i <= n; i++) {
    cout << a[i] << " ";
  }
  return 0;
}