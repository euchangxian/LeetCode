#include <string_view>
#include <utility>
#include <vector>

using i64 = long long;
constexpr int MOD = 1E9 + 7;

class Solution {
 public:
  int possibleStringCount(std::string_view word, int k) {
    // Each character may have been mis-typed multiple times.
    // Return the number of possible original strings that Alice might have
    // intended to type, if she was trying to type a string of size at least k.
    //
    // n <= 1E5, k <= 2000
    // That means that only sequences of length > k could have been mistyped.
    // Absolutely no idea. Getting worse at this.
    auto n = static_cast<int>(word.size());
    std::vector<int> segments{1};
    for (int i = 1; i < n; ++i) {
      if (word[i] == word[i - 1]) {
        ++segments.back();
      } else {
        segments.push_back(1);
      }
    }

    // if there was no restriction on k.
    int result = 1LL;
    for (int len : segments) {
      result = (static_cast<i64>(result) * len) % MOD;
    }

    // Each segment can be freely manipulated to still form an original string
    // satisfying >= k
    if (segments.size() >= k) {
      return result;
    }

    std::vector<int> dp(k, 0);
    dp[0] = 1;
    for (int len : segments) {
      std::vector<int> curr(k, 0);
      int sum = 0;
      for (int i = 0; i < k; ++i) {
        if (i > 0) {
          sum = (static_cast<i64>(sum) + dp[i - 1]) % MOD;
        }

        if (i > len) {
          sum = ((static_cast<i64>(sum) - dp[i - len - 1]) + MOD) % MOD;
        }
        curr[i] = sum;
      }
      dp = std::move(curr);
    }

    int invalid = 0;
    for (int i = segments.size(); i < k; ++i) {
      invalid = (static_cast<i64>(invalid) + dp[i]) % MOD;
    }
    return static_cast<int>((static_cast<i64>(result) - invalid + MOD) % MOD);
  }
};
