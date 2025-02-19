#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

class Solution {
 public:
  std::string getHappyString(int n, int k) {
    // A happy string is a string that:
    // - consists of only 'a', 'b', 'c'
    // - s[i] != s[i+1], i.e., adjacent characters are different.
    // Consider a list of happy strings, each of length n sorted in
    // lexicographical order. Return the kth string of the list.
    std::vector<std::string> result;
    result.reserve(k);
    std::string curr;
    dfs(n, k, result, curr);

    if (result.size() < k) {
      return "";
    }
    return result.back();
  }

 private:
  void dfs(const int n,
           const int k,
           std::vector<std::string>& result,
           std::string& curr) {
    if (result.size() >= k) {
      return;
    }
    if (curr.size() == n) {
      result.push_back(curr);
      return;
    }

    for (char c : {'a', 'b', 'c'}) {
      if (!curr.empty() && c == curr.back()) {
        continue;
      }

      curr += c;
      dfs(n, k, result, curr);
      curr.pop_back();
    }
  }
};
