#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
  // Divide a by b. Let the remainder be r. r = a % b
  // If r == 0, then b is the GCD of a and b
  // If r != 0, then GCD of a and b == GCD of b and r
  int euclidsGCDIterative(int a, int b) {
    // No need to ensure that b is the smaller number.
    // There will be at most one more iteration to swap a and b
    while (b > 0) {
      int temp = a % b;
      a = b;
      b = temp;
    }

    return a;
  }

  int euclidsGCDRecursive(int a, int b) {
    if (b == 0) {
      return a;
    }

    return euclidsGCDRecursive(b, a % b);
  }

 public:
  int findGCD(vector<int>& nums) {
    // nums.size() >= 2
    int smallest = INT_MAX;
    int largest = INT_MIN;

    for (auto const& num : nums) {
      smallest = min(smallest, num);
      largest = max(largest, num);
    }

    return euclidsGCDIterative(largest, smallest);
  }
};
