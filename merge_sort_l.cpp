#include <cstdio>
#include <iostream>

using namespace std;

const int N = 2e5 + 5;

int n, a[N], link[N];

int in_sort(int low, int high) {
  int p = low;
  for (int i = low + 1; i <= high; i++) {
    if (a[i] < a[p]) {
      link[i] = p;
      p = i;
    } else {
      int t = p;
      while (link[t] && a[i] >= a[link[t]]) t = link[t];
      link[i] = link[t];
      link[t] = i;
    }
  }
  return p;
}

int merge_l(int q, int r) {
  int i = q, j = r, k = 0;
  while (i && j) {
    if (a[i] <= a[j]) {
      link[k] = i;
      k = i;
      i = link[i];
    } else {
      link[k] = j;
      k = j;
      j = link[j];
    }
  }
  if (!i)
    link[k] = j;
  else
    link[k] = i;
  return link[0];
}

int merge_sort_l(int low, int high) {
  if (high - low + 1 <= 16) return in_sort(low, high);
  int mid = low + high >> 1;
  int q = merge_sort_l(low, mid);
  int r = merge_sort_l(mid + 1, high);
  return merge_l(q, r);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  int p = merge_sort_l(1, n);
  while (p) {
    printf("%d ", a[p]);
    p = link[p];
  }
  puts("");
  return 0;
}