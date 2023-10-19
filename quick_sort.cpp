#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1e6 + 5;

int n, a[N];

void quick_sort(int a[], int l, int r) {
  if (l >= r) return;
  int i = l - 1, j = r + 1, x = a[l];
  while (i < j) {
    do i++;
    while (a[i] < x);
    do j--;
    while (a[j] > x);
    if (i < j) swap(a[i], a[j]);
  }
  quick_sort(a, l, j);
  quick_sort(a, j + 1, r);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  quick_sort(a, 1, n);
  for (int i = 1; i <= n; i++) printf("%d ", a[i]);
  return 0;
}