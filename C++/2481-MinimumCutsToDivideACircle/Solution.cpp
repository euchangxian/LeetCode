class Solution {
 public:
  int numberOfCuts(int n) {
    // two types of cuts. Full diameter, radius.
    // radii cut seems to be the building block. Every two radius cut can be
    // combined to make a diameter cut.
    // Hm. 4 => 2 cuts, 3 => 3 cuts, 8 => 4 cuts.
    // Parity-based.
    // N radius cuts to cut into N parts.
    // For even, can combine 2 radius cuts into 1 diameter cut.
    if (n == 1) {
      return 0;
    }
    return n % 2 == 0 ? n / 2 : n;
  }
};
