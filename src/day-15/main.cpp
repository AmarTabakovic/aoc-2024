#include "util.hpp"

enum class MapEntry {
  kNone,
  kWall,
  kBox,
  kLanternfish,
};

enum class Move { kTop, kBottom, kLeft, kRight };

using Map = std::vector<std::vector<MapEntry>>;

// (row, col)
using Coordinate = std::pair<int, int>;

MapEntry CharToMapEntry(char c)
{
  using enum MapEntry;
  switch (c) {
  case '.':
    return kNone;
  case '#':
    return kWall;
  case 'O':
    return kBox;
  case '@':
    return kLanternfish;
  }

  return kNone;
}

Move CharToMove(char c)
{
  using enum Move;
  switch (c) {
  case '^':
    return kTop;
  case 'v':
    return kBottom;
  case '<':
    return kLeft;
  case '>':
    return kRight;
  }

  return kTop;
}

void Render(const Map &map)
{
  for (const auto &row : map) {
    for (const auto &entry : row) {
      if (entry == MapEntry::kBox) {
        std::cout << "O";
      } else if (entry == MapEntry::kLanternfish) {
        std::cout << "@";
      } else if (entry == MapEntry::kNone) {
        std::cout << ".";
      } else {
        std::cout << "#";
      }
    }
    std::cout << std::endl;
  }
}

Coordinate NextPos(const Coordinate &coord, const Move &move)
{
  switch (move) {
  case Move::kBottom:
    return {coord.first + 1, coord.second};
  case Move::kLeft:
    return {coord.first, coord.second - 1};
  case Move::kRight:
    return {coord.first, coord.second + 1};
  case Move::kTop:
    return {coord.first - 1, coord.second};
  }
}

int Part1(const std::vector<std::string> &input)
{
  Map map{};

  int moves_begin_index{};
  Coordinate lanternfish_pos{};

  for (int i = 0; i < input.size(); i++) {
    if (input[i] == "") {
      moves_begin_index = i + 1;
      break;
    }
    map.push_back({});
    for (int j = 0; j < input[i].size(); j++) {
      auto map_entry{CharToMapEntry(input[i][j])};
      if (map_entry == MapEntry::kLanternfish) {
        lanternfish_pos = {i, j};
      }
      map[i].push_back(map_entry);
    }
  }

  std::vector<Move> moves;
  for (int i = moves_begin_index; i < input.size(); i++) {
    for (int j = 0; j < input[i].size(); j++) {
      moves.push_back(CharToMove(input[i][j]));
    }
  }

  for (auto move : moves) {
    Render(map);

    // Lanternfish is surrounded by walls, cannot go out of bounds
    Coordinate next_pos{NextPos(lanternfish_pos, move)};

    auto dest{map[next_pos.first][next_pos.second]};

    if (dest == MapEntry::kNone) {
      // Lanternfish faces free space, swap
      map[next_pos.first][next_pos.second] = MapEntry::kLanternfish;
      map[lanternfish_pos.first][lanternfish_pos.second] = MapEntry::kNone;

      lanternfish_pos = next_pos;
    } else if (dest == MapEntry::kWall) {
      // Lanternfish faces wall, cannot move
      continue;
    } else if (dest == MapEntry::kBox) {
      Coordinate next_non_box_pos{next_pos};
      int num_boxes{0};

      while (map[next_non_box_pos.first][next_non_box_pos.second] == MapEntry::kBox) {
        num_boxes++;
        if (move == Move::kBottom) {
          next_non_box_pos.first++;
        } else if (move == Move::kTop) {
          next_non_box_pos.first--;
        } else if (move == Move::kLeft) {
          next_non_box_pos.second--;
        } else if (move == Move::kRight) {
          next_non_box_pos.second++;
        }
      }
      // Box(es) followed by wall, cannot move
      if (map[next_non_box_pos.first][next_non_box_pos.second] == MapEntry::kWall) {
        continue;
      } else if (map[next_non_box_pos.first][next_non_box_pos.second] == MapEntry::kNone) {
        // Box(es) followed by free space, move
        map[next_non_box_pos.first][next_non_box_pos.second] = MapEntry::kBox;
        map[next_pos.first][next_pos.second] = MapEntry::kLanternfish;
        map[lanternfish_pos.first][lanternfish_pos.second] = MapEntry::kNone;

        lanternfish_pos = next_pos;
      }
    }
  }

  int sum_gps{0};
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == MapEntry::kBox) {
        sum_gps += 100 * i + j;
      }
    }
  }

  return sum_gps;
}

int Part2(const std::vector<std::string> &input) {
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
