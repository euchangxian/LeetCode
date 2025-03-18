#include <queue>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> frequency;

    for (int num : nums) {
      frequency[num]++;
    }

    auto cmp = [&frequency](int a, int b) {
      return frequency[a] < frequency[b];
    };

    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

    for (const auto& pair : frequency) {
      pq.push(pair.first);
    }

    std::vector<int> result;
    for (int i = 0; i < k && !pq.empty(); i++) {
      result.push_back(pq.top());
      pq.pop();
    }

    return result;
  }
};
