#include <string>
#include <vector>

class Solution {
 public:
  int countSeniors(std::vector<std::string>& details) {
    int count = 0;

    for (const std::string& detail : details) {
      int age = (detail[11] - '0') * 10 + (detail[12] - '0');

      if (age > 60) {
        ++count;
      }
    }
    return count;
  }
};
