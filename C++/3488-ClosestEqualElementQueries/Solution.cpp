#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> solveQueries(std::vector<int>& nums,
                                std::vector<int>& queries) {
    // Circular array nums.
    // For each query i:
    // - find the minimum distance between the element at queries[i] and any
    //   other index j such that nums[queries[i]] == nums[j].
    //   -1 if not.
    //
    // Seems like precomputation?
    // A 2D vector of indices will be correct already.
    // Can we do better?
    const auto n = static_cast<int>(nums.size());
    auto circDist = [n](int a, int b) {
      auto diff = std::abs(a - b);
      return std::min(diff, n - diff);
    };

    std::unordered_map<int, std::vector<int>> valToIndices;
    valToIndices.reserve(n);
    for (int i = 0; i < n; ++i) {
      valToIndices[nums[i]].push_back(i);
    }

    std::vector<int> answer;
    answer.reserve(n);
    for (auto i : queries) {
      // must be present
      const auto& indices = valToIndices[nums[i]];
      if (indices.size() == 1) {
        answer.push_back(-1);
        continue;
      }

      // must be present
      auto it = std::ranges::lower_bound(indices, i);
      auto leftJ = it == indices.begin() ? indices.back() : *(it - 1);
      auto rightJ = (it + 1) == indices.end() ? indices.front() : *(it + 1);

      auto result = std::min(circDist(i, leftJ), circDist(i, rightJ));
      answer.push_back(result);
    }
    return answer;
  }
};
