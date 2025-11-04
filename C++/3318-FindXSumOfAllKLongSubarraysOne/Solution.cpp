#include <algorithm>
#include <array>
#include <functional>
#include <ranges>
#include <utility>
#include <vector>

constexpr int MAX_VAL = 50;
class Solution {
 public:
  std::vector<int> findXSum(std::vector<int>& nums, int k, int x) {
    // Given n integers,
    // x-sum of an array is determined by:
    // - count occurances of all elements in the array
    // - keep track of the x-most frequent elements.
    //   tie-break by keeping the larger element.
    // - take the sum.
    // Return an integer array answer of length n-k+1 where answer[i] is the
    // x-sum of the subarray nums[i..i+k-1] (k-sized window)
    //
    // One for the top-x, the other for the remaining.
    const auto n = static_cast<int>(nums.size());
    std::vector<int> answer;
    answer.reserve(n - k + 1);

    auto xSum = [x](auto freq) {
      std::nth_element(freq.begin(), freq.begin() + x, freq.end(),
                       std::greater<>{});

      int sum = 0;
      for (auto [f, num] : freq | std::views::take(x)) {
        sum += f * num;
      }
      return sum;
    };

    // {freq, nums[i]}
    std::array<std::pair<int, int>, MAX_VAL + 1> freq{};
    for (int i = 0; i < n; ++i) {
      ++freq[nums[i]].first;
      freq[nums[i]].second = nums[i];

      if (i >= k) {
        --freq[nums[i - k]].first;
      }

      if (i + 1 >= k) {
        answer.push_back(xSum(freq));
      }
    }

    return answer;
  }
};
