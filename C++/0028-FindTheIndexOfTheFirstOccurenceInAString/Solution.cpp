#include <string_view>

class Solution {
 public:
  int strStr(std::string_view haystack, std::string_view needle) {
    // Return the index of the first occurence of needle in haystack or -1.
    auto idx = haystack.find(needle);
    if (idx == std::string_view::npos) {
      return -1;
    }
    return idx;
  }
};
