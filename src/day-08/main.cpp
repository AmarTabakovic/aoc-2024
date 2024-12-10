#include "util.hpp"

// (row, col)
using Coordinate = std::pair<int, int>;

int Solve(const std::vector<std::string> &input, bool is_part2)
{
  std::set<Coordinate> antinodes{};
  std::map<char, std::vector<Coordinate>> antenna_coords{};
  const auto num_rows{input.size()};
  const auto num_cols{input[0].size()};

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (input[i][j] != '.') {
        antenna_coords[input[i][j]].push_back({i, j});
      }
    }
  }

  const auto in_bounds = [&num_rows, &num_cols](const Coordinate &coordinate) -> bool {
    return coordinate.first < num_rows && coordinate.first >= 0 && coordinate.second < num_cols
           && coordinate.second >= 0;
  };

  for (auto &[_, antennas] : antenna_coords) {
    for (int i = 0; i < antennas.size(); i++) {
      for (int j = i + 1; j < antennas.size(); j++) {
        const auto &antenna1{antennas[i]}, &antenna2{antennas[j]};

        const auto dist_row{antenna2.first - antenna1.first},
            dist_col{antenna2.second - antenna1.second};

        if (is_part2) {
          // Traverse both sides
          for (int k = -1; k <= 1; k += 2) {
            Coordinate curr_antinode{antenna1};
            while (in_bounds(curr_antinode)) {
              antinodes.insert(curr_antinode);
              curr_antinode.first += k * dist_row;
              curr_antinode.second += k * dist_col;
            }
          }
        } else {
          const Coordinate antinode1{antenna2.first + dist_row, antenna2.second + dist_col};
          const Coordinate antinode2{antenna1.first - dist_row, antenna1.second - dist_col};

          if (in_bounds(antinode1)) {
            antinodes.insert(antinode1);
          }
          if (in_bounds(antinode2)) {
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
