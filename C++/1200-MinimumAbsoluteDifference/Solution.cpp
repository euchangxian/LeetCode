#include <algorithm>
#include <limits>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> minimumAbsDifference(std::vector<int>& arr) {
    // given distinct integers, find all pairs of elements with the minimum
    // absolute difference of any two elements.
    // Return a list of pairs, each pair follows:
    // - a < b
    // - b-a == minDiff of any two elements.
    //
    // Two pass?
    // Minimum difference occur from adjacent elements in a sorted array.
    // Can do in 1 pass.
    // Either vector::clear, or manual pointer management and shrinking.
    const auto n = static_cast<int>(arr.size());
    std::ranges::sort(arr);

    std::vector<std::vector<int>> result;
    auto minDiff = std::numeric_limits<int>::max();
    for (int i = 0; i < n - 1; ++i) {
      auto diff = arr[i + 1] - arr[i];
      if (diff > minDiff) {
        continue;
      }

      if (diff < minDiff) {
        minDiff = diff;
        result.clear();
      }
      result.push_back({arr[i], arr[i + 1]});
    }
    return result;
  }
};
