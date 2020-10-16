#include "solver.h"

int main() {
  WonderfulSudokuSolver solver;
  solver.Input();
  solver.Solve();
  solver.Output();

  return 0;
}