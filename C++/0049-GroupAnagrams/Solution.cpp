#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<std::string>> groupAnagrams(
      std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> groups;

    for (const std::string& s : strs) {
      std::string sorted = s;
      sort(sorted.begin(), sorted.end());

      groups[sorted].push_back(s);
    }

    std::vector<std::vector<std::string>> result;
    for (const auto& [key, group] : groups) {
      result.push_back(group);
    }

    return result;
  }
};
