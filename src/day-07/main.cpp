#include "util.hpp"

// Gotta pack out dem big numbers now!
using NumType = unsigned long long;

void Recurse(NumType lhs,
             NumType aux,
             const std::vector<NumType> &nums,
             int index,
             std::unordered_set<NumType> &solutions,
             bool is_part2)
{
  // Base case 1: LHS < RHS
  if (lhs < aux) {
    return;
  }
  // Base case 2: Reached end of list
  if (index == nums.size()) {
    if (lhs == aux) {
      solutions.insert(lhs);
    }
    return;
  }

  Recurse(lhs, aux + nums[index], nums, index + 1, solutions, is_part2);
  Recurse(lhs, aux * nums[index], nums, index + 1, solutions, is_part2);

  if (is_part2) {
    Recurse(lhs,
            std::stoull(std::to_string(aux) + std::to_string(nums[index])),
            nums,
            index + 1,
            solutions,
            is_part2);
  }
}

NumType Solve(const std::vector<std::string> &input, bool is_part2)
{
  // === Amusing story for whomever may be interested ===
  // I originally wrote part 1 with iteration by simply iterating from
  // i = 0 to 2^(n-1) and using each bit in i for represeting either addition
  // or multiplication.
  // You should have seen my face when I read part 2.

  NumType sum{0};
  for (const auto &line : input) {
    NumType lhs{};
    std::vector<NumType> nums{};
    std::istringstream iss{line};

    iss >> lhs;
    iss.ignore(1);

    NumType i{};
    while (iss >> i) {
      nums.push_back(i);
    }

    std::unordered_set<NumType> solutions;
    Recurse(lhs, nums[0], nums, 1, solutions, is_part2);

    for (auto solution : solutions) {
      sum += solution;
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

int main()
{
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
