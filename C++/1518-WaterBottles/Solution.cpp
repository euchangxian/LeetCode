class Solution {
public:
  int numWaterBottles(int numBottles, int numExchange) {
    int result = numBottles;
    while (numBottles >= numExchange) {
      int k = numBottles % numExchange;
      numBottles /= numExchange;
      result += numBottles;
      numBottles += k;
    }
    return result;
  }
};
