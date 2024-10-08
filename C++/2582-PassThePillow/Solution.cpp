class Solution {
 public:
  int passThePillow(int n, int time) {
    bool isReverse = (time / (n - 1)) & 1;
    int k = time % (n - 1);
    if (isReverse) {
      return n - k;
    }
    return k + 1;
  }
};
