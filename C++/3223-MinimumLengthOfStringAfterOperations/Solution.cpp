#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int minimumLength(std::string_view s) {
    // Any number of times:
    // - Choose j such that there exists at least one i < j < k such that
    //   s[i] == s[j] == s[k]
    // - Delete the closest s[i] and s[k].
    // Want: Minimum Length of s.
    //
    // For these any amount of operations kind, simulation is usually not the
    // answer.
    // Hm. Frequency array. If there is at least 3, then delete 2.
    // Therefore. for each character, the remaining amount would
    // be x - (floor(x/3) * 2)
    // Any counter-examples?
    // "aaaaa" => returns 3 instead of 1.
    // Wrong formula!!
    // Notice that we want to remove in pairs. Thus, we can think of it as
    // a parity problem. This is because there will only be two "end" states,
    // remaining == 1 => previous == 3, and remaining == 2 => previous == 4.
    // All other amounts reduces to these two.
    //
    // If x < 3, return x.
    // If x >= 3:
    //   - if x is odd, return 1.
    //   - if x is even, return 2.
    std::array<int, 26> frequency{};
    for (char c : s) {
      ++frequency[c - 'a'];
    }

    int remaining = 0;
    for (int freq : frequency) {
      if (freq < 3) {
        remaining += freq;
      } else {
        remaining += 2 - (freq & 1);
      }

      // branchless fun. Not necessarily better due to compiler optimization.
      // for >= 3 condition, if odd, freq&1 == 1, thus we do 2 - freq&1
      // remaining += ((freq < 3) * freq) + ((freq >= 3) * (2 - (freq & 1)));
    }
    return remaining;
  }
};
