#include "util.hpp"

// (x, y)
using Coordinate = std::pair<int, int>;

constexpr int kNumRows{103}, kNumCols{101};

struct Robot
{
  Coordinate pos;
  Coordinate vel;
};

std::vector<Robot> ParseRobots(const std::vector<std::string> &input)
{
  std::vector<Robot> robots;
  for (const auto &line : input) {
    int px{}, py{}, vx{}, vy{};
    std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
    robots.push_back(Robot{{px, py}, {vx, vy}});
  }
  return robots;
}

void Render(const std::vector<Robot> robots)
{
  // Insert into set for fast querying
  std::set<Coordinate> coords{};
  for (const auto &robot : robots) {
    coords.insert({robot.pos.first, robot.pos.second});
  }

  for (int i = 0; i < kNumRows; i++) {
    for (int j = 0; j < kNumCols; j++) {
      if (coords.contains({j, i})) {
        std::cout << "R";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

void MoveRobot(Robot &robot, int steps)
{
  robot.pos.first = (robot.pos.first + robot.vel.first * steps + kNumCols * steps) % kNumCols;
  robot.pos.second = (robot.pos.second + robot.vel.second * steps + kNumRows * steps) % kNumRows;
}

int Part2Manual(const std::vector<std::string> &input)
{
  std::vector<Robot> robots{ParseRobots(input)};

  int iterations{99};
  for (auto &robot : robots) {
    MoveRobot(robot, iterations);
  }

  while (true) {
    // MacOS and Linux only
    system("clear");

    std::cout << "Iteration " << iterations << std::endl;
    Render(robots);

    std::cout << "Christmas tree found? (y/n) ";
    std::string input{};

    while (!(input == "n" || input == "y")) {
      std::cin >> input;

      if (input == "y") {
        return iterations;
      } else if (input != "n") {
        std::cout << "Unknown input.\n";
      }
    }

    for (auto &robot : robots) {
      MoveRobot(robot, kNumCols);
    }
    iterations += kNumCols;
  }
  return 0;
}

int Part2Automatic(const std::vector<std::string> &input)
{
  std::vector<Robot> robots{ParseRobots(input)};

  int iterations{99};
  for (auto &robot : robots) {
    MoveRobot(robot, iterations);
  }

  while (true) {
    std::set<Coordinate> coords{};
    for (const auto &robot : robots) {
      coords.insert({robot.pos.first, robot.pos.second});
    }

    // DFS
    const int xmas_tree_threshold{42};
    std::set<Coordinate> visited{};

    for (const auto &robot : robots) {
      if (!visited.contains(robot.pos)) {
        std::stack<Coordinate> to_visit{};
        to_visit.push(robot.pos);
        auto count{0};
        while (!to_visit.empty()) {
          auto curr{to_visit.top()};
          to_visit.pop();
          visited.insert({curr});
          count++;

          if (count >= xmas_tree_threshold) {
            return iterations;
          }

          int x{curr.first}, y{curr.second};

          const std::vector<Coordinate> neighbors{{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};

          for (const auto &neighbor : neighbors) {
            if (coords.contains(neighbor) && !visited.contains(neighbor)) {
              to_visit.push(neighbor);
            }
          }
        }
      }
    }

    for (auto &robot : robots) {
      MoveRobot(robot, kNumCols);
    }

    iterations += kNumCols;
  }
  return 0;
}

int Part1(const std::vector<std::string> &input)
{
  std::vector<Robot> robots{ParseRobots(input)};

  const int iterations{100};
  for (auto &robot : robots) {
    MoveRobot(robot, iterations);
  }

  int num_q1{0}, num_q2{0}, num_q3{0}, num_q4{0};
  for (auto &robot : robots) {
    auto x{robot.pos.first};
    auto y{robot.pos.second};

    if (x < kNumCols / 2 && y < kNumRows / 2) {
      num_q1++;
    } else if (x > kNumCols / 2 && y < kNumRows / 2) {
      num_q2++;
    } else if (x < kNumCols / 2 && y > kNumRows / 2) {
      num_q3++;
    } else if (x > kNumCols / 2 && y > kNumRows / 2) {
      num_q4++;
    }
  }

  return num_q1 * num_q2 * num_q3 * num_q4;
}

int Part2(const std::vector<std::string> &input, bool manual)
{
  // This one was weird. At first, I just searched for symmetry along the
  // y-axis, since I thought that the Christmas tree would be just one giant
  // tree that fills the entire grid, but I gave up this approach after
  // the number of iterations started reaching the millions.
  //
  // I then manually analyzed the output of the first few hundred
  // iterations and noticed that the robots cluster together either
  // horizontally or vertically in the following iterations:
  //
  // 58 (hor), 99 (vert), 161 (hor), 200 (vert), 264 (hor), 301 (vert),
  // 367 (hor), ...
  //
  // So every 101 iterations there is a vertical clustering and every 103
  // iterations there is a horizontal clustering.
  // I simply looked at every 101st iteration starting from iteration 99 and
  // after a while, I found the Christmas tree.
  //
  // I then noticed that the Christmas tree is solid and that it consists of
  // many connected robots, which meant that this could be solved with a graph
  // traversal by traversing each connected component and counting the number
  // of nodes. If the number of nodes is above a threshold, say 42, then
  // the connected component must almost certainly be the Christmas tree.
  //
  // For the sake of Christmas spirit, I left both variants of part 2 here.

  if (manual) {
    return Part2Manual(input);
  }
  return Part2Automatic(input);
}

int main(int argc, char **argv)
{
  std::ios::sync_with_stdio(false);

  bool manual{false};

  const auto print_usage = []() { std::cout << "Usage:\n" << "day14 [--manual]\n"; };

  if (argc > 2) {
    print_usage();
    return 1;
  }

  if (argc == 2) {
    auto arg = std::string{argv[1]};
    if (arg == "--manual") {
      manual = true;
    } else {
      print_usage();
      return 1;
    }
  }

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input, manual) << std::endl;

  return 0;
}
