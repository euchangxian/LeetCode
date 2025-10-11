#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 maximumTotalDamage(std::vector<int>& power) {
    // power[i] represent damage of the ith spell.
    // If a magician casts a power[i] spell, then they cannot cast any spell
    // with a damage of power[i]-2,power[i]-1,power[i]+1,poewr[i]+2.
    // i.e., [-2..+2] range.
    // Each spell can be cast once.
    // Return the maximum possible total damage that can be cast.
    //
    // power[i] <= 1E9
    // => Need a map.
    constexpr auto cannotCast = [](int p1, int p2) {
      return p1 != p2 && std::abs(p1 - p2) <= 2;
    };

    std::unordered_map<int, int> freq;
    for (auto p : power) {
      ++freq[p];
    }

    std::vector<int> uniq;
    uniq.reserve(freq.size());
    for (auto [p, _] : freq) {
      uniq.emplace_back(p);
    }
    std::ranges::sort(uniq);

    const auto n = static_cast<int>(uniq.size());
    std::vector<i64> dp(n);
    dp[0] = static_cast<i64>(uniq[0]) * freq[uniq[0]];
    for (int i = 1; i < n; ++i) {
      int currPower = uniq[i];
      i64 currDamage = static_cast<i64>(currPower) * freq[currPower];

      dp[i] = dp[i - 1];
      int j = i - 1;
      while (j >= 0 && cannotCast(currPower, uniq[j])) {
        --j;
      }

      if (j >= 0) {
        dp[i] = std::max(dp[i], dp[j] + currDamage);
      } else {
        dp[i] = std::max(dp[i], currDamage);
      }
    }
    return dp.back();
  }
};
