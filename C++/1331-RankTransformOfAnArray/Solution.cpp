#include <set>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> arrayRankTransform(std::vector<int>& arr) {
    std::set<int> nums(arr.begin(), arr.end());

    std::unordered_map<int, int> rank;
    int r{1};
    for (int num : nums) {
      rank[num] = r++;
    }

    for (std::size_t i{0}; i < arr.size(); ++i) {
      arr[i] = rank[arr[i]];
    }
    return arr;
  }
};
