#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 public:
  int findMaxLength(vector<int>& nums) {
    // Want: Maximum length of a contiguous subarray with an equal number of
    // 0 and 1.
    // Not sliding window. We cannot determine when a number at the left of
    // the window should be removed.
    // Hmmmmmm...
    // Subarray => no sorting
    // 10^5 => at least an nlogn solution
    // Suppose we are at the ith index. What kind of information would allow us
    // to determine that there is some j < i such that nums[j..i] has an equal
    // amount of 0s and 1s?
    // We can easily find out the number of 0s and 1s from nums[0..i], simply
    // by maintaining a count, e.g., at i = 5, ones = 4, zeros = 2.
    // Then, we would want to know which nums[0..j] has ones = 2, so that we
    // can remove the corresponding number of ones.
    // 011 | 101. But this may also remove corresponding zeros though?
    // 0 1 1 0 1 0
    // 0 1 2 2 3 3 => seems like we may need to maintain the ones count, deduce
    // the zeros count?
    // What about maintaining a sort of balance? Add one for each '1', minus 1
    // for each '0'.
    // Naively, seeing any 0s at any index i would indicate that nums[0..i] has
    // the same number of 0s and 1s.
    // What information do we want to figure out nums[j..i]? i.e., if we see
    // balance = 5, then we want to look for balance = 5, since it indicates
    // that we can minus away that excess, i.e., that subarray containing 5
    // '1's.

    std::vector<int> prefixes(2 * nums.size() + 1, INT_MIN);
    // handles the case where nums[0..i] has equal count
    prefixes[0 + nums.size()] = -1;

    int count = 0;
    int maxSize = 0;
    for (int i = 0; i < nums.size(); ++i) {
      // Add 1 for 1s, subtract 1 for 0s
      count += nums[i] == 1 ? 1 : -1;

      // If we've seen this count before, we've found a balanced subarray
      // Because count[i] - count[j] = 0 means subarray (j,i] is balanced
      int idx = count + nums.size();  // offset to handle negatives
      if (prefixes[idx] != INT_MIN) {
        maxSize = std::max(maxSize, i - prefixes[idx]);
      } else {
        // We are seeing this count for the first time.
        prefixes[idx] = i;
      }
    }
    return maxSize;
  }
};
