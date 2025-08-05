#include <vector>

class Solution {
 public:
  int numOfUnplacedFruits(std::vector<int>& fruits, std::vector<int>& baskets) {
    // fruits[i] = quantity of ith type of fruit
    // baskets[j] = capacity of the jth basket
    // From left-to-right fruits:
    // - Each fruit type must be placed in the leftmost available basket with
    //   a capacity greater than or equal to the quantity.
    // - Each basket can only hold one type of fruit.
    // Return the number of fruit types that remain unplaced after allocating.
    //
    // Given small constraints, just simulate.
    auto n = static_cast<int>(fruits.size());
    int result = n;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (fruits[i] <= baskets[j]) {
          --result;
          baskets[j] = 0;
          break;
        }
      }
    }
    return result;
  }
};
