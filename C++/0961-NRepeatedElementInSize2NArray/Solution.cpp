#include <bitset>
#include <utility>
#include <vector>

constexpr int MAX_VAL = 1E4;
class Solution {
 public:
  int repeatedNTimes(std::vector<int>& nums) {
    // nums.length == 2*n
    // nums contain n+1 unique elements.
    // Exactly one element of nums is repeated n times.
    //
    // Majority element? Nope. Requires >n repeats.
    std::bitset<MAX_VAL + 1> seen{};

    for (auto x : nums) {
      if (seen[x]) {
        return x;
      }
      seen[x] = true;
    }
    std::unreachable();
  }
};
