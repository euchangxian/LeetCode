#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

class Solution {
  static constexpr std::size_t MAX_POS = 2E5;

  enum Idx : std::size_t {
    Position = 0,
    Count = 1,
  };

 public:
  int maxTotalFruits(std::vector<std::vector<int>>& fruits,
                     int startPos,
                     int k) {
    // Infinite x-axis.
    // fruits[i] = [position, amount] where there are amount fruits at position.
    // fruits is initially sorted by position in ascending order.
    // Each position is unique.
    // Starting at startPos: at any position, can walk left or right 1 unit,
    // corresponding to 1 step. Harvest all fruits at that position.
    // Walk at most k steps in total.
    // Return maximum fruits that can be collected.
    //
    // Hm. Greedy? Graph-like? Probably not?
    //
    // Feels sliding window-like. Start from k-units all the way to the left.
    // Hm. But the window isnt a k-size window. I.e., moving left 1-unit, then
    // moving right 1-unit results in a delta of zero and no extra ground
    // covered.
    // Though, I believe this is the correct approach.
    // If we move x steps to the left, then we can move k-x steps to the right.
    // This means we end at (k-2x)-position to the right.
    // Is this symmetrical? Nope. We cover less ground on the right.
    // Hm. We can get the ranges possible.
    // Two for-loops seem sufficient, in both directions. There may be a bit
    // of repeated work.
    std::array<int, MAX_POS + 1> prefix{};
    for (const auto& fruit : fruits) {
      prefix[fruit[Idx::Position]] = fruit[Idx::Count];
    }

    auto n = static_cast<int>(fruits.size());
    auto minStepsBetween = [&](auto left, auto right) {
      auto goLeftThenRight = std::abs(startPos - left) + (right - left);
      auto goRightThenLeft = std::abs(right - startPos) + (right - left);
      return std::min(goLeftThenRight, goRightThenLeft);
    };

    int left = 0;
    int currSum = 0;
    int result = 0;
    for (int right = 0; right < n; ++right) {
      currSum += fruits[right][Idx::Count];

      while (left <= right &&
             minStepsBetween(fruits[left][Idx::Position],
                             fruits[right][Idx::Position]) > k) {
        currSum -= fruits[left][Idx::Count];
        ++left;
      }
      result = std::max(result, currSum);
    }

    return result;
  }
};
