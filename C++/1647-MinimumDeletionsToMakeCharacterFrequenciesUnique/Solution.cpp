#include <algorithm>
#include <array>
#include <functional>
#include <string_view>

class Solution {
 public:
  int minDeletions(std::string_view s) {
    // A string s is called good if no two different characters in s have the
    // same frequency.
    // Return the minimum number of deletions to make s good.
    // Hm. Kinda cascading deletes? Delete from the largest frequency first.
    // i.e., try to find the next empty slot.
    // Worst case should therefore be all characters have same frequency >= 26
    std::array<int, 26> frequency{};
    for (char c : s) {
      ++frequency[c - 'a'];
    }

    int result = 0;
    std::sort(frequency.begin(), frequency.end(), std::greater<>{});
    for (int i = 1; i < 26; ++i) {
      if (frequency[i] == 0) {
        break;
      }

      if (frequency[i] >= frequency[i - 1]) {
        // the new frequency should be the previous frequency-1.
        int deletions = frequency[i] - std::max(0, frequency[i - 1] - 1);
        frequency[i] -= deletions;
        result += deletions;
      }
    }
    return result;
  }
};
