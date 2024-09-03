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
  int getLucky(string s, int k) {

    string transformed;
    transformed.reserve(s.length());
    for (auto const &c : s) {
      int digits = (c - 'a' + 1);

      transformed += to_string(digits);
    }

    while (k--) {
      int sum = 0;
      for (auto const &c : transformed) {
        sum += c - '0';
      }
      transformed = to_string(sum);
    }
    return stoi(transformed);
  }
};
