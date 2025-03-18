#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
 public:
  long long dividePlayers(std::vector<int>& skill) {
    // First glance looked like partition equal subset sums which is a DP
    // problem. Second glance looked like CS3230's CD problem, which is a
    // Greedy problem.

    const std::size_t n = skill.size();
    std::sort(skill.begin(), skill.end());
    std::size_t l = 0;
    std::size_t r = n - 1;

    // All sums must be equal to this. Return early if not.
    const int targetSum = skill[l] + skill[r];
    long long chemistry =
        static_cast<long long>(skill[l++]) * static_cast<long long>(skill[r--]);

    // n is of even length. No need l <= r
    while (l < r) {
      if (skill[l] + skill[r] != targetSum) {
        return -1;
      }

      chemistry +=
          static_cast<long long>(skill[l]) * static_cast<long long>(skill[r]);

      ++l;
      --r;
    }

    return chemistry;
  }
};
