#include <string>
#include <vector>

class Solution {
 public:
  bool phonePrefix(std::vector<std::string>& numbers) {
    // Return true if no phone number is a prefix of any other phone number.
    // This is "easy" because the constraints are small: n <= 50
    for (int i = 0; i < numbers.size(); ++i) {
      for (int j = 0; j < numbers.size(); ++j) {
        if (i == j) {
          continue;
        }
        if (numbers[j].starts_with(numbers[i])) {
          return false;
        }
      }
    }
    return true;
  }
};
