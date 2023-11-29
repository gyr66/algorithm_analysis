#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int N = 105;
const double EPS = 1e-6;

struct Item {
  int id;
  int w, p;
  bool operator<(const Item& b) const { return w * b.p < p * b.w; }
} a[N];

// 一个节点代表一个状态，对于第depth个物品，做出的选择是picked，做出选择后的容量和价值分别为cc和cp
struct Node {
  int cc, cp;
  int depth;
  bool picked;
  double upper_bound;
  Node* parent;

  bool operator<(const Node& b) const { return upper_bound < b.upper_bound; }
};

int n, w, ans;
double lb;
Node* ans_node;
priority_queue<Node*> que;
int map[N];

// 从第depth个物品开始选，当前容量为cw，当前价值为cp，所能得到的最大价值
double get_upper_bound(int depth, int cc) {
  double res = 0;
  int i = depth;
  while (cc >= a[i].w && i <= n) {
    cc -= a[i].w;
    res += a[i].p;
    i++;
  }
  if (i <= n) res += cc * 1.0 / a[i].w * a[i].p;
  return res;
}

// 从第depth个物品开始选，当前容量为cc，当前价值为cp，所能得到的最小价值
int get_lower_bound(int depth, int cc) {
  if (depth > n) return 0;
  int res = 0;
  int i = depth;
  while (cc >= a[i].w && i <= n) {
    cc -= a[i].w;
    res += a[i].p;
    i++;
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> w;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].w >> a[i].p;
    a[i].id = i;
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= N; i++) map[i] = a[i].id;
  lb = get_lower_bound(1, w) - EPS;
  que.push(new Node{w, 0, 0, false, get_upper_bound(1, w), nullptr});
  while (!que.empty()) {
    Node* t = que.top();
    que.pop();
    if (t->upper_bound <= lb) continue;
    if (t->depth == n) {
      lb = t->cp;
      if (ans < t->cp) {
        ans = t->cp;
        ans_node = t;
      }
      continue;
    }
    // 约束条件：判断能否选择第depth个物品
    if (t->cc >= a[t->depth + 1].w) {
      que.push(new Node{t->cc - a[t->depth + 1].w, t->cp + a[t->depth + 1].p,
                        t->depth + 1, true, t->upper_bound, t});
    }
    double _upper_bound = t->cp + get_upper_bound(t->depth + 2, t->cc);
    // 限界条件
    if (_upper_bound <= lb) continue;
    int _lower_bound = t->cp + get_lower_bound(t->depth + 2, t->cc);
    lb = max(lb, _lower_bound * 1.0 - EPS);
    que.push(new Node{t->cc, t->cp, t->depth + 1, false, _upper_bound, t});
  }
  vector<int> v;
  cout << ans << endl;
  while (ans_node) {
    if (ans_node->picked) {
      v.push_back(map[ans_node->depth]);
    }
    ans_node = ans_node->parent;
  }
  sort(v.begin(), v.end());
  for (auto i : v) cout << i << " ";
  return 0;
}