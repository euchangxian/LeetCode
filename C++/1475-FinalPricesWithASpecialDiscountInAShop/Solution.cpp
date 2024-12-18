#include <cstddef>
#include <cstdlib>
#include <stack>
#include <vector>

class Solution {
 public:
  std::vector<int> finalPrices(std::vector<int>& prices) {
    // buy ith item, discount equivalent to prices[j], j is the minimum index
    // such that j > i and prices[j] <= prices[i]. Otherwise, no discount.
    // Hm. I.e., find the left-most index j on the right of i,
    // such that prices[j] is less than the price of the item.
    // Naively, a linear search to the right of index i would work. O(n^2).
    // Can we do better? How?
    // Observe: once we encounter a price that is small enough, we can
    // discount all previous items with a greater price. Monotonic stack!
    std::vector<int> newPrices = prices;

    // monotonically increasing stack
    std::stack<int> incStack;
    for (int i = 0; i < prices.size(); ++i) {
      // pop previous bigger prices if applicable.
      while (!incStack.empty() && prices[incStack.top()] >= prices[i]) {
        newPrices[incStack.top()] -= prices[i];
        incStack.pop();
      }

      incStack.push(i);
    }

    return newPrices;
  }
};
