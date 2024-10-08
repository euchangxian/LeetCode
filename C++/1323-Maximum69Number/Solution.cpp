#include <algorithm>
#include <array>
#include <bitset>
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
  int maximum69Number(int num) {
    // Brute force solution is definitely trivial: Just convert num to a string
    // and greedily change the first '6' to a '9'
    // For the optimized solution,
    // the difficulty lies in extracting the most significant digit at each
    // iteration. Extracting the least significant digit is simple using
    // modulo.
    int leftMostSix = -1;

    int original = num;
    for (int i = 0; num > 0; ++i) {
      int digit = num % 10;
      num /= 10;

      if (digit == 6) {
        leftMostSix = i;
      }
    }

    // The key is 3 * pow(10, i). If there is no 6, then i will be negative.
    // Casting to an integer will give us 0. Therefore there will be no
    // changes to the original number.
    //
    // Otherwise, take the exponent which is equivalent to shifting the
    // digit to the i-th place. Multiplying by 3, then adding the result
    // to the original number is equivalent to changing the '6' to '9'
    // E.g. original = 9669. Then i = 2. pow(10, 2) = 100
    // 9669 + (3 * 100) = 9969
    return original + (3 * static_cast<int>(pow(10, leftMostSix)));
  }
};
