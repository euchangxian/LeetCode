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
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
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
    // Only +, -, () and digits.
    // Stack.
    // Could recurse into parentheses.
    // Two Stacks? One for operands, one for operators. Keep track of the
    // number of left parentheses as state?
    // i.e., push operands. If theres an operator and two elements in the stack,
    // then evaluate the expression and push back onto the stack.
    //
  }
};
