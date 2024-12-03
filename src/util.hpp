#ifndef UTIL_HPP
#define UTIL_HPP

// Commonly used headers
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace util {

class Timer
{
  enum class TimerState { kReset, kStarted, kStopped };

public:
  Timer() = default;
  ~Timer() = default;

  void Start()
  {
    if (state_ == TimerState::kStarted) {
      throw std::runtime_error("Timer is already running.");
    }

    t1_ = std::chrono::high_resolution_clock::now();
    state_ = TimerState::kStarted;
  }

  void Stop()
  {
    if (state_ != TimerState::kStarted) {
      throw std::runtime_error("Timer must be started first to be stopped.");
    }

    t2_ = std::chrono::high_resolution_clock::now();
    state_ = TimerState::kStopped;
  }

  void Reset()
  {
    t1_ = {};
    t2_ = {};
    state_ = TimerState::kReset;
  }

  double GetTimeMs()
  {
    if (state_ != TimerState::kStopped) {
      throw std::runtime_error("Timer must be stopped first to get the elapsed time.");
    }
    return std::chrono::duration<double, std::milli>(t2_ - t1_).count();
  }

private:
  using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

  TimePoint t1_, t2_;
  TimerState state_{TimerState::kReset};
};

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
