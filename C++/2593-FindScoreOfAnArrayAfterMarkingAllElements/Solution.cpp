#include <array>
#include <cstddef>
#include <cstdlib>
#include <map>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  long long findScore(std::vector<int>& nums) {
    auto cmp = [](const std::array<int, 2>& a,
                  const std::array<int, 2>& b) -> bool {
      // For PQUEUE, condition is negated. This is because we want the "min"
      // element to be at the front.
      return a[0] > b[0] || (a[0] == b[0] && a[1] > b[1]);
    };

    std::priority_queue<std::array<int, 2>, std::vector<std::array<int, 2>>,
                        decltype(cmp)>
        minHeap(cmp);

    std::vector<char> marked(nums.size(), false);
    for (int i = 0; i < nums.size(); ++i) {
      minHeap.push({nums[i], static_cast<int>(i)});
    }

    long long score = 0LL;
    while (!minHeap.empty()) {
      auto [val, idx] = minHeap.top();
      minHeap.pop();

      if (marked[idx]) {
        continue;
      }

      score += val;
      marked[idx] = true;

      if (idx - 1 >= 0) {
        marked[idx - 1] = true;
      }
      if (idx + 1 < nums.size()) {
        marked[idx + 1] = true;
      }
    }
    return score;
  }

  long long findScoreSlow(std::vector<int>& nums) {
    // Ordered Set is used to get efficient min-value retrieval,
    // and to remove the adjacent elements (at random) efficiently.
    auto cmp = [&nums](int i, int j) -> bool {
      return nums[i] < nums[j] || (nums[i] == nums[j] && i < j);
    };

    std::map<int, int, decltype(cmp)> indices(cmp);
    for (int i = 0; i < nums.size(); ++i) {
      indices[i] = nums[i];
    }

    long long score = 0LL;
    while (!indices.empty()) {
      auto [idx, val] = *indices.begin();
      indices.erase(idx);

      score += val;

      if (idx - 1 >= 0) {
        indices.erase(idx - 1);
      }

      if (idx + 1 < nums.size()) {
        indices.erase(idx + 1);
      }
    }

    return score;
  }
};
