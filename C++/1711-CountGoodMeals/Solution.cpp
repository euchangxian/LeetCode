#include <unordered_map>
#include <utility>
#include <vector>

constexpr int MOD = 1e9 + 7;

class Solution {
 public:
  int countPairs(std::vector<int>& deliciousness) {
    // A good meal is a pair of indices (i, j) such that:
    // - deliciousness[i] + deliciousness[j] is a power of 2.
    //
    // two-sum like, I guess.?
    // Naively its log(nums[i]) time per subproblem, to enumerate all
    // differences that sum to a power of 2, making for a total of
    // nlogn.
    // Seems supported by the constraint that deliciousness <= 2^20.
    //
    // Can we do better?
    constexpr int MAX_NUM = (1 << 21);
    int result = 0;
    std::unordered_map<int, int> seen;
    for (int num : deliciousness) {
      // 2^k - num == target
      // Given that deliciousness[i] >= 0, we implicitly get:
      // 2^k >= num
      for (int i = 1; i <= MAX_NUM; i <<= 1) {
        int target = i - num;
        auto it = seen.find(target);

        if (it != seen.end()) {
          result = (result + 1LL * it->second) % MOD;
        }
      }
      ++seen[num];
    }
    return result;
  }
};
