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
    Heuristic1();
    Heuristic2();
  }

  void Solve() {
    if (FindEmpty() == NotFound) {
      answers.push_back(board);
      return;
    }
    auto [id_row, id_column] = FindEmpty();
    std::vector<int> candidates = GetPlaceableNumbers(id_row, id_column);
    if (candidates.empty()) return;
    for (int number : candidates) {
      Set(id_row, id_column, number);
      Solve();
      Set(id_row, id_column, 0);
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
  bool IsEmpty(int id_row, int id_column) {
    return board[id_row][id_column] == 0;
  }

  void Set(int id_row, int id_column, int number) {
    board[id_row][id_column] = number;
  }

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
        if (IsEmpty(i, j)) return {i, j};
      }
    }
    return {-1, -1};
  }

  std::vector<int> GetPlaceableNumbers(int id_row, int id_column) {
    std::vector<int> res;
    for (int number = 1; number <= N; ++number) {
      bool can = true;
      if (!IsPlaceable_Row(id_row, number)) can = false;
      if (!IsPlaceable_Column(id_column, number)) can = false;
      if (!IsPlaceable_Block(id_row, id_column, number)) can = false;
      if (can) res.emplace_back(number);
    }
    return res;
  }

  bool Decidable(int id_row, int id_column) {
    return IsEmpty(id_row, id_column) &&
           GetPlaceableNumbers(id_row, id_column).size() == 1;
  }

  void Heuristic1() {
    bool flag = true;
    while (flag) {
      flag = false;
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (Decidable(i, j)) {
            Set(i, j, GetPlaceableNumbers(i, j)[0]);
            flag = true;
          }
        }
      }
    }
  }

  bool CheckRow(int id_row, int id_column, int number) {
    for (int column = 0; column < N; ++column) {
      if (column == id_column) continue;
      if (IsEmpty(id_row, column) && IsPlaceable_Column(column, number))
        return false;
    }
    return true;
  }

  bool CheckColumn(int id_row, int id_column, int number) {
    for (int row = 0; row < N; ++row) {
      if (row == id_row) continue;
      if (IsEmpty(row, id_column) && IsPlaceable_Row(row, number)) return false;
    }
    return true;
  }

  bool CheckBlock(int id_row, int id_column, int number) {
    int center_row = id_row / 3 * 3 + 1;
    int center_column = id_column / 3 * 3 + 1;
    for (int i = center_row - 1; i <= center_row + 1; ++i) {
      for (int j = center_column - 1; j <= center_column + 1; ++j) {
        if (i == id_row && j == id_column) continue;
        if (IsEmpty(i, j)) {
          if (IsPlaceable_Row(id_row, number) &&
              IsPlaceable_Column(id_column, number)) {
            return false;
          }
        }
      }
    }
    return true;
  }

  void Heuristic2() {
    bool flag = true;
    while (flag) {
      flag = false;
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (board[i][j] == 0) {
            std::vector<int> candidates = GetPlaceableNumbers(i, j);
            for (int number : candidates) {
              if (CheckRow(i, j, number) || CheckColumn(i, j, number) ||
                  CheckBlock(i, j, number)) {
                flag = true;
                Set(i, j, number);
                continue;
              }
            }
          }
        }
      }
    }
  }
};