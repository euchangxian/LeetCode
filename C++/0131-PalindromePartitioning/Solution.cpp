#include <vector>

class Solution {
 public:
  std::vector<std::vector<std::string>> partition(std::string s) {
    std::vector<std::vector<std::string>> partitions =
        getPalindromicPartitions(s);
    return partitions;
  }

 private:
  std::vector<std::vector<std::string>> getPalindromicPartitions(
      std::string s) {
    std::vector<std::vector<std::string>> partitions;
    std::vector<std::string> currPartition;

    getPartitions(s, partitions, currPartition, 0);
    return partitions;
  }

  void getPartitions(std::string s,
                     std::vector<std::vector<std::string>>& partitions,
                     std::vector<std::string>& curr,
                     int start) {
    if (start >= s.length()) {
      partitions.push_back(curr);
      return;
    }
    for (int end = start; end < s.size(); ++end) {
      if (isPalindrome(s, start, end)) {
        curr.push_back(s.substr(start, end - start + 1));
        getPartitions(s, partitions, curr, end + 1);
        curr.pop_back();
      }
    }
  }

  bool isPalindrome(const std::string& s, int left, int right) {
    while (left < right) {
      if (s[left] != s[right]) {
        return false;
      }
      ++left;
      --right;
    }
    return true;
  }
};
