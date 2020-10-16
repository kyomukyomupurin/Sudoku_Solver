#pragma once

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
      char str[N + 1];
      scanf("%s", str);
      for (int j = 0; j < N; ++j) {
        board[i][j] = (isdigit(str[j]) ? str[j] - '0' : 0);
      }
    }
    Init();
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
      putchar('\n');
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
  bool IsPlaceable_Row(int id, int number) {
    for (int i = 0; i < N; ++i) {
      if (board[id][i] == number) return false;
    }
    return true;
  }

  bool IsPlaceable_Column(int id, int number) {
    for (int i = 0; i < N; ++i) {
      if (board[i][id] == number) return false;
    }
    return true;
  }

  bool IsPlaceable_Block(int id_row, int id_column, int number) {
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
      if (!IsPlaceable_Row(empty_row, number)) can = false;
      if (!IsPlaceable_Column(empty_column, number)) can = false;
      if (!IsPlaceable_Block(empty_row, empty_column, number)) can = false;
      if (can) res.emplace_back(number);
    }
    return res;
  }

  bool Decidable(int empty_row, int empty_column) {
    return board[empty_row][empty_column] == 0 &&
           GetPlaceableNumbers(empty_row, empty_column).size() == 1;
  }

  void Init() {
    bool flag = true;
    while (flag) {
      flag = false;
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (Decidable(i, j)) {
            board[i][j] = GetPlaceableNumbers(i, j)[0];
            flag = true;
          }
        }
      }
    }
  }
};