#include <cstddef>
#include <string>
#include <string_view>

class Solution {
 private:
  std::string runLengthEncode(std::string_view s) {
    std::string encoded;

    // worst case all distinct characters
    encoded.reserve(2 * s.length());

    int count = 1;
    for (size_t i = 1; i < s.length(); ++i) {
      if (s[i] == s[i - 1]) {
        ++count;
        continue;
      }
      encoded.push_back(count + '0');
      encoded.push_back(s[i - 1]);
      count = 1;
    }

    encoded.push_back(count + '0');
    encoded.push_back(s.back());
    return encoded;
  }

 public:
  std::string countAndSay(int n) {
    // Given the recursive relation:
    // countAndSay(1) = "1"
    // countAndSay(n) = RLE(countAndSay(n-1))
    // where RLE (Run-Length Encoding) replaces consecutive characters (1 or
    // more in this problem) with the concatenation of the length of the
    // sequence and the character. E.g. "1" becomes "11", "111" becomes "31".
    if (n == 1) {
      return "1";
    }

    return runLengthEncode(countAndSay(n - 1));
  }
};
