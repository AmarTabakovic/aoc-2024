#include "util.hpp"

int Part1(const std::vector<std::string> &input) {
  std::vector<int> left_vec, right_vec;

  for (const auto &line : input) {
    std::istringstream iss{line};
    int left, right;
    iss >> left >> right;
    left_vec.push_back(left);
    right_vec.push_back(right);
  }

  std::sort(left_vec.begin(), left_vec.end());
  std::sort(right_vec.begin(), right_vec.end());

  int sum = 0;
 
  // Both vectors have the same size
  for (int i = 0; i < left_vec.size(); i++) {
    sum += std::abs(right_vec[i] - left_vec[i]);
  }
  
  return sum;
}

int Part2(const std::vector<std::string> &input) {
  std::vector<int> left_vec;
  std::map<int, int> freq;

  for (const auto &line : input) {
    std::istringstream iss{line};
    int left, right;
    iss >> left >> right;

    left_vec.push_back(left);
    freq[right]++;
  }

  int sum = 0;
  for (auto i : left_vec) {
    sum += (freq[i] * i);
  }

  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
 
  std::vector<std::string> input = util::ReadInput("input"); 

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
