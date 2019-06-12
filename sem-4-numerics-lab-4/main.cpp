#include <conio.h>

#include <advanced math/advanced math.h>

using namespace adv_math;
using std::cout;
using std::endl;

int main( void ) {
  auto Func = func::constant(1) / (func::cos<func::x>(func::x()) + func::sin<func::x>(func::x()));
  //auto Func = func::constant(1) / func::x();
  integr::chebyshev IntegrC(2);
  integr::trapezoidal IntegrT(1);

  double L = -0.245 * Pi, R = -0.24 * Pi;
  double Diff = 0, Toler = 1;
  while (Diff < Toler) {
    IntegrT.setTolerance(Toler);
    double
      ResC = IntegrC.integrate(Func, L, R),
      ResT = IntegrT.integrate(Func, L, R);
    cout << "T = " << Toler << "; " << ResC << " : " << ResT << " in " << IntegrT.getDivisions() << endl;
    Toler *= 0.9;
    Diff = abs(ResC - ResT);
  }

  _getch();
  return 0;
}
