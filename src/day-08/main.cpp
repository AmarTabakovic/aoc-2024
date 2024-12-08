#include "util.hpp"

// (row, col)
using Coordinate = std::pair<int, int>;

bool InBounds(Coordinate coordinate, int num_rows, int num_cols)
{
  return coordinate.first < num_rows && coordinate.first >= 0 && coordinate.second < num_cols
         && coordinate.second >= 0;
}

int Solve(const std::vector<std::string> &input, bool is_part2)
{
  std::set<Coordinate> antinodes{};
  std::map<char, std::vector<Coordinate>> coord_map;
  auto num_rows{input.size()};
  auto num_cols{input[0].size()};

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (input[i][j] != '.') {
        coord_map[input[i][j]].push_back({i, j});
      }
    }
  }

  for (auto &[_, antennas] : coord_map) {
    for (int i = 0; i < antennas.size(); i++) {
      for (int j = i + 1; j < antennas.size(); j++) {
        const auto &antenna1{antennas[i]};
        const auto &antenna2{antennas[j]};

        if (antenna1 == antenna2) {
          continue;
        }

        int dist_row = antenna2.first - antenna1.first;
        int dist_col = antenna2.second - antenna1.second;

        if (is_part2) {
          // Traverse both sides
          for (int i = -1; i <= 1; i += 2) {
            auto curr_antinode = Coordinate{antenna1.first, antenna1.second};
            while (InBounds(curr_antinode, num_rows, num_cols)) {
              antinodes.insert(curr_antinode);
              curr_antinode.first += i * dist_row;
              curr_antinode.second += i * dist_col;
            }
          }
        } else {
          auto antinode1 = Coordinate{antenna2.first + dist_row, antenna2.second + dist_col};
          auto antinode2 = Coordinate{antenna1.first - dist_row, antenna1.second - dist_col};

          if (InBounds(antinode1, num_rows, num_cols)) {
            antinodes.insert(antinode1);
          }
          if (InBounds(antinode2, num_rows, num_cols)) {
            antinodes.insert(antinode2);
          }
        }
      }
    }
  }

  return antinodes.size();
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
