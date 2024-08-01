#include <algorithm>
#include <climits>
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
  int countSeniors(vector<string> &details) {
    int count = 0;

    for (string const &detail : details) {
      int age = (detail[11] - '0') * 10 + (detail[12] - '0');

      if (age > 60) {
        ++count;
      }
    }
    return count;
  }
};
