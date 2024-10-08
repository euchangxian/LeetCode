#include <vector>

using namespace std;
class Solution {
 public:
  int minOperations(vector<string>& logs) {
    int operations = 0;
    for (string log : logs) {
      if (log.substr(0, 3) == "../") {
        operations = max(0, operations - 1);
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
