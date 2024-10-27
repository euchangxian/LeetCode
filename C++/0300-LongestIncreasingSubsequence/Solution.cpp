#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 public:
  int lengthOfLIS(std::vector<int>& nums) {
    int n = nums.size();

    // LIS must be sorted.
    // See: Patience Solitaire.
    // 1. Cards coming in one-by-one
    // 2. Cards need to be place in "piles" following some rules
    //
    // Rules:
    // - A card can only be placed on top of a higher value card
    // - If no such pile exists, create a new pile.
    // - Use as few piles as possible.
    //
    // Essentially, the dp array does not represent the actual increasing
    // subsequence itself; It represents "piles".
    // When a card (num) is drawn, if it is bigger than the top card on the
    // last pile, then create a new pile, effectively extending the increasing
    // subsequence.
    // If it is smaller, then we need to find the right pile to place it.
    // We do this by finding the first pile whose top card is >= than our
    // current card and replace it. This is optimal because:
    // 1. Any future card that could've been placed on the old card can still be
    //    placed on our new (smaller) card
    // 2. We might now be able to place future cards that are between our new
    //    card and the old card that we replaced
    // The number of piles at the end equals the length of LIS because:
    // - We only create a new pile when we can extend the sequence
    // - When we replace cards, we're just optimizing for future possibilities
    std::vector<int> dp;
    dp.reserve(n);
    dp.push_back(nums[0]);

    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] > dp.back()) {
        // Can trivially extend the sequence.
        dp.push_back(nums[i]);
        continue;
      }

      // std::lower_bound returns an iterator to the first element GREATER THAN
      // OR EQUAL / NOT LESS than the given value. *it >= num
      // std::upper_bound returns an iterator to the first element GREATER than
      // the given value. *it > num
      // Search for the first element in the LIS that is greater than or equal
      // to the current element, and replace it.
      auto it = std::lower_bound(dp.begin(), dp.end(), nums[i]);
      *it = nums[i];
    }

    return dp.size();
  }

  int lengthOfLISNaive(vector<int>& nums) {
    int n = nums.size();

    // Let dp[i] represent the longest increasing subsequence at i
    vector<int> dp(n, 1);
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }

    return *max_element(dp.begin(), dp.end());
  }
};
