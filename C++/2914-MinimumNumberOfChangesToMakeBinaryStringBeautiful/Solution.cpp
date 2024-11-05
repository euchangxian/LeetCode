#include <cstddef>
#include <cstdlib>
#include <string_view>

using namespace std;
class Solution {
 public:
  int minChanges(std::string_view s) {
    // Seems rather simple, where the given string is of even length, it is
    // guaranteed that we can pair up elements, (which is the smallest possible
    // substring of size 2).
    // Therefore, for each pair, we can simply change pairs that have elements
    // that do not match for a cost of 1, in a greedy fashion.
    // Can we prove that the greedy choice works?
    int changes = 0;
    for (int i = 0; i < s.size(); i += 2) {
      changes += s[i] != s[i + 1];
    }
    return changes;
  }
};
