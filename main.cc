#include <algorithm>
#include <iostream>
#include <vector>

class SudokuSolver {
  static constexpr int N = 9;
  std::vector<std::vector<int>> board;

 public:
  SudokuSolver() {
    board.assign(N, std::vector<int>(N));
  }

  void Input() {
    for (int i = 0; i < N; ++i) {
      char str[10]; scanf("%s", str);
      for (int j = 0; j < N; ++j) {
        board[i][j] = (isdigit(str[j]) ? str[j] - '0' : 0);
      }
    }
  }

  void Solve() {}

  void Output() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        printf("%2d ", board[i][j]);
      }
      putchar('\n');
    }
  }

 private:
  bool Placeable_Row(int id, int number) {}

  bool Placeable_Column(int id, int number) {}

  bool Placeable_Block(int id, int number) {}

};

int main() {
  SudokuSolver solver;
  solver.Input();
  solver.Solve();
  solver.Output();
}