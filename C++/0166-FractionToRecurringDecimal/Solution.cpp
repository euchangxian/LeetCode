#include <cstdlib>
#include <string>
#include <unordered_map>

class Solution {
 public:
  std::string fractionToDecimal(int numerator, int denominator) {
    // Given two integers representing numerator and denominator of a fraction,
    // return the fraction in string format.
    // If the fractional part is repeating, enclose the repeating part in
    // parentheses.
    // Return any possible answer.
    //
    // Converting to a double loses precision. And we cant identify the
    // repeating part? e.g., 1/3 => 0.(3)
    // Long Division? How to detect repeating patterns?
    // 1. Handle sign part by XOR-ing the sign bits of numerator and
    //    denominator.
    //
    // Edge Cases:
    // - numerator = 0 => return 0
    // - denominator = 0 (problem constraints prevent this)
    // - INT_MIN/-1 => overflow
    if (numerator == 0) {
      return std::string{"0"};
    }

    std::string result;
    result.reserve(1E4 + 1);
    if ((numerator < 0) ^ (denominator < 0)) {
      result += '-';
    }
    auto n = std::llabs(numerator);
    auto d = std::llabs(denominator);

    auto integral = n / d;
    result += std::to_string(integral);

    auto remainder = n % d;
    if (remainder == 0) {
      return result;
    }

    result += '.';

    // {remainder, idx}
    std::unordered_map<long long, std::size_t> seen;
    for (; remainder > 0; remainder %= d) {
      if (auto it = seen.find(remainder); it != seen.end()) {
        auto idx = it->second;
        result.insert(idx, 1, '(');
        result += ')';
        break;
      }

      seen[remainder] = result.size();
      remainder *= 10;
      result += std::to_string(remainder / d);
    }
    return result;
  }
};
