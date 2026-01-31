#include <algorithm>
#include <vector>

class Solution {
 public:
  char nextGreatestLetter(std::vector<char>& letters, char target) {
    // letters sorted in non-decreasing order, and a target char.
    // There are at least two different characterse in letters.
    // Return the smallest character in letters that is larger than target,
    // or the first character.
    //
    // Binary Search
    auto it = std::upper_bound(letters.begin(), letters.end(), target);
    return it == letters.end() ? letters.front() : *it;
  }
};
