#include <algorithm>
#include <array>
#include <string_view>

class Solution {
 public:
  bool canReach(std::string_view s, int minJump, int maxJump) {
    // binary string s.
    // Start at index 0, which is '0'.
    // Jump from index i to index j if:
    // - i+minJump <= j <= min(i+maxJump, n-1)
    // - s[j] == '0'
    // Return true if can reach index n-1, false otherwise.
    //
    // Greedy? Jump as far as possible? No. can construct non-optimal to hide
    // '0' at minJump distance.
    // Just do dp[j] |= dp[k] for i-maxJump <= k <= i-minJump, if s[k] == '0'
    // Nope. Too slow.
    //
    // Observe that dp[i] is true iff s[i] == '0', and there's at least one
    // reachable index in the window [i-maxJump..i-minJump].
    // We just need to check that there's an index reachable - prefix.
    constexpr std::size_t MAX_N = 1E5;
    const auto n = static_cast<int>(s.size());

    // prefix[i] => #idx reachable in [0, i)
    std::array<int, MAX_N + 1> prefix{};
    prefix[1] = true;
    for (auto i = 1; i < n; ++i) {
      if (s[i] != '0') {
        prefix[i + 1] = prefix[i];
      }

      auto reachable = 0;
      if (s[i] == '0') {
        auto windowRight = i - minJump;
        if (windowRight >= 0) {
          auto windowLeft = std::max(0, i - maxJump);
          reachable =
              std::clamp(prefix[windowRight + 1] - prefix[windowLeft], 0, 1);
        }
      }
      prefix[i + 1] = prefix[i] + reachable;
    }
    return prefix[n] - prefix[n - 1] >= 1;
  }
};
