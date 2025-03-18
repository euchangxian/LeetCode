#include <unordered_map>
#include <vector>

class Solution {
 public:
  bool isNStraightHand(std::vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize) {
      return false;
    }

    std::unordered_map<int, int> freq;
    for (int num : hand) {
      ++freq[num];
    }

    int i = 0;
    while (i < hand.size()) {
      int start = hand[i];

      // Decrement start till the minimum number possible
      while (freq[start - 1]) {
        --start;
      }

      for (int next = start; next < start + groupSize; ++next) {
        if (!freq[next]) {
          return false;
        }
        --freq[next];
      }

      while (i < hand.size() && !freq[hand[i]]) {
        ++i;
      }
    }

    return true;
  }
};
