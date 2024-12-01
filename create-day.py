import os
import sys

CMAKELISTS_CONTENT = 'add_executable(day{:02d} main.cpp)'
MAIN_CONTENT = '''#include "util.hpp"

int Part1(const std::vector<std::string> &input) {
  return 0;
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
'''

if len(sys.argv) != 2:
    print('Please enter the day.')
    exit(1)

day_nr = None

try:
    day_nr = int(sys.argv[1])
except ValueError:
    print('Not a number.')
    exit(1)

if (day_nr > 25):
    print('Cannot go beyond the 25th day.')
    exit(1)

# Create the day directory
try:
    day_dir = f'src/day-{day_nr:02d}'
    os.mkdir(day_dir)
except OSError as error:
    print(error)
    exit(1)

# Create main.cpp
with open(f'{day_dir}/main.cpp', 'w') as file:
    file.write(MAIN_CONTENT)

# Create CMakeLists.txt
with open(f'{day_dir}/CMakeLists.txt', 'w') as file:
    file.write(CMAKELISTS_CONTENT.format(day_nr))

print(f'Successfully created day {day_nr}')
