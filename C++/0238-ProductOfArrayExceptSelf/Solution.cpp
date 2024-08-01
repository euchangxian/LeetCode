#include <vector>

using namespace std;
class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    int n = nums.size();
    vector<int> postfixProduct = vector<int>(n, 1);

    for (int i = n - 2; i >= 0; --i) {
      postfixProduct[i] = postfixProduct[i + 1] * nums[i + 1];
    }

    int prefixProduct = nums[0];
    nums[0] = postfixProduct[0];
    for (int i = 1; i < n; ++i) {
      int temp = nums[i];
      nums[i] = prefixProduct * postfixProduct[i];
      prefixProduct *= temp;
    }
    return nums;
  }
};
