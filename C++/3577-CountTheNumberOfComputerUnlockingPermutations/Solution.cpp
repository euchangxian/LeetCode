#include <vector>

constexpr int MOD = 1E9 + 7;

class Solution {
 public:
  int countPermutations(std::vector<int>& complexity) {
    // n locked computers labelled 0..n-1 with unique passwords.
    // complexity[i] indicate the complexity of the passwords.
    // computer i=0 is already decrypted and serves as root
    // ALl other computers must be unlocked using an already unlocked computer.
    // - computer i can be unlocked using the password of computer j, where
    //   j < i AND complexity[j] < complexity[i]
    // - computer j must be unlocked.
    // Find the number of permutations representing a valid order in which the
    // computers can be unlocked, modulo 1E9+7.
    //
    // There is one condition in which the number of ways is 0:
    // - complexity[root] = min(complexity)
    //
    // Seems dp-like.
    // Let dp[i] be the number of ways to unlock computer i.
    // dp[i] = sum(dp[j]) for all j < i and complexity[j] < complexity[i]
    // But this is O(N^2).
    // How can we do better?
    //
    // Hm. We must use index 0 as the start. As long as its the minimum,
    // we have n-1 possible nodes to unlock next.
    // We can just use the root node to unlock everything.
    // It will always fulfil j < i and complexity[j] < complexity[i].
    // factorial(n-1), lol.
    const auto n = static_cast<int>(complexity.size());

    long long result = 1;
    for (int i = 1; i < n; ++i) {
      if (complexity[i] <= complexity[0]) {
        return 0;
      }
      result = (result * i) % MOD;
    }

    return result;
  }
};
