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
  std::string minCostGoodCaption(std::string_view caption) {
    // A good caption is a string where every character in it appears in
    // groups of at least 3 consecutive occurences.
    // Each operation on caption[i]:
    // - Change caption[i] to the character immediately before it,
    //   if caption[i] != 'a'
    // - Change caption[i] to the character immediately after it,
    //   if caption[i] != 'z'
    // Minimum operations to transform caption into a good caption.
    // Return the lexicographically smallest good caption.
    //
    // Jeez. Feels like Edit Distance.
    // For these kind of triplets, the approach is almost always to consider
    // the centre. Can we do the same for this, Given that we need consecutive
    // triplets to be equal?
    //
    // Choices
    // 1. Change current-considered character to be equal to previous.
    //    - How do we keep track of triplet/consecutive-3 status?
    // 2. Keep current character.
  }
};
