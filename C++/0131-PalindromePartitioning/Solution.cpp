#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> partitions = getPalindromicPartitions(s);
    return partitions;
  }

private:
  vector<vector<string>> getPalindromicPartitions(string s) {
    vector<vector<string>> partitions;
    vector<string> currPartition;

    getPartitions(s, partitions, currPartition, 0);
    return partitions;
  }

  void getPartitions(string s, vector<vector<string>> &partitions,
                     vector<string> &curr, int start) {
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

  bool isPalindrome(string const &s, int left, int right) {
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

int main() {
  auto partitions = Solution().partition("aab");
  for (auto part : partitions) {
    for (auto c : part) {
      cout << c << ", ";
    }
    cout << endl;
  }
}
