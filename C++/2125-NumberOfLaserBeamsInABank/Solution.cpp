#include <algorithm>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  int numberOfBeams(std::vector<std::string>& bank) {
    // Binary string array bank, bank[i] represents the ith row.
    // bank[i][j] = '0' indicate that the cell is empty, '1' indicate there
    // is a security device.
    // There is a laser beam between two security device if:
    // - the two devices are on different rows, r1 < r2, and
    // - for each row r1 < i < r2, there are no security devices in the ith row.
    // Return the total number of laser beams.
    //
    // Hm. We can only form laser beams between adjacent rows.
    // i.e., a prevCount and a currCount.
    int result = 0;
    int prev = 0;
    for (std::string_view row : bank) {
      auto devices = std::ranges::count(row, '1');

      if (devices > 0) {
        result += std::exchange(prev, devices) * devices;
      }
    }
    return result;
  }
};
