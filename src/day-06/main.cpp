#include "util.hpp"

// (row, column)
using Coordinate = std::pair<int, int>;

// Clockwise (matters!)
enum class Direction { kUp = 0, kRight, kDown, kLeft };

Coordinate NextCoordinate(const Coordinate &coord, Direction dir)
{
  switch (dir) {
  case Direction::kUp:
    return {coord.first - 1, coord.second};
  case Direction::kDown:
    return {coord.first + 1, coord.second};
  case Direction::kLeft:
    return {coord.first, coord.second - 1};
  case Direction::kRight:
    return {coord.first, coord.second + 1};
  }
}

Direction NextDirection(Direction dir)
{
  // The evil cast + modulo + cast!
  return static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
}

int Part1(const std::vector<std::string> &input)
{
  Coordinate current_pos{};
  Direction current_dir{Direction::kUp};
  auto num_rows{input.size()};
  auto num_cols{input[0].size()};

  // Find starting coordinate
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (input[i][j] == '^') {
        current_pos = std::make_pair(i, j);
      }
    }
  }

  std::set<Coordinate> visited{};
  bool in_map{true};
  while (true) {
    visited.insert(current_pos);
    auto next_pos{NextCoordinate(current_pos, current_dir)};

    // Bounds check
    if (next_pos.first >= num_rows || next_pos.first < 0 || next_pos.second >= num_cols
        || next_pos.second < 0) {
      break;
    }
    // Collision check
    if (input[next_pos.first][next_pos.second] == '#') {
      // Le evil cast + modulo + cast
      current_dir = NextDirection(current_dir);
    } else {
      current_pos = next_pos;
    }
  }

  return visited.size();
}

int Part2(std::vector<std::string> &input)
{
  auto num_rows{input.size()};
  auto num_cols{input[0].size()};

  Coordinate starting_pos{};
  // Find starting coordinate
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (input[i][j] == '^') {
        starting_pos = {i, j};
      }
    }
  }

  int num_possible_obstacles{0};

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      // Skip existing obstacle or guard's starting position
      if (input[i][j] == '#' || (i == starting_pos.first && j == starting_pos.second)) {
        continue;
      }

      input[i][j] = '#';

      auto current_pos{starting_pos};
      Direction current_dir{Direction::kUp};

      // Track whether we visited an obstacle before already from the same direction
      std::set<std::pair<Coordinate, Direction>> history;

      while (true) {
        auto next_pos{NextCoordinate(current_pos, current_dir)};

        // Bounds check
        if (next_pos.first >= num_rows || next_pos.first < 0 || next_pos.second >= num_cols
            || next_pos.second < 0) {
          break;
        }
        // Collision check
        if (input[next_pos.first][next_pos.second] == '#') {
          if (history.contains({next_pos, current_dir})) {
            num_possible_obstacles++;
            break;
          } else {
            history.insert({next_pos, current_dir});
            current_dir = NextDirection(current_dir);
          }
        } else {
          current_pos = next_pos;
        }
      }
      input[i][j] = '.';
    }
  }

  return num_possible_obstacles;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
