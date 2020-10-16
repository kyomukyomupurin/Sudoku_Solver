#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

class WonderfulSudokuSolver {
  static constexpr size_t N = 9;
  using Board = std::array<std::array<int, N>, N>;
  std::pair<int, int> NotFound = {-1, -1};
  std::vector<Board> answers;
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
      answers.push_back(board);
      return;
    }
    auto [empty_row, empty_column] = FindEmpty();
    std::vector<int> candidates = GetPlaceableNumbers(empty_row, empty_column);
    if (candidates.empty()) return;
    for (int number : candidates) {
      board[empty_row][empty_column] = number;
      Solve();
      board[empty_row][empty_column] = 0;
    }
  }

  void Output() {
    int id = 1;
    for (Board& answer : answers) {
      printf("Answer %d:\n", id++);
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          printf("%d", answer[i][j]);
        }
        putchar('\n');
      }
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
    int center_row = id_row / 3 * 3 + 1;
    int center_column = id_column / 3 * 3 + 1;
    for (int i = center_row - 1; i <= center_row + 1; ++i) {
      for (int j = center_column - 1; j <= center_column + 1; ++j) {
        if (board[i][j] == number) return false;
      }
    }
    return true;
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

class Timer {
 public:
  // (second)
  double get_elapsed_time() {
    return static_cast<double>(get_cycle() - start_) /
           static_cast<double>(clock_frequency_);
  }

  void start() { start_ = get_cycle(); }

 private:
  int64_t start_;
  static constexpr int64_t clock_frequency_ = 1800000000; // Local
  //static constexpr int64_t clock_frequency_ = 3000000000; // AtCoder
  //static constexpr int64_t clock_frequency_ = 3600000000; // Codeforces
  //static constexpr int64_t clock_frequency_ = 2300000000; // yukicoder

  int64_t get_cycle() {
    uint32_t low, high;
    __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
    return (static_cast<int64_t>(low)) | (static_cast<int64_t>(high) << 32);
  }
};


int main() {
  Timer time;
  time.start();
  WonderfulSudokuSolver solver;
  solver.Input();
  solver.Solve();
  solver.Output();

  printf("Execution time : %.15lf\n", time.get_elapsed_time());

  return 0;
}