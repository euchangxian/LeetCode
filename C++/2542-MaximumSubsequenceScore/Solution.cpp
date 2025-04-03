#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

using i64 = long long;

constexpr int MAX_N = 1e5;

class Solution {
 public:
  i64 maxScore(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
    // Take the sum of the top K elements. Keep track of their indices.
    // Save the k-th largest element.
    // For each index in nums2 in ascending order of nums2[j], (thus,
    // nums2[j] is the minimum):
    // - if j is in the set, then take sum * nums2[j]
    // - else, ((sum - kth + nums1[j]) * nums2[j])
    const int n = nums1.size();

    std::vector<std::pair<int, int>> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
      v.emplace_back(nums1[i], nums2[i]);
    }
    // sort descending order of nums2
    std::ranges::sort(v, std::greater<>{}, &std::pair<int, int>::second);

    // minHeap.
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;

    i64 result = 0;
    i64 curr = 0;
    for (const auto [num1, num2] : v) {
      pq.push(num1);
      curr += num1;

      if (pq.size() > k) {
        curr -= pq.top();
        pq.pop();
      }

      if (pq.size() == k) {
        result = std::max(result, curr * num2);
      }
    }
    return result;
  }
};
