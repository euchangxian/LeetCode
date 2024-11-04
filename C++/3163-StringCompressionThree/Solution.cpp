#include <cstddef>
#include <string>
#include <string_view>

using namespace std;
class Solution {
 public:
  std::string compressedString(std::string_view word) {
    // Compress, with the operation:
    // comp := ""
    // while not word.empty:
    //   replace consecutive occurences of c (up to 9) with digit + c
    // return comp
    std::string comp;
    comp.reserve(word.size() * 2);  // worst case, single chars

    int i = 0;
    while (i < word.size()) {
      int count = 0;
      char c = word[i];

      while (i < word.size() && word[i] == c && count < 9) {
        ++count;
        ++i;
      }

      comp += count + '0';
      comp += c;
    }
    return comp;
  }
};
