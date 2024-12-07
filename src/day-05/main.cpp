#include "util.hpp"

using RuleMap = std::unordered_map<int, std::unordered_set<int>>;

std::vector<int> ParseNamesForUpdate(std::string update_line)
{
  std::vector<int> updates;

  std::replace(update_line.begin(), update_line.end(), ',', ' ');
  std::istringstream iss{update_line};

  int i;
  while (iss >> i) {
    updates.push_back(i);
  }

  return updates;
}

int Solve(const std::vector<std::string> &input, bool is_part2)
{
  RuleMap successors{};
  int second_section_index{};
  for (int i = 0; i < input.size(); i++) {
    auto line{input[i]};

    if (line == "") {
      second_section_index = i + 1;
      break;
    }

    int a{}, b{};
    std::sscanf(line.data(), "%d|%d", &a, &b);
    successors[a].insert(b);
  }

  int sum{0};

  for (int i = second_section_index; i < input.size(); i++) {
    auto update_names{ParseNamesForUpdate(input[i])};
    auto ok{true};
    for (auto it{update_names.begin()}; it != update_names.end() - 1; it++) {
      if (!successors[*it].contains(*(it + 1))) {
        ok = false;
        break;
      }
    }

    if (is_part2) {
      if (!ok) {
        std::sort(update_names.begin(), update_names.end(), [&successors](int a, int b) {
          return successors[a].contains(b);
        });
        sum += update_names[update_names.size() / 2];
      }
    } else {
      if (ok) {
        sum += update_names[update_names.size() / 2];
      }
    }
  }

  return sum;
}

int Part1(const std::vector<std::string> &input) {
  return Solve(input, false);
}

int Part2(const std::vector<std::string> &input)
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
