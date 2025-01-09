#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>
#include <unordered_set>

class Solution {
 public:
  int equalDigitFrequency(std::string_view s) {
    // Rolling Hash!
    // This technique maintains a unique hash that can be updated in constant
    // time, that maps to a substring.
    // This rolling hash method is actually quite similar in concept to the
    // initial naive solution using a std::string_view.
    //
    // Hash of a substring s[i..j] inclusive:
    // hash = ((BASE * hash) + digit + 1)) % MOD
    // There are multiple distinct choices that come into play to determine the
    // Hash function.
    // Base:
    // The base is chosen to be a prime number 31, which is greater than the set
    // of possible digits [0..9], and is very optimizable by the compiler, since
    // 31 * x == (x << 5) - x
    //
    // Modulo:
    // The modulo is 1e9 + 7, which is a large prime that fits within a 32-bit
    // integer, and is easily remembered.
    //
    // Adding one to the digit:
    // This is to differentiate between "0" and "00", or "01" and "1", as
    // anything multiplied by 0 is still 0, resulting in collisions.
    constexpr int BASE = 31;
    constexpr int MOD = 1e9 + 7;

    const int L = static_cast<int>(s.size());
    std::unordered_set<int> seen;
    for (int start = 0; start < L; ++start) {
      int rollingHash = 0;

      std::array<int, 10> frequency{};
      int unique = 0;
      int maxFreq = 0;

      for (int end = start; end < L; ++end) {
        // update hash:
        // Temporarily convert to long long to avoid overflows.
        // No need to save as a long long. The MOD ensures the resultant hash
        // is within a 32-bit integer.
        rollingHash = ((1LL * BASE * rollingHash) + s[end] - '0' + 1) % MOD;

        if (frequency[s[end] - '0'] == 0) {
          ++unique;
        }
        maxFreq = std::max(maxFreq, ++frequency[s[end] - '0']);

        if (unique * maxFreq == end - start + 1) {
          seen.insert(rollingHash);
        }
      }
    }

    return static_cast<int>(seen.size());
  }

  int equalDigitFrequencyStringView(std::string_view s) {
    // Number of unique substrings of digit string s, where every digit appear
    // the same number of times.
    // First glance seemed like sliding window.
    // But given constraints, we can check all possible substrings, by iterating
    // over all possible lengths from [1..n], and then all possible starting
    // indices [0..n-1]
    // O(n^3). O(n^2) to check all substrings. O(n) for each substring.
    //
    // How can we do better?
    // Can optimize to O(n^2) with a different loop semantics and
    // std::string_view.
    // Instead of looping over all lengths, then starting indices,
    // loop over all starting indices, then all substrings. This allows us to
    // not have to re-compute the frequency of substrings starting from a
    // particular index.
    // Runs pretty fast, since no unnecessary heap allocations is done.
    const int L = static_cast<int>(s.size());

    std::unordered_set<std::string_view> seen;
    for (int start = 0; start < L; ++start) {
      std::array<int, 10> frequency{};
      int unique = 0;
      int maxFreq = 0;
      for (int end = start; end < L; ++end) {
        if (frequency[s[end] - '0']++ == 0) {
          ++unique;
        }
        maxFreq = std::max(maxFreq, frequency[s[end] - '0']);

        // If the maximum frequency multiplied with the number of unique
        // characters in the window is equal to the number of elements, then
        // we can conclude that each of the elements in the window occur
        // the same number of times.
        if (maxFreq * unique == end - start + 1) {
          seen.insert(s.substr(start, end - start + 1));
        }
      }
    }

    return static_cast<int>(seen.size());
  }
};
