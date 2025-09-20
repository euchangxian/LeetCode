#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
 public:
  int calculate(std::string_view s) {
    // Abide by order of operations. * or / + or -, left to right.
    // Division should truncate towards 0.
    // Think this is Stack-based.
    // Probably preprocess? To create a postfix expression.
    auto op = [](char op) -> std::function<int(int, int)> {
      switch (op) {
        case '+':
          return std::plus<>{};
        case '-':
          return std::minus<>{};
        case '*':
          return std::multiplies<>{};
        case '/':
          return std::divides<>{};
        default:
          std::unreachable();
      }
    };
  }
};
