class Solution {
 public:
  int minBitFlips(int start, int goal) {
    // 0 <= start, goal <= 10e9
    int requiredFlips = start ^ goal;

    // Count bits
    // int count = 0;
    // while (requiredFlips) {
    //  count += requiredFlips & 1;
    //  requiredFlips >>= 1;
    //}

    int count = __builtin_popcount(requiredFlips);
    return count;
  }
};
