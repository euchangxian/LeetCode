#include <string_view>

class Solution {
 public:
  int maxOperations(std::string_view s) {
    // binary string s.
    // any number of times:
    // - choose any index i where i+1 < s.length such that s[i] == '1',
    //   s[i+1] == '0'
    // - move s[i] to the right until it reaches the end of the string or
    //   encounters another '1'.
    // Return the maximum number of operations that can be done.
    //
    // Doesn't seem like mutating the order of operations will result in a
    // different maximum operation.
    // Seems more like its based off the 1s and 0s and their positions?
    //
    // NOPE. Misunderstood.
    // Each operation of moving a '1' to the right is considered a SINGLE op
    // regardless of how many 0s it encounters.
    // If we wanted the minimum, then counting from the rightmost is correct,
    // since we want each '1' to be blocked as little as possible.
    const auto n = static_cast<int>(s.size());

    int result = 0;
    int ones = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '1') {
        ++ones;
        continue;
      }

      if (i > 0 && s[i - 1] == '1') {
        result += ones;
      }
    }
    return result;
  }
};
