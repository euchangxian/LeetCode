#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Only up to 10^8 is necessary
constexpr std::array<int, 9> powOfTen = []() {
  std::array<int, 9> result{};
  result[0] = 1;
  for (int i = 1; i < 9; ++i) {
    result[i] = result[i - 1] * 10;
  }
  return result;
}();

struct TrieNode {
  bool isEnd;
  std::array<std::unique_ptr<TrieNode>, 10> children;

  TrieNode() : children{}, isEnd{false} {}
};

class Trie {
private:
  // Shared instead of unique because an iterator needs to copy the pointer
  std::unique_ptr<TrieNode> root;

  // No need to handle x = 0. Constraints guarantee x is positive.
  inline int numDigits(const int x) const {
    return static_cast<int>(std::floor(std::log10(x)) + 1);
  }

public:
  Trie() : root(std::make_unique<TrieNode>()) {}

  void insert(const int x) {
    // No need to delete at the end of the function. Iter does not own the
    // pointer.
    TrieNode *iter{root.get()};

    const int n = numDigits(x);
    // Iterate from most significant, left-most digit to least significant.
    for (int i = n - 1; i >= 0; --i) {
      const int digit = (x / powOfTen[i]) % 10;

      if (!iter->children[digit]) {
        iter->children[digit] = std::make_unique<TrieNode>();
      }
      iter = iter->children[digit].get();
    }

    iter->isEnd = true;
  }

  int findLongestPrefix(const int y) const {
    int result{0};

    TrieNode *iter{root.get()};
    const int n = numDigits(y);
    for (int i = n - 1; i >= 0; --i) {
      const int digit = (y / powOfTen[i]) % 10;
      if (!iter->children[digit]) {
        break;
      }

      iter = iter->children[digit].get();
      ++result;
    }

    return result;
  }
};

using namespace std;
class Solution {
public:
  int longestCommonPrefix(vector<int> &arr1, vector<int> &arr2) {
    // positive integers in arr1 and arr2
    // Find largest common prefix all of pairs. At least O(nm) to compare
    // each element of arr1 to each element of arr2. isPrefix check should be
    // O(1) time, since each integer is only 32 bits long, or 9 digits long,
    // given the constraints 1 <= arr[i] <= 10^8
    // Can we do better than O(nm)?
    // Lexicographical order would allow us to compare prefixes quicker.
    Trie prefixes{};

    for (const int &num : arr1) {
      prefixes.insert(num);
    }

    int longestPrefix = 0;
    for (const int &num : arr2) {
      longestPrefix = std::max(longestPrefix, prefixes.findLongestPrefix(num));
    }

    return longestPrefix;
  }
};
