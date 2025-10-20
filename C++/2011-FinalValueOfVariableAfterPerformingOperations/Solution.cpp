#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  int finalValueAfterOperations(std::vector<std::string>& operations) {
    // ++x,x++ increases value of x by 1.
    // --x,x-- decreases value of x by 1.
    // Initially 0, return final value.
    int x = 0;
    for (std::string_view op : operations) {
      if (op.front() == '+' || op.back() == '+') {
        ++x;
      } else {
        --x;
      }
    }
    return x;
  }
};
