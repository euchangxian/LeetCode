#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> queryResults(int limit,
                                std::vector<std::vector<int>>& queries) {
    // Simulation. Keep track of unique colors using "buckets".
    std::unordered_map<int, int> colors{};
    std::unordered_map<int, int> buckets;
    buckets.reserve(queries.size());

    std::vector<int> answer;
    answer.reserve(queries.size());
    for (const auto& query : queries) {
      const int ball = query[0];
      const int color = query[1];

      if (colors.contains(ball) && --buckets[colors[ball]] == 0) {
        buckets.erase(colors[ball]);
      }

      colors[ball] = color;
      ++buckets[colors[ball]];

      answer.push_back(buckets.size());
    }
    return answer;
  }
};
