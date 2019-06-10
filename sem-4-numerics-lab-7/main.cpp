#include <iostream>

#include <advanced math/advanced math.h>

using namespace adv_math;
using std::endl;

int main( void ) {
  std::ifstream In("inputs/in.txt");
  std::ofstream OutDiffs("outputs/diffs.txt");
  std::ofstream OutStab("outputs/stab.txt");

  equations::boundary Eq(new auto(func::constant(1) + func::sin<func::x>(func::x()) * func::sin<func::x>(func::x())),
    new auto(func::cos<func::x>(func::x()) * func::cos<func::x>(func::x())),
    new auto(func::constant(3) * func::exp<func::x>(func::x())),
    {{0, 1}, {1, e}});
  solvers::finite_difference Solver(Eq);

  int Anchors, Repeats;
  In >> Anchors >> Repeats;
  int N = Anchors + 1;
  double H = 1. / N;

  OutDiffs << Anchors << " " << Repeats << endl;
  for (int RepN = 1; RepN <= Repeats; RepN++) {
    auto Pts = Solver.Solve(N);
    for (int Anch = 1; Anch <= Anchors; Anch++)
      OutDiffs << Pts[Anch * RepN] - exp(Anch * RepN * H) << " ";
    OutDiffs << endl;
    N *= 2;
    H = 1. / N;
  }

  N = Anchors + 1;
  H = 1. / N;
  double Delta = 0.01;
  std::vector<double> Devs(Anchors, 0);
  for (int RepN = 1; RepN <= 1000; RepN++) {
    double
      Y0 = 1 + (double)rand() / RAND_MAX * Delta,
      YN = e + (double)rand() / RAND_MAX * Delta;
    equations::boundary Eq(new auto(func::constant(1) + func::sin<func::x>(func::x()) * func::sin<func::x>(func::x())),
      new auto(func::cos<func::x>(func::x()) * func::cos<func::x>(func::x())),
      new auto(func::constant(3) * func::exp<func::x>(func::x())),
      {{0, Y0}, {1, YN}});
    solvers::finite_difference Solver(Eq);

    auto Pts = Solver.Solve(N);
    for (int Anch = 1; Anch <= Anchors; Anch++)
      Devs[Anch - 1] += pow(Pts[Anch] - exp(Anch * H), 2);
  }
  OutStab << Anchors << endl;
  for (auto &Dev : Devs) {
    Dev = sqrt(Dev * 0.001);
    OutStab << Dev << " ";
  }

  return 0;
}
