#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 private:
  bool feasible(int n, std::vector<int>& quantities, int maxAmount) {
    int storesUsed = 0;
    for (int i = 0; i < quantities.size(); ++i) {
      // ceiling division. each store can only receive one product.
      storesUsed += (quantities[i] + maxAmount - 1) / maxAmount;
    }

    return storesUsed <= n;  // represents all distributed.
  }

 public:
  int minimizedMaximum(int n, std::vector<int>& quantities) {
    // n Stores. m products where quantities[i] represent the number of ith
    // product.
    // Each store can be given at most one type, but any quantity, including 0.
    // Nice description.
    //
    // Looking at examples, its to give out ALL quantities, each store can be
    // given any amount including 0.
    // But each store can only get 1 product type.
    // Therefore, m/n will not work, if we have more than 1 product type.
    // I.e., something like splitting into subarrays of sum < k each.
    // => Binary search.
    int left = 1;
    int right = *std::max_element(quantities.begin(), quantities.end());

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (feasible(n, quantities, mid)) {
        // minimum lies to the left.
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};
