#include <cstdlib>
#include <conio.h>

#include <advanced math/advanced math.h>

using namespace adv_math;
using std::cout;
using std::endl;

int main( void ) {
  std::ifstream In("inputs/in.txt");
  std::ofstream OutDiff("outputs/diff.txt");

  /*auto Y1 = []( double X, const std::vector<double> &Y ) -> double {
      return Y[1];
    };
  auto Y2 = []( double X, const std::vector<double> &Y ) -> double {
      return 3 * exp(X) - cos(X) * cos(X) * Y[0] - (1 + sin(X) * sin(X)) * Y[1];
    };
  equations::sde Sys({Y1, Y2}, 0, {1, 1});*/
  auto Y1 = []( double X, const std::vector<double> &Y ) -> double {
      return sqrt(1 - Y[0] * Y[0]);
    };
  equations::sde Sys({Y1}, 0, {0});
  solvers::sde_runge_kutta<2> SolverRK(Sys, 0.01);
  solvers::sde_predictor_corrector<solvers::sde_runge_kutta<1>, 4> SolverPC1(Sys, 0.01);
  solvers::sde_predictor_corrector<solvers::sde_runge_kutta<2>, 4> SolverPC2(Sys, 0.01);
  solvers::sde *Solvers[] = { &SolverRK, &SolverPC1, &SolverPC2 };

  int Anchors, Repeats;
  In >> Anchors >> Repeats;
  int N = Anchors;
  double H = 1. / N;

  OutDiff << Anchors << " " << Repeats << endl;
  for (const auto &Solver : Solvers) {
    N = Anchors;
    H = 1. / N;
    //for (int RepN = 1; RepN <= Repeats; RepN++) {
    auto Pts = Solver->values(2, N);
    for (int Anch = 1; Anch <= Anchors; Anch++) {
      double X = 2. * Anch / Anchors;
      OutDiff << abs(Pts[Anch * N / Anchors][0] - sin(X)) << " ";
    }
    //for (const auto &Pt : Pts)
    //  OutDiff << Pt << "; ";
    OutDiff << endl;
    N *= 2;
    H = 1. / N;
    //}
  }

  //_getch();
  return 0;
}
