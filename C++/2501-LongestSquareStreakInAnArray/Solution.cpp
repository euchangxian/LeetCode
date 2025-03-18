#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <vector>

using i64 = long long;

constexpr int maxElems = 100001;
const int maxRoot = std::sqrt(maxElems);

class Solution {
 public:
  int longestSquareStreak(std::vector<int>& nums) {
    // A subsequence is called a Streak if
    // - the length of the subsequence is at least 2,
    // - after sorting the subsequence, each element is the square of the
    //   previous element.
    //
    // I guess this is a more constrained Longest Increasing Subsequence
    // problem? Except the order does not matter. Therefore, find all unique
    // squares, like two-sum?
    // I.e., for {4, 3, 6, 16, 8, 2},
    //
    // Use the squared number as the key:
    // 16: 4
    // 9: 3
    // 36: 6
    // 16 -> saw 4 earlier, 256: 16
    // 64 -> 8
    // 4 -> 2 (how can we determine if we found 4? explore both directions?)
    // What if we have multiple possible sequences? i.e., power of 2s, power of
    // 3s?
    //
    // What if we just sort the array, using an ordered Set?
    // Visualizes into something like a linkedlist:
    // e.g., for {4, 3, 6, 16, 8, 2}
    // =>        {2, 3, 4, 6, 8, 16}
    //            ^
    //                  ^
    //                        ^
    //                            ^ // length 4
    //               ^              // 3 * 3 = 9 not in array, terminate
    //                  ^           // Ah, repeated work... Cant simply erase?
    //                                 What about a DP array/memoization?
    //                                 i.e., store the length of the subsequence
    //                                 Ah....... Just update the value of the
    //                                 squared number, since we will traverse
    //                                 it later due to the sorted order...
    // In fact, given the constraints, we can solve in O(n) time?
    // std::sort(nums.begin(), nums.end());

    // Element Set.
    std::bitset<maxElems> set{};
    for (int num : nums) {
      set.set(num);
    }

    // longest square streak. Maintains the length of the square subsequence
    // ending at nums[i].
    std::array<int, maxElems> lss{};

    int maxStreak = 1;
    for (int i = 2; i < maxElems; ++i) {
      if (!set.test(i)) {
        continue;
      }
      maxStreak = std::max(maxStreak, getStreak(set, lss, i));
    }
    return maxStreak > 1 ? maxStreak : -1;
  }

 private:
  int getStreak(std::bitset<maxElems>& set,
                std::array<int, maxElems>& lss,
                int curr) {
    if (!set.test(curr)) {
      return 0;
    }

    if (curr > maxRoot) {
      return 1;
    }

    if (lss[curr] > 0) {
      return lss[curr];
    }

    // No need to check for overflow; base case checks it already.
    lss[curr] = 1 + getStreak(set, lss, curr * curr);
    return lss[curr];
  }
};
