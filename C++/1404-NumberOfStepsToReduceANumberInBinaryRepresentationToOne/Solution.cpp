#include <iostream>
#include <string>

using namespace std;
class Solution {
 public:
  // even => divide by 2 / right shift
  // odd => add 1, next step will right shift
  // 110, 11, 100, 10, 1
  // 1001, 1010, 101, 110, 11, 100, 10, 1
  // the goal is to have all 1s remaining in the string => every operation will
  // be a right shift until the leading 1 is reached.
  // The key insight is that the 'carry' will always be present after a '1' is
  // encountered.
  int numSteps(string s) {
    int count = 0;
    int carry = 0;
    for (int i = s.length() - 1; i > 0; --i) {
      int current = s[i] - '0';
      if ((current + carry) % 2 == 0) {
        ++count;
      } else {
        count += 2;
        carry = 1;
      }
    }
    return count + carry;
  }
};

int main() {
  cout << Solution().numSteps("1101") << endl;
  cout << Solution().numSteps("10") << endl;
  cout << Solution().numSteps("1") << endl;
}
