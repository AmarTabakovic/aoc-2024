#ifndef UTIL_HPP
#define UTIL_HPP

// Commonly used headers
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace util {

std::vector<std::string> ReadInput(const std::string &path)
{
  std::vector<std::string> input; 
  std::ifstream myfile{path};
  std::string line;
  
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      input.push_back(line);
    }
    myfile.close();
  }

  return input;
}
} // namespace util

#endif // UTIL_HPP
