#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::string kthDistinct(std::vector<std::string>& arr, int k) {
    if (k > arr.size()) {
      return "";
    }

    std::unordered_map<std::string, int> freq;
    for (const std::string& s : arr) {
      ++freq[s];
    }

    for (const std::string& s : arr) {
      if (freq[s] == 1 && --k == 0) {
        return s;
      }
    }
    return "";
  }
};
