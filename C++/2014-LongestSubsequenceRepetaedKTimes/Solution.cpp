#include <array>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string longestSubsequenceRepeatedK(std::string_view s, int k) {
    // Given string s of length n, integer k.
    // Find the longest subsequence repeated k times.
    // A subsequence seq is repeated k times if seq*k is a subsequence of s.
    // Return the longest, lexicographically largest.
    //
    // 2 <= n, k <= 2000
    // 2 <= n < k * 8
    // Hm. This means that the length of the longest subsequence is at most
    // n/k (repeated k times).
    //
    // Honestly. No idea.
    // For a subsequence of size 1, i.e., k=1, quite trivial from largest to
    // smallest alphabet.
    // k=2?
    auto n = static_cast<int>(s.size());

    // to prune
    std::array<int, 26> freq{};
    for (char c : s) {
      ++freq[c - 'a'];
    }

    std::string chars;
    for (int i = 25; i >= 0; --i) {
      chars += std::string(freq[i] / k, i + 'a');
    }

    auto valid = [&](std::string_view seq, int repeats) {
      for (int i = 0, j = 0; i < n && repeats < k; ++i) {
        j += s[i] == seq[j];

        if (j == seq.size()) {
          ++repeats;
          j = 0;
        }
      }
      return repeats >= k;
    };

    std::string result;
    auto dfs = [&](this auto&& dfs, std::string& curr, int mask) -> void {
      for (int i = 0; i < chars.size(); ++i) {
        if ((mask & (1 << i)) == 0) {
          std::string seq = curr + chars[i];
          if (valid(seq, 0)) {
            if (seq.size() > result.size()) {
              result = seq;
            }
            dfs(seq, mask + (1 << i));
          }
        }
      }
    };

    std::string curr{};
    dfs(curr, 0);

    return result;
  }
};
