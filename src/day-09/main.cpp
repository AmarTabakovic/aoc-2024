#include "util.hpp"

int CharToInt(char c)
{
  return c - '0';
}

using NumType = long long;
constexpr NumType kEmpty{-1};

std::vector<int> Decompress(const std::string &disk_map)
{
  bool is_disk{true};
  std::vector<int> decompressed{};
  int disk_index{0};
  for (auto disk : disk_map) {
    auto size{CharToInt(disk)};
    if (is_disk) {
      for (int i = 0; i < size; i++) {
        decompressed.push_back(disk_index);
      }
      disk_index++;
    } else {
      for (int i = 0; i < size; i++) {
        decompressed.push_back(-1);
      }
    }
    is_disk = !is_disk;
  }
  return decompressed;
}

NumType ComputeChecksum(const std::vector<int> &decompressed)
{
  NumType checksum{0};

  for (int i = 0; i < decompressed.size(); i++) {
    if (decompressed[i] == -1) {
      continue;
    }
    checksum += decompressed[i] * i;
  }

  return checksum;
}

NumType Part1(const std::vector<std::string> &input)
{
  auto decompressed{Decompress(input[0])};
  auto left{0}, right{static_cast<int>(decompressed.size()) - 1};

  while (right > left) {
    if (decompressed[left] != kEmpty) {
      left++;
      continue;
    }
    if (decompressed[right] == kEmpty) {
      right--;
      continue;
    }
    decompressed[left] = decompressed[right];
    decompressed[right] = kEmpty;
    left++;
    right--;
  }

  return ComputeChecksum(decompressed);
}

NumType Part2(const std::vector<std::string> &input)
{
  auto decompressed = Decompress(input[0]);
  auto right{static_cast<int>(decompressed.size()) - 1};

  std::unordered_set<int> checked;

  while (right >= 0) {
    if (decompressed[right] == -1 || checked.contains(decompressed[right])) {
      right--;
      continue;
    }

    auto curr_disk_num{decompressed[right]};
    auto right1{right};
    int disk_count{0};

    while (decompressed[right1] == curr_disk_num && right1 >= 0) {
      disk_count++;
      right1--;
    }

    // Search for suitable free space from left to right
    for (int i = 0; i < decompressed.size(); i++) {
      if (decompressed[i] == kEmpty) {
        // Count the number of free spaces
        int free_count{0}, j{i};
        while (decompressed[j] == kEmpty) {
          free_count++;
          j++;
        }

        // We found a suitable segment of free space
        if (j - 1 < right1 + 1 && free_count >= disk_count) {
          // Overwrite the segment of free space with the disk number
          for (int k = i; k < i + disk_count; k++) {
            decompressed[k] = curr_disk_num;
          }

          // "Free up" previously used disk space
          for (int k = right1 + 1; k <= right; k++) {
            decompressed[k] = kEmpty;
          }
          checked.insert(curr_disk_num);
          break;
        } else { // Otherwise, skip forward past the free space
          i = j;
        }
      }
    }
    right = right1; // Update pointer to skip behind the old disk entries
  }

  return ComputeChecksum(decompressed);
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
