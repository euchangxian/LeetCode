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
public:
  vector<int> plusOne(vector<int> &digits) {
    int n = digits.size();

    for (int i = n - 1; i >= 0; --i) {
      if (digits[i] < 9) {
        ++digits[i];
        return digits;
      }

      digits[i] = 0;
    }

    // This line will only be reached if all the original digits are 9
    vector<int> newDigits(n + 1, 0);
    newDigits[0] = 1;
    return newDigits;
  }
};
