#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 105, K = 105;

struct Task {
  int id;
  int time;

  bool operator<(const Task& t) const { return time > t.time; }
} a[N];

int n, k;
int ans = 1e9;
vector<int> path;
int map[N];

struct Node {
  int cur;     // 已经分配了cur个任务，现在要分配第cur+1个任务
  int choice;  // 第cur个任务分配到第choice台机器
  int estimate;  // 估计在当前状态下完成所有任务需要的时间
  vector<int> machine;  // 完成之前分配的任务，每台机器的完成时间
  Node* parent;  // 搜索树上父节点指针，用于回溯生成方案
};

struct CompareEst {
  bool operator()(Node* const& p1, Node* const& p2) {
    return p1->estimate > p2->estimate;
  }
};

priority_queue<Node*, vector<Node*>, CompareEst> que;

// 已经分配了cur个任务，各个机器负载情况为machine，使用贪心策略估计完成所有任务的时间
int estimate(vector<int> machine, int cur) {
  int res = 0;
  for (int i = cur + 1; i <= n; i++) {
    int min_time = machine.front();
    int min_index = 0;
    for (int j = 1; j < k; j++) {
      if (machine[j] < min_time) {
        min_time = machine[j];
        min_index = j;
      }
    }
    machine[min_index] += a[i].time;
  }
  res = *max_element(machine.begin(), machine.end());
  return res;
}

int inline get_time(const vector<int>* machine) {
  return *max_element(machine->begin(), machine->end());
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].time;
    a[i].id = i;
  }
  sort(a + 1, a + n + 1);  // 从大到小排序
  for (int i = 1; i <= n; i++) {
    map[i] = a[i].id;
  }
  que.push(new Node{0, -1, 0, vector<int>(k, 0), nullptr});
  while (!que.empty()) {
    auto t = que.top();
    que.pop();
    // 限界
    if (get_time(&t->machine) >= ans) continue;
    if (t->cur == n) {
      int time = get_time(&t->machine);
      if (time < ans) {
        ans = time;
        path.clear();
        Node* p = t;
        while (p->cur) {
          path.push_back(p->choice + 1);
          p = p->parent;
        }
      }
    }
    for (int i = 0; i < k; i++) {
      // 将第cur+1个任务分配给第i台机器
      vector<int> machine = t->machine;
      machine[i] += a[t->cur + 1].time;
      // 限界
      if (get_time(&machine) >= ans) continue;
      Node* next =
          new Node{t->cur + 1, i, estimate(machine, t->cur + 1), machine, t};
      que.push(next);
    }
  }
  cout << ans << endl;
  vector<int> output(n + 1);
  for (int i = 1; i <= n; i++) {
    output[map[i]] = path.back();
    path.pop_back();
  }
  for (int i = 1; i <= n; i++) {
    cout << output[i] << " ";
  }
  return 0;
}