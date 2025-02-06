#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int tupleSameProduct(std::vector<int>& nums) {
    // Find (a, b, c, d) such that a*b = c*d, where a, b, c, d are distinct.
    // Naive O(n^4). How can we do better?
    // Does the array being distinct help? In a sense, if we iterate O(N^2) to
    // get the products a*b, then we know that any matches must be from
    // different factors c*d, given that the numbers are distinct.
    // O(n^2) is sufficient to get AC.
    // NOTE: (a, b, c, d) is equivalent to
    // (a, b, d, c), (b, a, c, d), and (b, a, d, c),
    // (c, d, a, b), (c, d, b, a), (d, c, a, b) and (d, c, b, a)
    // Thus, each match produces 8 tuples.
    // Each pair can also be paired with every existing pair with the same
    // product.
    const int n = nums.size();
    int count = 0;
    std::unordered_map<int, int> seen;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        count += 8 * seen[nums[i] * nums[j]]++;
      }
    }
    return count;
  }
};
