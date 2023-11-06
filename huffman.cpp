#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int N = 105;

int n;
struct Node {
  char ch;
  int freq;
  Node* left;
  Node* right;
  string code;
};

Node* a[N];
auto compare = [](const Node* a, const Node* b) { return a->freq > b->freq; };
priority_queue<Node*, vector<Node*>, decltype(compare)> que(compare);

void dfs(Node* node) {
  if (node->left == nullptr && node->right == nullptr) {
    return;
  }
  if (node->left != nullptr) {
    node->left->code = node->code + "0";
    dfs(node->left);
  }
  if (node->right != nullptr) {
    node->right->code = node->code + "1";
    dfs(node->right);
  }
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) {
    char ch;
    int freq;
    cin >> ch >> freq;
    a[i] = new Node{ch, freq, nullptr, nullptr, ""};
    que.push(a[i]);
  }
  while (que.size() > 1) {
    Node* x = que.top();
    que.pop();
    Node* y = que.top();
    que.pop();
    Node* new_node = new Node{'^', x->freq + y->freq, x, y, ""};
    que.push(new_node);
  }
  Node* root = que.top();
  dfs(root);
  for (int i = 1; i <= n; i++) {
    cout << a[i]->ch << " " << a[i]->freq << " " << a[i]->code << endl;
  }
}