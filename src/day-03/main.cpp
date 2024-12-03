#include "util.hpp"

int Part1(const std::vector<std::string> &input)
{
  const std::regex regex{R"(mul\([0-9]{1,4},[0-9]{1,4}\))"};
  int sum{0};

  for (const auto &line : input) {
    for (auto it = std::sregex_iterator{line.begin(), line.end(), regex};
         it != std::sregex_iterator{};
         it++) {
      int a{0}, b{0};
      std::sscanf(it->str().data(), "mul(%d,%d)", &a, &b);
      sum += a * b;
    }
  }
  return sum;
}

int Part2(const std::vector<std::string> &input) {
  const std::regex regex{R"((mul\([0-9]{1,4},[0-9]{1,4}\))|(do\(\))|(don't\(\)))"};
  bool mul_enabled{true};
  int sum{0};

  for (const auto &line : input) {
    for (auto it = std::sregex_iterator{line.begin(), line.end(), regex};
         it != std::sregex_iterator{};
         it++) {
      auto str{it->str()};
      if (str == "don't()") {
        mul_enabled = false;
      } else if (str == "do()") {
        mul_enabled = true;
      } else {
        if (mul_enabled) {
          int a{0}, b{0};
          std::sscanf(str.data(), "mul(%d,%d)", &a, &b);
          sum += a * b;
        }
      }
    }
  }
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
 
  std::vector<std::string> input = util::ReadInput("input"); 

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
