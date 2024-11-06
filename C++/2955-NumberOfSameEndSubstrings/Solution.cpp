#include <array>
#include <cstdlib>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::vector<int> sameEndSubstringCount(
      std::string_view s,
      std::vector<std::vector<int>>& queries) {
    // Seemed a bit difficult at first, where my first thought was to use 2D-DP
    // to figure out the number of same end substrings...
    // However, lets try to look at a simpler variant!
    // Take for example the subarray "aaa". The number of same-end substrings
    // would be 1-len = "a", "a", "a", 2-len = "aa", "aa", 3-len = "aaa"
    // I.e., its nC2, where n is the number of same-chars in the substring.
    // nC2 = n * (n-1) / 2
    // then add n since the 1-len substrings are not accounted for.

    // Each counts[i] represent the respective count of characters in the
    // substring s[0..i]
    std::vector<std::array<int, 26>> counts;
    counts.reserve(s.size() + 1);  // inclusive left/right. offset by 1

    std::array<int, 26> count{};  // running count, for simpler copy-push
    counts.push_back(count);      // allows for inclusive start calculations
    for (int i = 0; i < s.size(); ++i) {
      ++count[s[i] - 'a'];
      counts.push_back(count);  // copy ctor
    }

    std::vector<int> answers;
    answers.reserve(queries.size());
    for (std::vector<int>& query : queries) {
      int l = query[0];
      int r = query[1];

      std::array<int, 26>& leftCount = counts[l];
      std::array<int, 26>& rightCount = counts[r + 1];

      int sum = 0;
      for (int i = 0; i < 26; ++i) {
        int n = rightCount[i] - leftCount[i];

        sum += n + (n * (n - 1) / 2);
      }
      answers.push_back(sum);
    }
    return answers;
  }
};
