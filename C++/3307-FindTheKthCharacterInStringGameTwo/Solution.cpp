#include <vector>

using i64 = long long;
class Solution {
 public:
  char kthCharacter(i64 k, std::vector<int>& operations) {
    auto n = static_cast<int>(operations.size());
    int result = 0;
    for (int i = 0; i < n && i < 60; ++i) {
      if (((k - 1) >> i) & 1) {
        result += operations[i];
      }
    }
    return (result % 26) + 'a';
  }
};
