#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> distinctNumbers(std::vector<int>& nums, int k) {
    // construct array ans of size n-k+1 where ans[i] is the number of distinct
    // numbers in the subarray.
    // I.e., fixed size sliding window unique of size k.
    // Maintain an unordered_map with frequency, popping when 0.
    // fixed size array/vector works too, requires an extra variable.
    const int n = nums.size();

    std::vector<int> answer;
    answer.reserve(n - k + 1);

    std::array<int, 100'001> window{};
    int unique = 0;
    for (int i = 0; i < n; ++i) {
      if (window[nums[i]]++ == 0) {
        ++unique;
      }

      if (i >= k && --window[nums[i - k]] == 0) {
        --unique;
      }

      if (i >= k - 1) {
        answer.push_back(unique);
      }
    }
    return answer;
  }
};
