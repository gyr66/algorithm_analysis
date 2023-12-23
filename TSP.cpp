#include <iostream>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

const int N = 25;

int n;
int** a;

int** create() {
  int** t = new int*[n + 1];
  for (int i = 0; i <= n; i++) {
    t[i] = new int[n + 1];
  }
  return t;
}

int** simplify(int** a, int& c) {
  int** res = create();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      res[i][j] = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    int min = INF;
    for (int j = 1; j <= n; j++) {
      if (res[i][j] < min) min = res[i][j];
    }
    if (min != INF) c += min;
    for (int j = 1; j <= n; j++) {
      if (res[i][j] != INF) res[i][j] -= min;
    }
  }
  for (int j = 1; j <= n; j++) {
    int min = INF;
    for (int i = 1; i <= n; i++) {
      if (res[i][j] < min) min = res[i][j];
    }
    if (min != INF) c += min;
    for (int i = 1; i <= n; i++) {
      if (res[i][j] != INF) res[i][j] -= min;
    }
  }
  return res;
}

struct Node {
  int** a;
  int c;
  int idx;
  int cnt;

  bool operator<(const Node& b) const { return c > b.c; }
};

void print(int** a) {
  cout << "----------------" << endl;
  for (int i = 1; i <= n; i++) {
    cout << "|";
    for (int j = 1; j <= n; j++) {
      cout << a[i][j] << " ";
    }
    cout << "|" << endl;
  }
  cout << "----------------" << endl;
}

priority_queue<Node> que;

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  a = create();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      if (a[i][j] == 0) a[i][j] = INF;
    }
  }
  int c = 0;
  int** b = simplify(a, c);
  que.push({b, c, 1, 1});
  while (!que.empty()) {
    Node cur = que.top();
    que.pop();
    if (cur.cnt == n) {
      cout << cur.c << endl;
      return 0;
    }
    for (int i = 2; i <= n; i++) {
      if (cur.a[cur.idx][i] != INF) {
        int c = cur.c;
        c += cur.a[cur.idx][i];
        int** t = create();
        for (int j = 1; j <= n; j++) {
          for (int k = 1; k <= n; k++) {
            if (j == cur.idx || k == i) {
              t[j][k] = INF;
            } else {
              t[j][k] = cur.a[j][k];
            }
          }
        }
        t[i][1] = INF;
        int** b = simplify(t, c);
        que.push({b, c, i, cur.cnt + 1});
      }
    }
    for (int i = 0; i <= n; i++) {
      delete[] cur.a[i];
    }
    delete[] cur.a;
  }
  return 0;
}