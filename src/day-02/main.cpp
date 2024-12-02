#include "util.hpp"

std::vector<std::vector<int>> GenerateReports(const std::vector<std::string> &input)
{
  std::vector<std::vector<int>> reports;

  for (const auto &line : input) {
    std::vector<int> report;
    std::istringstream iss{line};
    int curr;
    while (iss >> curr) {
      report.push_back(curr);
    }
    reports.push_back(std::move(report));
  }

  return reports;
}

int Part1(const std::vector<std::string> &input) {
  auto reports = GenerateReports(input);

  int num_safe = 0;

  for (const auto &report : reports) {
    bool is_safe = true;
    bool is_increasing = ((report[1] - report[0]) > 0);

    for (int i = 0; i < report.size() - 1; i++) {
      auto delta = report[i + 1] - report[i];

      if (delta == 0 || std::abs(delta) > 3 || is_increasing != delta > 0) {
        is_safe = false;
        break;
      }
    }

    if (is_safe) {
      num_safe++;
    }
  }

  return num_safe;
}

int Part2(const std::vector<std::string> &input)
{
  auto reports = GenerateReports(input);

  // Le epic ugly code (insert trollface here)
  //
  // There is probably a way more elegant way to do all of this but sleep
  // deprivation is already kicking in hard enough

  int num_safe = 0;

  for (const auto &report : reports) {
    // Cannot just take the first pair anymore, since either the first
    // or the second might get removed throughout this algorithm
    int num_growing = 0, num_decreasing = 0;
    for (int i = 0; i < report.size() - 1; i++) {
      auto delta = report[i + 1] - report[i];
      if (delta > 0) {
        num_growing++;
      } else if (delta < 0) {
        num_decreasing++;
      }
    }
    bool is_increasing = num_growing > num_decreasing;

    // Search for the first pair of invalid indices
    std::vector<int> invalid_indices;
    for (int i = 0; i < report.size() - 1; i++) {
      auto delta = report[i + 1] - report[i];
      if (delta == 0 || std::abs(delta) > 3 || is_increasing != delta > 0) {
        invalid_indices.push_back(i);
        invalid_indices.push_back(i + 1);
        break;
      }
    }

    // We found no invalid indices, the report is OK
    if (invalid_indices.empty()) {
      num_safe++;
      continue;
    }

    bool is_safe = false;
    for (auto invalid_index : invalid_indices) {
      // Create the indices to iterate over report without the current invalid
      // index
      std::vector<int> indices;
      for (int i = 0; i < report.size(); i++) {
        if (i == invalid_index) {
          continue;
        }
        indices.push_back(i);
      }

      bool is_curr_safe = true;
      for (int i = 0; i < indices.size() - 1; i++) {
        auto curr_index = indices[i];
        auto next_index = indices[i + 1];
        auto delta = report[next_index] - report[curr_index];

        if ((delta == 0 || std::abs(delta) > 3 || is_increasing != delta > 0)) {
          is_curr_safe = false;
          break;
        }
      }
      is_safe = is_safe || is_curr_safe;
    }

    if (is_safe) {
      num_safe++;
    }
  }
  return num_safe;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
