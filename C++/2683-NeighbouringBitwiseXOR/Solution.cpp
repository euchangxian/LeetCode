#include <cstddef>
#include <cstdlib>
#include <numeric>
#include <vector>

class Solution {
 public:
  bool doesValidArrayExist(std::vector<int>& derived) {
    // derived[i] = original[i] ^ original[(i + 1)%n]
    // Note that derived/original is a binary array.
    // i.e., nums[i] = 0 | 1
    //
    // Determine if there exists a valid original array.
    // Hm. First glance seems like DP-ish. Since each original[i] can be either
    // 0 or 1, as long as it reflects on derived[i], where derived[i] == 0
    // means that original[i] == original[i+1], and derived[i] == 1 means that
    // original[i] != original[i+1].
    // Therefore, dp[i][j] represents if the first ith element of original
    // is valid, where original[i] == j.
    // Are there any XOR properties to exploit to do better?
    // Trying out random things:
    // Taking the XOR sum of derived, derived[i] = {1, 1, 0}
    // derived[0] = original[0] ^ original[1]
    // derived[1] = original[1] ^ original[2]
    // derived[2] = original[2] ^ original[0]
    // Can see that we are left with XORsum = original[0] ^ original[0]
    // Thus, XORsum must be equal to 0.
    // Is this a sufficient condition to determine if the valid array exists?
    return std::reduce(derived.begin(), derived.end(), 0,
                       [](int acc, int val) -> int { return acc ^ val; }) == 0;
  }
};
