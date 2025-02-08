#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
    // envelopes[i] = [width, height]
    // An envelope can fit into another iff the other's width and height are
    // strictly greater than this envelope.
    // Find number of envelopes that can be Russian Doll-ed.
    // Like an LIS, but with Pairs. std::pair uses lexicographical ordering
    // which does not satisfy our requirements, since we need both elements
    // to be less/greater.
    // Wew, a preprocessing step reduces this into a generic LIS.
    // Sort by width, then in ascending order of heights. We keep the smallest
    // of each distinct width.
    // NOPE. By doing so, we potentially undercount, i.e., we want to wrap a
    // envelope with a bigger envelope, but by removing all duplicate width,
    // we potentially lose a bigger envelope that is sufficient to wrap the
    // current envelope.
    // Therefore, what we want to do is still sort by ascending order of width,
    // BUT tie-broken by descending order of Heights. This allows us to
    // iterate left-to-right, satisfying the width constraint, and find LIS
    // on Heights.
    //
    // On implementation-wise, because of this Zig-Zag-like pattern, the LIS
    // will only increase in length when considering a new width.
    // This is because for the same width, the heights are in descending order,
    // replacing the existing height in the LIS.

    // sort by width, tie broken by increasing heights.
    std::sort(envelopes.begin(), envelopes.end(),
              [](const auto& a, const auto& b) {
                return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
              });

    // only need to store height.
    std::vector<int> lis;
    lis.reserve(envelopes.size());
    lis.push_back(envelopes[0][1]);
    for (int i = 1; i < envelopes.size(); ++i) {
      int height = envelopes[i][1];
      if (height > lis.back()) {
        lis.push_back(height);
        continue;
      }

      auto it = std::lower_bound(lis.begin(), lis.end(), height);
      *it = height;
    }
    return lis.size();
  }
};
