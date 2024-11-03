#include <cstddef>
#include <string>
#include <string_view>

using namespace std;
class Solution {
 public:
  bool rotateString(std::string_view s, std::string_view goal) {
    // To determine if s can be rotated to become goal, simply check a fixed
    // sliding window of s.size = goal.size
    // Append copies of s to itself, such that the last character of s can
    // be the starting character of the goal.
    if (s.size() != goal.size()) {
      return false;
    }
    const size_t n = s.size();

    std::string str;
    str.reserve(2 * n - 1);
    str += s;
    str += s.substr(0, n - 1);

    // convert to a SV
    s = std::string_view(str.data(), str.size());

    // Alternate solution using std::string::find and std::string::npos
    // auto pos = s.find(goal);
    // return pos != std::string::npos;
    for (int i = 0; i + n <= str.size(); ++i) {
      if (s.substr(i, n) == goal) {
        return true;
      }
    }
    return false;
  }
};
