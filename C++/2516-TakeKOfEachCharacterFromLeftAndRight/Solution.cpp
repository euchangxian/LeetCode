#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int takeCharacters(std::string_view s, int k) {
    // String with 'a', 'b' and 'c' only. To take at least k of each character.
    // Minimize extra characters taken.
    //
    // Off the bat, greedy approach seems wrong. Lets try to come up with a
    // counter-example.
    // "aababbbbbbbbbbbcccbbaaaa"
    // Taking greedily, suppose we take left by default.
    // "aa|babbbbbbbbbbbcccbbaaaa"
    // "aababbbbbbbbbbbcccbbaaaaaaa"
    // Probably attempt to take from left only.
    // Not good!
    //
    // Seems like a sliding window of some sorts. Size of at least 3k?
    // Doesnt seem so though? Though we can try 3k+1, 3k+2, ....
    // Jk what about trying the whole string first..? Try to minimize till 3k.
    // Or what about counting the frequency of the i characters from the
    // left/right?
    //
    // REDUCE the problem. The initial problem seems difficult to have a
    // "sliding window".
    // BUT, what if we say "find the largest subarray such that the count of
    // the elements outside is still at least k."
    // This allows us to form a varying length sliding window starting from
    // the left and slide to the right!!!
    std::array<int, 3> count{};
    for (char c : s) {
      ++count[c - 'a'];
    }

    auto lessThanK = [k](const int freq) -> bool { return freq < k; };
    // impossible.
    if (std::any_of(count.begin(), count.end(), lessThanK)) {
      return -1;
    }

    int largest = 0;
    int l = 0;
    for (int r = 0; r < s.size(); ++r) {
      --count[s[r] - 'a'];

      while (std::any_of(count.begin(), count.end(), lessThanK)) {
        ++count[s[l] - 'a'];
        ++l;
      }

      largest = std::max(largest, r - l + 1);
    }

    return static_cast<int>(s.size()) - largest;
  }
};
