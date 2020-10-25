#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include <stack>

class WonderfulSudokuSolver {
  static constexpr size_t SqrtN = 4;
  static constexpr size_t N = SqrtN * SqrtN;
  using Board = std::array<std::array<int, N>, N>;
  Board board;
  std::vector<Board> answers;
  std::pair<int, int> NotFound = {-1, -1};

 public:
  WonderfulSudokuSolver() = default;

  void Input() {
    // for (int i = 0; i < N; ++i) {
    //   char str[N + 1];
    //   scanf("%s", str);
    //   for (int j = 0; j < N; ++j) {
    //     board[i][j] = (isdigit(str[j]) ? str[j] - '0' : 0);
    //   }
    // }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        scanf("%d", &board[i][j]);
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
    auto [id_row, id_col] = FindEmpty();
    std::vector<int> candidates = GetPlaceableNumbers(id_row, id_col);
    if (candidates.empty()) return;
    for (int number : candidates) {
      std::stack<std::pair<int, int>> st;
      Set(id_row, id_col, number);
      st.emplace(id_row, id_col);

      // Heuristic1
      bool flag = true;
      while (flag) {
        flag = false;
        for (int row = 0; row < N; ++row) {
          for (int col = 0; col < N; ++col) {
            if (Decidable(row, col)) {
              Set(row, col, GetPlaceableNumbers(row, col)[0]);
              st.emplace(row, col);
              flag = true;
            }
          }
        }
      }

      // Heuristic2
      flag = true;
      while (flag) {
        flag = false;
        for (int row = 0; row < N; ++row) {
          for (int col = 0; col < N; ++col) {
            if (board[row][col] == 0) {
              std::vector<int> candidates = GetPlaceableNumbers(row, col);
              for (int number : candidates) {
                if (CheckRow(row, col, number) || CheckColumn(row, col, number) ||
                    CheckBlock(row, col, number)) {
                  flag = true;
                  Set(row, col, number);
                  st.emplace(row, col);
                  continue;
                }
              }
            }
          }
        }
      }

      Solve();
      while (!st.empty()) {
        auto [row, col] = st.top();
        st.pop();
        Reset(row, col);
      }
    }
  }

  void Output() {
    int id = 1;
    for (Board& answer : answers) {
      putchar('\n');
      printf("Answer %d:\n", id++);
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          printf("%2d ", answer[i][j]);
        }
        putchar('\n');
      }
    }
  }

 private:
  bool IsEmpty(int id_row, int id_col) { return board[id_row][id_col] == 0; }

  void Set(int id_row, int id_col, int number) {
    board[id_row][id_col] = number;
  }

  void Reset(int id_row, int id_col) {
    Set(id_row, id_col, 0);
  }

  bool IsPlaceable_Row(int id_row, int number) {
    for (int col = 0; col < N; ++col) {
      if (board[id_row][col] == number) return false;
    }
    return true;
  }

  bool IsPlaceable_Column(int id_col, int number) {
    for (int row = 0; row < N; ++row) {
      if (board[row][id_col] == number) return false;
    }
    return true;
  }

  bool IsPlaceable_Block(int id_row, int id_col, int number) {
    int center_row = id_row / SqrtN * SqrtN;
    int center_col = id_col / SqrtN * SqrtN;
    for (int row = center_row; row < center_row + SqrtN; ++row) {
      for (int col = center_col; col < center_col + SqrtN; ++col) {
        if (board[row][col] == number) return false;
      }
    }
    return true;
  }

  std::pair<int, int> FindEmpty() {
    for (int row = 0; row < N; ++row) {
      for (int col = 0; col < N; ++col) {
        if (IsEmpty(row, col)) return {row, col};
      }
    }
    return {-1, -1};
  }

  std::vector<int> GetPlaceableNumbers(int id_row, int id_col) {
    std::vector<int> res;
    for (int number = 1; number <= N; ++number) {
      bool can = true;
      if (!IsPlaceable_Row(id_row, number)) can = false;
      if (!IsPlaceable_Column(id_col, number)) can = false;
      if (!IsPlaceable_Block(id_row, id_col, number)) can = false;
      if (can) res.emplace_back(number);
    }
    return res;
  }

  bool Decidable(int id_row, int id_col) {
    return IsEmpty(id_row, id_col) &&
           GetPlaceableNumbers(id_row, id_col).size() == 1;
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

  bool CheckRow(int id_row, int id_col, int number) {
    for (int col = 0; col < N; ++col) {
      if (col == id_col) continue;
      if (IsEmpty(id_row, col) && IsPlaceable_Column(col, number)) return false;
    }
    return true;
  }

  bool CheckColumn(int id_row, int id_col, int number) {
    for (int row = 0; row < N; ++row) {
      if (row == id_row) continue;
      if (IsEmpty(row, id_col) && IsPlaceable_Row(row, number)) return false;
    }
    return true;
  }

  bool CheckBlock(int id_row, int id_col, int number) {
    int center_row = id_row / SqrtN * SqrtN;
    int center_col = id_col / SqrtN * SqrtN;
    for (int row = center_row; row < center_row + SqrtN; ++row) {
      for (int col = center_col; col < center_col + SqrtN; ++col) {
        if (row == id_row && col == id_col) continue;
        if (IsEmpty(row, col)) {
          if (IsPlaceable_Row(id_row, number) &&
              IsPlaceable_Column(id_col, number)) {
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
      for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
          if (board[row][col] == 0) {
            std::vector<int> candidates = GetPlaceableNumbers(row, col);
            for (int number : candidates) {
              if (CheckRow(row, col, number) || CheckColumn(row, col, number) ||
                  CheckBlock(row, col, number)) {
                flag = true;
                Set(row, col, number);
                continue;
              }
            }
          }
        }
      }
    }
  }
};