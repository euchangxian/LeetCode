#include <array>
#include <cstddef>
#include <string>
#include <vector>

using namespace std;
class Solution {
 public:
  bool makeEqual(vector<string>& words) {
    // Since there is no need to optimize the operations, rather than focusing
    // on the operations, focus on the property necessary to make all strings
    // equal. Simply count the number of characters. They must appear
    // words.size() * k, k >= 0 times.
    const size_t n = words.size();

    array<int, 26> occurence{};
    for (const string& word : words) {
      for (const char c : word) {
        ++occurence[c - 'a'];
      }
    }

    for (const int count : occurence) {
      if (count % n != 0) {
        return false;
      }
    }
    return true;
  }
};
