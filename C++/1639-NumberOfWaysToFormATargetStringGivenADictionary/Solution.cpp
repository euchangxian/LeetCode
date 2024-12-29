#include <array>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

constexpr int MOD = 1'000'000'007;

class Solution {
 public:
  int numWays(std::vector<std::string>& words, std::string_view target) {
    // target should be formed left-to-right.
    // To form target[i], the kth character of the jth string, words[j][k] can
    // be used if target[i] = words[j][k].
    // Once used, for all j, words[j][x] for x <= k can not be used.
    // Want: Number of ways to form target.
    //
    // Hm. First, words are all same length. If target is longer than the words,
    // then there are no ways to form target.
    // In a simpler variant, if all words are equal to the target, then at each
    // index k, there are j choices
    // => k^j number of ways.
    //
    // Mhm. So let T be the length of the target, L be the length of the words,
    // N be the number of words.
    // if L == T, then the problem is simpler: At each index j,  find the
    // number of characters that are equal to target[j].
    // Should be simple: At each index j, count words[i][j] == target[j].
    //
    // However, if L > T... (L < T do not need to be considered), then there
    // are possible target[j] == words[i][k], k > j, which makes counting a
    // more complicated.
    // So suppose the later characters are picked. That means that characters
    // to the left can not be chosen anymore. how to count!!
    // Counting frequency?
    // Thinking about it as columns in words, what about tracking the frequency
    // of characters in each column?
    // Then, for each character in target, pick a column, count the number of
    // matching characters in that column, multiply it with the number of ways.
    // Oh....
    // dp[i][j] representing the number of ways to make up the first i
    // characters with the first j columns.
    const int t = target.size();

    const int n = words.size();
    const int k = words[0].size();
    if (t > k) {
      return 0;
    }

    std::vector<std::array<int, 26>> frequencies(k, std::array<int, 26>{});
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < k; ++j) {
        // j is the column.
        ++frequencies[j][words[i][j] - 'a'];
      }
    }

    // dp[i][j] is the number of ways to make target[0..i] using the first j
    // columns. Can definitely be optimized to 1D array.
    std::vector<std::vector<int>> dp(t + 1, std::vector<int>(k + 1, 0));

    // base case: 1 way to make empty string.
    //            0 ways to make any string with no characters (implicit)
    for (int j = 0; j < k + 1; ++j) {
      dp[0][j] = 1;  // 1 way regardless to make an empty string
    }

    // for each character in target
    for (int i = 1; i < t + 1; ++i) {
      // for each column
      for (int j = 1; j < k + 1; ++j) {
        long long take =
            (static_cast<long long>(dp[i - 1][j - 1]) *
             static_cast<long long>(frequencies[j - 1][target[i - 1] - 'a'])) %
            MOD;

        long long skip = dp[i][j - 1];
        dp[i][j] = (take + skip) % MOD;
      }
    }

    return dp[t][k];
  }
};
