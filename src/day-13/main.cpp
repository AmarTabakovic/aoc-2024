#include "util.hpp"

using NumType = long long;

constexpr NumType kOffset{10000000000000};

NumType Solve(const std::vector<std::string> &input, bool is_part2)
{
  NumType sum{0};
  // Solve linear system of equations
  // x_1 * a + x_2 * b = x
  // y_1 * a + y_2 * b = y
  //
  //       (x * y_2 - x_2 * y)
  // a = -----------------------
  //     (x_1 * y_2 - y_1 * x_2)
  //
  //       (y * x_1 - y_1 * x)
  // b = -----------------------
  //     (x_1 * y_2 - y_1 * x_2)

  for (auto it = input.begin(); it <= input.end(); it++) {
    NumType x_1{}, x_2{}, y_1{}, y_2{}, x{}, y{};

    std::sscanf(it->c_str(), "Button A: X+%lld, Y+%lld", &x_1, &y_1);
    it++;
    std::sscanf(it->c_str(), "Button B: X+%lld, Y+%lld", &x_2, &y_2);
    it++;
    std::sscanf(it->c_str(), "Prize: X=%lld, Y=%lld", &x, &y);
    it++;

    const auto denominator{x_1 * y_2 - y_1 * x_2};

    if (denominator == 0) {
      continue;
    }

    if (is_part2) {
      x += kOffset;
      y += kOffset;
    }

    const auto a = (x * y_2 - x_2 * y) / denominator;
    const auto b = (y * x_1 - y_1 * x) / denominator;

    // Manually verify whether valid
    if (x_1 * a + x_2 * b == x && y_1 * a + y_2 * b == y) {
      sum += a * 3 + b;
    }
  }
  return sum;
}

NumType Part1(const std::vector<std::string> &input)
{
  return Solve(input, false);
}

NumType Part2(const std::vector<std::string> &input)
{
  return Solve(input, true);
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
