#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  int minOperations(std::vector<std::string>& logs) {
    int operations = 0;
    for (std::string log : logs) {
      if (log.substr(0, 3) == "../") {
        operations = std::max(0, operations - 1);
        continue;
      }
      if (log.substr(0, 2) == "./") {
        continue;
      }

      operations += 1;
    }

    return operations;
  }
};
