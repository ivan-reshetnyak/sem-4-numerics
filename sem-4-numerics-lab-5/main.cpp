#include <cstdlib>
#include <conio.h>

#include <advanced math/advanced math.h>

using namespace adv_math;
using std::cout;
using std::endl;

void stabnstuff( void ) {
  std::ofstream Out("../outputs/out.txt");

  auto Y1 = []( double X, const std::vector<double> &Y ) -> double {
      return Y[1];
    };
  auto Y2 = []( double X, const std::vector<double> &Y ) -> double {
      return 3 * exp(X) - cos(X) * cos(X) * Y[0] - (1 + sin(X) * sin(X)) * Y[1];
    };
  equations::sde Sys({Y1, Y2}, 0, {1, 1});
  solvers::sde_runge_kutta<2> Solver(Sys, 0.01);

  double Perturb = 0.05;
  double Points[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::vector<double> Errs;
  for (const auto &Pt : Points) {
    Errs.clear();
    for (int i = 0; i < 1000; i++) {
      auto SolR = Solver(Pt);

      equations::sde SysW({Y1, Y2}, 0, {1 + (rand() / (double)RAND_MAX) * Perturb,
                                       1 + (rand() / (double)RAND_MAX) * Perturb});
      auto SolW = solvers::sde_runge_kutta<2>(SysW, 0.01)(Pt);

      Errs.push_back(pow(SolR[0] - SolW[0], 2) + pow(SolR[1] - SolW[1], 2));
    }
    double AvQ = 0;
    for (const auto &Err : Errs)
      AvQ += Err;
    Out << sqrt(AvQ / Errs.size()) << endl;
  }
}

void diffs( void ) {
  std::ifstream In("inputs/in.txt");
  std::ofstream OutDiff("outputs/diff.txt");

  auto Y1 = []( double X, const std::vector<double> &Y ) -> double {
      return Y[1];
    };
  auto Y2 = []( double X, const std::vector<double> &Y ) -> double {
      return 3 * exp(X) - cos(X) * cos(X) * Y[0] - (1 + sin(X) * sin(X)) * Y[1];
    };
  equations::sde Sys({Y1, Y2}, 0, {1, 1});
  solvers::sde_runge_kutta<2> Solver(Sys, 0.01);

  int Anchors, Repeats;
  In >> Anchors >> Repeats;
  int N = Anchors;
  double H = 1. / N;

  OutDiff << Anchors << " " << Repeats << endl;
  N = Anchors;
  H = 1. / N;
  for (int RepN = 1; RepN <= Repeats; RepN++) {
    auto Pts = Solver.values(2, N);
    for (int Anch = 1; Anch <= Anchors; Anch++) {
      double X = 2. * Anch / Anchors;
      OutDiff << abs(Pts[Anch * N / Anchors][0] - exp(X)) << " ";
    }
    OutDiff << endl;
    N *= 2;
    H = 1. / N;
  }
}

int main( void ) {
  diffs();

  //_getch();
  return 0;
}
