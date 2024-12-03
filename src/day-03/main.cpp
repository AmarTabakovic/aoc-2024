#include "util.hpp"

int Part1(const std::vector<std::string> &input)
{
  int sum = 0;

  std::regex regex{R"(mul\([0-9]{1,4},[0-9]{1,4}\))"};

  for (const auto &line : input) {
    for (auto it = std::sregex_iterator(line.begin(), line.end(), regex);
         it != std::sregex_iterator{};
         it++) {
      int a{0}, b{0};
      std::sscanf((*it).str().data(), "mul(%d,%d)", &a, &b);
      sum += a * b;
    }
  }
  return sum;
}

int Part2(const std::vector<std::string> &input) {
  int sum = 0;

  std::regex regex{R"((mul\([0-9]{1,4},[0-9]{1,4}\))|(do\(\))|(don't\(\)))"};
  bool mul_enabled{true};

  for (const auto &line : input) {
    for (auto it = std::sregex_iterator(line.begin(), line.end(), regex);
         it != std::sregex_iterator{};
         it++) {
      auto s = (*it).str();
      if (s == "don't()") {
        mul_enabled = false;
      } else if (s == "do()") {
        mul_enabled = true;
      } else {
        if (mul_enabled) {
          int a{0}, b{0};
          std::sscanf(s.data(), "mul(%d,%d)", &a, &b);
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
