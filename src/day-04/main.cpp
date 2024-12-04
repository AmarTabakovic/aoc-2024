#include "util.hpp"

// (row, col)
using Coordinate = std::pair<int, int>;

int SearchPart1(const std::vector<std::string> &grid,
                const Coordinate &coord,
                int num_rows,
                int num_cols)
{
  const std::string xmas{"XMAS"};

  const auto check = [&](int dir_vert, int dir_hor) {
    bool ok{true};

    for (int i = 1; i <= 3; i++) {
      const int row{coord.first + i * dir_vert};
      const int col{coord.second + i * dir_hor};

      const auto is_inside_bounds{row < num_rows || col >= 0 || col < num_cols || col >= 0};

      if (!is_inside_bounds || grid[row][col] != xmas[i]) {
        ok = false;
        break;
      }
    }
    return ok ? 1 : 0;
  };

  const auto dirs = std::vector{0, 1, -1};
  int count{0};

  for (auto d1 : dirs) {
    for (auto d2 : dirs) {
      count += check(d1, d2);
    }
  }

  return count;
}

int SearchPart2(const std::vector<std::string> &grid,
                const Coordinate &coord,
                int num_rows,
                int num_cols)
{
  int count{0};

  const auto row{coord.first}, col{coord.second};
  const auto is_inside_bounds{row + 1 < num_rows || col - 1 >= 0 || col + 1 < num_cols
                              || col - 1 >= 0};

  if (is_inside_bounds) {
    int mas_count{0};

    if (grid[row - 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'S') {
      mas_count++;
    }
    if (grid[row - 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'M') {
      mas_count++;
    }
    if (grid[row - 1][col + 1] == 'M' && grid[row + 1][col - 1] == 'S') {
      mas_count++;
    }
    if (grid[row - 1][col + 1] == 'S' && grid[row + 1][col - 1] == 'M') {
      mas_count++;
    }

    // Prevent incomplete MASes from being counted
    if (mas_count == 2) {
      count++;
    }
  }

  return count;
}

int Init(const std::vector<std::string> &input, bool is_part_2)
{
  int count{0};

  // Assumption: all rows have the same length
  const int num_rows = input.size();
  const int num_cols = input.at(0).size();

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (is_part_2) {
        if (input[i][j] == 'A') {
          count += SearchPart2(input, Coordinate{i, j}, num_rows, num_cols);
        }
      } else {
        if (input[i][j] == 'X') {
          count += SearchPart1(input, Coordinate{i, j}, num_rows, num_cols);
        }
      }
    }
  }
  return count;
}

int Part1(const std::vector<std::string> &input)
{
  return Init(input, false);
}

int Part2(const std::vector<std::string> &input) {
  return Init(input, true);
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
