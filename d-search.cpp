#include <cstring>
#include <iostream>
#include <stack>

using namespace std;

stack<int> sta;

const int N = 105;
const int M = 1005;

int n, m;
int h[N], e[M], ne[M], idx;
bool st[N];

void add(int u, int v) { e[idx] = v, ne[idx] = h[u], h[u] = idx++; }

void d_search(int start) {
  sta.push(start);
  st[start] = true;
  while (!sta.empty()) {
    int top = sta.top();
    cout << top << " ";
    sta.pop();
    for (int i = h[top]; ~i; i = ne[i]) {
      int j = e[i];
      if (!st[j]) {
        sta.push(j);
        st[j] = true;
      }
    }
  }
}

int main() {
  #ifdef LOCAL
    freopen("io/input.txt", "r", stdin);
    freopen("io/output.txt", "w", stdout);
  #endif
  cin >> n >> m;
  memset(h, -1, sizeof h);
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    add(x, y);
    add(y, x);
  }
  d_search(1);
}