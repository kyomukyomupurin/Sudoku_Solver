#include "solver.h"
#include "timer.h"

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