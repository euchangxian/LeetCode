class Solution {
 public:
  int maxBottlesDrunk(int numBottles, int numExchange) {
    // numBottles represent the initial number of full bottles.
    // In one operation:
    // - Drink any number of full bottles, turning them into empty bottles, OR
    // - Exchange numExchange empty bottles with one full water bottle, then
    //   increment numExchange by 1, i.e., cost increases.
    // Return the maximum number of bottles that can be drunk.
    //
    // Simulation?
    // Drink all, exchange until no longer possible, drink all again.
    int result = numBottles;
    for (auto empty = numBottles; empty >= numExchange; ++numExchange) {
      ++result;
      empty -= (numExchange - 1);
    }
    return result;
  }
};
