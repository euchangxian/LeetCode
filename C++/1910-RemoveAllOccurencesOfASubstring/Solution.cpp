#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string removeOccurrences(std::string_view s, std::string_view sub) {
    // remove all occurences of the substring in s.
    // Note that removing a substring may cause another substring to match.
    // e.g.,
    // s = aabb, sub = ab
    //      ^^ remove ab
    // s = a  b
    //     ^  ^ remove ab.
    // s = ''
    // Naively, O(nk) substring search.
    // KMP, rolling hash for O(N + K)?
    // Not sure, since there will be removals from the string.
    // Even if a fixed size window hash is maintained?
    const int k = sub.size();
    std::string res{s};

    int j = 0;
    for (int i = 0; i < s.size(); ++i) {
      res[j++] = s[i];

      if (j >= k) {
        std::string_view sv{res.begin(), res.end()};
        if (sv.substr(j - k, k) == sub) {
          j -= k;
        }
      }
    }
    return res.substr(0, j);
  }
};
