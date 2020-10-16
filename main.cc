#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

class WonderfulSudokuSolver {
  static constexpr size_t N = 9;
  using Board = std::array<std::array<int, N>, N>;
  std::pair<int, int> NotFound = {-1, -1};
  Board board;

 public:
  WonderfulSudokuSolver() = default;

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
    auto [empty_row, empty_column] = FindEmpty();
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
      if (board[id][i] == number) return false;
    }
    return true;
  }

  bool Placeable_Column(int id, int number) {
    for (int i = 0; i < N; ++i) {
      if (board[i][id] == number) return false;
    }
    return true;
  }

  bool Placeable_Block(int id_row, int id_column, int number) {
    // TO DO
  }

  std::pair<int, int> FindEmpty() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (board[i][j] == 0) return {i, j};
      }
    }
    return {-1, -1};
  }

  std::vector<int> GetPlaceableNumbers(int empty_row, int empty_column) {
    std::vector<int> res;
    for (int number = 1; number <= N; ++number) {
      bool can = true;
      if (!Placeable_Row(empty_row, number)) can = false;
      if (!Placeable_Column(empty_column, number)) can = false;
      if (!Placeable_Block(empty_row, empty_column, number)) can = false;
      if (can) res.emplace_back(number);
    }
    return res;
  }
};

int main() {
  WonderfulSudokuSolver solver;
  solver.Input();
  // solver.Solve();
  solver.Output();
}