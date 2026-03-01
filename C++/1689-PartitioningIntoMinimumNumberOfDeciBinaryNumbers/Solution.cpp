#include <algorithm>
#include <string_view>

class Solution {
 public:
  int minPartitions(std::string_view n) {
    // A decimal number is deci-binary if each of its digits is either 0 or 1
    // without any leading zeros.
    // 101 and 1100 are deci-binary, 112 and 3001 are not.
    // Return the minimum number of positive deci-binary numbers needed so that
    // they sum up to n.
    //
    // Huh hm.
    // Considering the nth-place, isn't it sufficient to get the max-digit?
    // Think we need to consider the carry? Hm. Maximum of 9 though.
    // Think there isnt a need.
    return *std::ranges::max_element(n) - '0';
  }
};
