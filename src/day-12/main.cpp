#include "util.hpp"

using Coordinate = std::pair<int, int>;

int Search(const std::vector<std::string> &input,
           std::set<Coordinate> &visited,
           Coordinate pos,
           int num_rows,
           int num_cols)
{
  auto plant{input[pos.first][pos.second]};

  std::stack<Coordinate> to_visit{};
  to_visit.push(pos);

  int area{0}, perimeter{0};

  while (!to_visit.empty()) {
    auto curr{to_visit.top()};
    to_visit.pop();
    auto row{curr.first}, col{curr.second};

    if (visited.contains(curr)) {
      continue;
    }

    visited.insert(curr);
    area++;

    // Bottom
    if (row + 1 < num_rows && input[row + 1][col] == plant) {
      to_visit.push({row + 1, col});
    } else {
      perimeter++;
    }
    // Top
    if (row - 1 >= 0 && input[row - 1][col] == plant) {
      to_visit.push({row - 1, col});
    } else {
      perimeter++;
    }
    // Right
    if (col + 1 < num_cols && input[row][col + 1] == plant) {
      to_visit.push({row, col + 1});
    } else {
      perimeter++;
    }
    // Left
    if (col - 1 >= 0 && input[row][col - 1] == plant) {
      to_visit.push({row, col - 1});
    } else {
      perimeter++;
    }
  }
  return area * perimeter;
}

int Part1(const std::vector<std::string> &input)
{
  const auto num_rows{input.size()};
  const auto num_cols{input[0].size()};

  std::set<Coordinate> visited;

  int sum{0};
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      Coordinate pos{i, j};
      if (!visited.contains(pos)) {
        sum += Search(input, visited, pos, num_rows, num_cols);
      }
    }
  }
  return sum;
}

int Part2(const std::vector<std::string> &input) {
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("example-input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
