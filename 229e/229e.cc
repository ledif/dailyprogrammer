#include <iostream>
#include <cmath>
#include <Stream.h>

using namespace stream;
using namespace stream::op;

template<typename F>
std::pair<double, std::size_t> fixed(double initial, F&& f)
{
  constexpr double epsilon = 1e-12;

  double ans;
  std::size_t iters = MakeStream::iterate(initial, f)
    | peek([&](double x) { ans = x; })
    | adjacent_difference()
    | take_while([=](double x) { return std::fabs(x) > epsilon; })
    | count();

  return std::make_pair(ans, iters);
}

int main(int argc, char* argv[])
{
  auto c = fixed(1.0, [](double x) { return std::cos(x); });
  auto t = fixed(2.0, [](double x) { return x - std::tan(x); });
  auto e = fixed(1.0, [](double x) { return 1 + 1/x; });
  auto f = fixed(0.3, [](double x) { return 4*x*(1-x); });

  auto printer = [](std::string expr, double value, std::size_t iters) {
    std::cout << expr << ": converged to " << value << " in "
              << iters << " iterations " << std::endl;
  };

  printer("cos(x)", c.first, c.second);
  printer("x - tan(x)", t.first, t.second);
  printer("1 + 1/x", e.first, e.second);
  printer("4x(1-x)", f.first, f.second);

  return 0;
}
