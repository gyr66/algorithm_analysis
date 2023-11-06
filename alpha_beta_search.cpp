#include <cstring>
#include <iostream>

using namespace std;

const int INF = 1e9;

int board[3][3];

bool is_terminal(int board[3][3]);
int utility(int board[3][3]);
int min_value(int board[3][3], int alpha, int beta);
int max_value(int board[3][3], int alpha, int beta);

pair<int, pair<int, int>> alpha_beta_search(int board[3][3]) {
  if (is_terminal(board)) return make_pair(utility(board), make_pair(-1, -1));
  int alpha = -INF, beta = INF;
  int v = -INF;
  pair<int, int> pos = make_pair(-1, -1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!board[i][j]) {
        board[i][j] = 1;
        int t = min_value(board, alpha, beta);
        if (t > v) {
          v = t;
          alpha = max(alpha, v);
          pos = make_pair(i, j);
        }
        board[i][j] = 0;
      }
    }
  }
  return make_pair(v, pos);
}

int min_value(int board[3][3], int alpha, int beta) {
  if (is_terminal(board)) return utility(board);
  int v = INF;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!board[i][j]) {
        board[i][j] = -1;
        v = min(v, max_value(board, alpha, beta));
        board[i][j] = 0;
        if (v <= alpha) return v;
        beta = min(beta, v);
      }
    }
  }
  return v;
}

int max_value(int board[3][3], int alpha, int beta) {
  if (is_terminal(board)) return utility(board);
  int v = -INF;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!board[i][j]) {
        board[i][j] = 1;
        v = max(v, min_value(board, alpha, beta));
        board[i][j] = 0;
        if (v >= beta) return v;
        alpha = max(alpha, v);
      }
    }
  }
  return v;
}

bool is_terminal(int board[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!board[i][j]) return false;
    }
  }
  return true;
}

int utility(int board[3][3]) {
  for (int i = 0; i < 3; i++) {
    if (board[i][0] && board[i][0] == board[i][1] && board[i][0] == board[i][2])
      return board[i][0];
    if (board[0][i] && board[0][i] == board[1][i] && board[0][i] == board[2][i])
      return board[0][i];
  }
  if (board[0][0] && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    return board[0][0];
  if (board[0][2] && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    return board[0][2];
  return 0;
}

int main() {
#ifdef LOCAL
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
#endif
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> board[i][j];
    }
  }
  pair<int, pair<int, int>> res = alpha_beta_search(board);
  int v = res.first;
  if (v == 1)
    puts("win");
  else if (v == -1)
    puts("lose");
  else
    puts("tie");
  pair<int, int> pos = res.second;
  cout << pos.first << " " << pos.second << endl;
  return 0;
}