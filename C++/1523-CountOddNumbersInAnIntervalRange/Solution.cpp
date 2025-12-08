class Solution {
 public:
  int countOdds(int low, int high) {
    // Return the count of odd numbers in the range [low..high]
    return ((high + 1) / 2) - (low / 2);
  }
};
