#include "util.hpp"

// (row, col)
using Coordinate = std::pair<int, int>;

int Search(const std::vector<std::string> &input,
           Coordinate starting_pos,
           int num_rows,
           int num_cols,
           bool is_part2)
{
  std::stack<Coordinate> to_visit{};
  to_visit.push(starting_pos);

  std::set<Coordinate> visited_peaks{};
  int total_visited_count{0};

  while (!to_visit.empty()) {
    auto curr_pos{to_visit.top()};
    to_visit.pop();

    const auto row{curr_pos.first}, col{curr_pos.second};

    if (input[row][col] == '9') {
      if (is_part2) {
        total_visited_count++;
      } else {
        visited_peaks.insert(curr_pos);
      }
      continue;
    }

    // Height samples are between 0 to 9, so we can simply subtract both ASCII characters
    // and still obtain the actual difference

    // Bottom
    if (row + 1 < num_rows && input[row + 1][col] - input[row][col] == 1) {
      to_visit.push({row + 1, col});
    }

    // Top
    if (row - 1 >= 0 && input[row - 1][col] - input[row][col] == 1) {
      to_visit.push({row - 1, col});
    }

    // Right
    if (col + 1 < num_cols && input[row][col + 1] - input[row][col] == 1) {
      to_visit.push({row, col + 1});
    }

    // Left
    if (col - 1 >= 0 && input[row][col - 1] - input[row][col] == 1) {
      to_visit.push({row, col - 1});
    }
  }

  return is_part2 ? total_visited_count : visited_peaks.size();
}

int Solve(const std::vector<std::string> &input, bool is_part2)
{
  const auto num_rows{input.size()};
  const auto num_cols{input[0].size()};

  int sum{0};

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (input[i][j] == '0') {
        sum += Search(input, {i, j}, num_rows, num_cols, is_part2);
      }
    }
  }

  return sum;
}

int Part1(const std::vector<std::string> &input) {
  return Solve(input, false);
}

int Part2(const std::vector<std::string> &input) {
  return Solve(input, true);
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
