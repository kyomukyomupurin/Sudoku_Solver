#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

class SudokuSolver {
  static constexpr size_t N = 9;
  using Board = std::array<std::array<int, N>, N>;
  std::pair<int, int> NotFound = {-1, -1};
  Board board;

 public:
  SudokuSolver() = default;

  void Input() {
    for (int i = 0; i < N; ++i) {
      char str[10];
      scanf("%s", str);
      for (int j = 0; j < N; ++j) {
        board[i][j] = (isdigit(str[j]) ? str[j] - '0' : 0);
      }
    }
  }

  void Solve() {
    if (FindEmpty() == NotFound) {
      return;
    }
    auto [empty_column, empty_row] = FindEmpty();
  }

  void Output() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        printf("%2d ", board[i][j]);
      }
      putchar('\n');
    }
  }

 private:
  bool Placeable_Row(int id, int number) {
    for (int i = 0; i < N; ++i) {
      if (board[id][i] == number) {
        return false;
      }
    }
    return true;
  }

  bool Placeable_Column(int id, int number) {
    for (int i = 0; i < N; ++i) {
      if (board[i][id] == number) {
        return false;
      }
    }
    return true;
  }

  bool Placeable_Block(int id, int number) {}

  std::pair<int, int> FindEmpty() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (board[i][j] == 0) {
          return {i, j};
        }
      }
    }
    return {-1, -1};
  }
};

int main() {
  SudokuSolver solver;
  solver.Input();
  solver.Solve();
  solver.Output();
}