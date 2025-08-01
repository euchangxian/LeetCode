#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> generate(int numRows) {
    std::vector<std::vector<int>> rows;
    rows.reserve(numRows);
    rows.push_back({1});
    for (int i = 1; i < numRows; ++i) {
      const auto& prev = rows.back();

      auto cols = i + 1;
      std::vector<int> curr(cols);
      curr[0] = curr.back() = 1;
      for (int j = 1; j < cols - 1; ++j) {
        curr[j] = prev[j - 1] + prev[j];
      }
      rows.emplace_back(std::move(curr));
    }
    return rows;
  }
};
