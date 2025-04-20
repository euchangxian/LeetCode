#include <array>
#include <vector>

constexpr int MAX_VAL = 1000;
class Solution {
 public:
  int numRabbits(std::vector<int>& answers) {
    std::array<int, MAX_VAL + 1> freq{};
    for (int x : answers) {
      ++freq[x];
    }

    // at least that many rabbits
    int result = answers.size();
    for (int i = 0; i <= MAX_VAL; ++i) {
      // ceiling division
      // Determine the number of groups of size (i+1) rabbits.
      int groups = (freq[i] + i) / (i + 1);
      result += (groups * (i + 1)) - freq[i];  // add the extra not in answers
    }
    return result;
  }
};
