#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
 public:
  bool isNStraightHand(vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize) {
      return false;
    }

    unordered_map<int, int> freq;
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

int main() {
  // 1 : 1
  // 2 : 2
  // 3 : 2
  // 4 : 1
  // 6 : 1
  // 7 : 1
  // 8 : 1
  vector<int> tc = {1, 2, 3, 6, 2, 3, 4, 7, 8};
  cout << boolalpha << Solution().isNStraightHand(tc, 3) << endl;
}
