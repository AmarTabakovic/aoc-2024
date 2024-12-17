#include "util.hpp"

enum class Instruction { kAdv = 0, kBxl, kBst, kJnz, kBxc, kOut, kBdv, kCdv };

std::string Part1(const std::vector<std::string> &input)
{
  int reg_a{}, reg_b{}, reg_c{};
  std::sscanf(input[0].c_str(), "Register A: %d", &reg_a);
  std::sscanf(input[1].c_str(), "Register B: %d", &reg_b);
  std::sscanf(input[2].c_str(), "Register C: %d", &reg_c);

  auto program_str{input[4]};
  program_str = program_str.substr(9, program_str.size() - 8 + 1);
  std::replace(program_str.begin(), program_str.end(), ',', ' ');

  std::istringstream iss{program_str};
  std::vector<int> program{};
  int num{};

  while (iss >> num) {
    program.push_back(num);
  }

  auto combo = [&reg_a, &reg_b, &reg_c](int op) {
    if (op >= 0 && op <= 3) {
      return op;
    } else if (op == 4) {
      return reg_a;
    } else if (op == 5) {
      return reg_b;
    } else if (op == 6) {
      return reg_c;
    }
    return 0;
  };

  std::vector<int> out_buffer{};
  int instr_ptr{0};

  while (instr_ptr < program.size() - 1) {
    auto instr{static_cast<Instruction>(program[instr_ptr])};
    auto operand{program[instr_ptr + 1]};

    switch (instr) {
    case Instruction::kAdv: {
      reg_a = reg_a / (1 << combo(operand));
      break;
    }
    case Instruction::kBxl:
      reg_b ^= operand;
      break;
    case Instruction::kBst:
      reg_b = combo(operand) % 8;
      break;
    case Instruction::kJnz:
      if (reg_a != 0) {
        instr_ptr = operand;
        continue;
      }
      break;
    case Instruction::kBxc:
      reg_b ^= reg_c;
      break;
    case Instruction::kOut:
      out_buffer.push_back(combo(operand) % 8);
      break;
    case Instruction::kBdv: {
      reg_b = reg_a / (1 << combo(operand));
      break;
    }
    case Instruction::kCdv: {
      reg_c = reg_a / (1 << combo(operand));
      break;
    }
    }
    instr_ptr += 2;
  }

  std::ostringstream oss;
  for (auto it = out_buffer.begin(); it != out_buffer.end() - 1; it++) {
    oss << *it << ",";
  }
  oss << *(out_buffer.end() - 1);

  return oss.str();
}

int Part2(const std::vector<std::string> &input)
{
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::string> input = util::ReadInput("input");

  std::cout << Part1(input) << std::endl;
  std::cout << Part2(input) << std::endl;

  return 0;
}
