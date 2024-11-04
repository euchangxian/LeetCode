#include <cstddef>
#include <cstdlib>
#include <string_view>
#include <vector>

using namespace std;
class Solution {
 private:
  // Compute the longest proper prefix that is also a suffix
  std::vector<int> computeLPS(std::string_view pattern) {
    std::vector<int> lps(pattern.size(), 0);

    // start from second char, since lps[0] = 0.
    for (int i = 1; i < pattern.size(); ++i) {
      int length = lps[i - 1];  // start with previous LPS length

      // while no match and length > 0, fall back to previous known prefix.
      while (length > 0 && pattern[i] != pattern[length]) {
        length = lps[length - 1];
      }

      // If a match is found, extend the prefix
      if (pattern[i] == pattern[length]) {
        ++length;
      }

      lps[i] = length;
    }

    return lps;
  }

  std::vector<int> getSubstringIndicesKMP(std::string_view s,
                                          std::string_view pattern) {
    std::vector<int> indices;
    indices.reserve(s.size());

    std::vector<int> lps = computeLPS(pattern);

    int i = 0;  // index for s
    int j = 0;  // index for pattern
    while (i < s.size()) {
      if (s[i] == pattern[j]) {
        ++i;
        ++j;

        // check if the pattern is matched.
        if (j == pattern.size()) {
          // push back the index of the start of the pattern
          indices.push_back(i - pattern.size());

          j = lps[j - 1];
        }
        continue;
      }

      // on mismatch, use LPS to shift the pattern
      if (j > 0) {
        j = lps[j - 1];
        continue;
      }

      // Otherwise, this means that we are at the start of the pattern, advance
      // i only.
      ++i;
    }

    return indices;
  }

 public:
  std::vector<int> beautifulIndices(std::string_view s,
                                    std::string_view a,
                                    std::string_view b,
                                    int k) {
    // An index i is beautiful if:
    // - 0 <= i <= s.length - a.length,
    // - s[i..(i+a.length-1)] == a, i.e., a is a substring of s.
    // and if there exists in index j such that
    // - 0 <= j <= s.length - b.length
    // - s[j..(j+b.length-1)] == b, i.e., b is a substring of s
    // and |j - i| <= k, i.e., the start of the substring a and b is <= k
    // distance apart.
    // Output: array of beautiful indices in sorted ascending order.
    // Naively, find the indices of the start of all substrings of a and b
    // respectively.
    // O(n * La + n * Lb), naive string matching. Could be improved to
    // O(n + La + Lb) using KMP.
    // Then, since the indices would already be in sorted order, use a two
    // pointer approach to check the pairs of (i, j) if |j - i| <= k.
    // See 244.Shortest Word Distance Two, where instead of a naive O(m^2) all
    // pairs comparison, exploit the already-sorted property of the indices,
    // and avoid further comparison by advancing the lower-value pointer, since
    // the distance between the pointers would only increase.
    if (s.size() < a.size() || s.size() < b.size()) {
      return {};
    }
    std::vector<int> indicesA = getSubstringIndicesKMP(s, a);
    std::vector<int> indicesB = getSubstringIndicesKMP(s, b);

    std::vector<int> beautiful;
    beautiful.reserve(s.size() / a.size());
    int i = 0;
    int j = 0;
    while (i < indicesA.size() && j < indicesB.size()) {
      int diff = std::abs(indicesA[i] - indicesB[j]);
      if (diff <= k) {
        beautiful.push_back(indicesA[i]);  // we want index i.
        // seems like each beautiful index should only be considered once.
        ++i;
        continue;  // however, each j can be paired with multiple i.
      }

      // advance the lower value index otherwise to find new pairs.
      if (indicesA[i] < indicesB[j]) {
        ++i;
      } else {
        ++j;
      }
    }
    return beautiful;
  }
};
