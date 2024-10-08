#include <string>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<string> fizzBuzz(int n) {
    std::vector<string> result;
    result.reserve(n);
    for (int i = 1; i <= n; ++i) {
      std::string output;
      output.reserve(8);
      if (i % 3 == 0) {
        output += "Fizz";
      }
      if (i % 5 == 0) {
        output += "Buzz";
      }

      if (output.empty()) {
        output += std::to_string(i);
      }
      result.push_back(output);
    }
    return result;
  }
};
