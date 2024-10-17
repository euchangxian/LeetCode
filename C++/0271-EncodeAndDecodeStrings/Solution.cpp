#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
/**
 * Since every ASCII character may occur, the key is to store a "header",
 * denoting the length of the string.
 * strs[i].length <= 200. Therefore, 3 bytes should be reserved for the header,
 * one for each digit, padded with zeros.
 */
class Codec {
 private:
  const size_t headerLength = 3;

 public:
  // Encodes a list of strings to a single string.
  string encode(vector<string>& strs) {
    std::ostringstream encoded;
    encoded << std::setfill('0');  // pad with leading '0's, persistent flag.

    for (const string& str : strs) {
      size_t n = str.length();
      encoded << std::setw(headerLength) << n << str;
    }

    return encoded.str();
  }

  // Decodes a single string to a list of strings.
  vector<string> decode(string s) {
    vector<string> decoded;
    size_t i = 0;
    while (i < s.length()) {
      int strLen = stoi(s.substr(i, headerLength));
      decoded.emplace_back(s.substr(i + headerLength, strLen));
      i += headerLength + strLen;
    }
    return decoded;
  }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
