#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * Since every ASCII character may occur, the key is to store a "header",
 * denoting the length of the string.
 * strs[i].length <= 200. Therefore, 3 bytes should be reserved for the header,
 * one for each digit, padded with zeros.
 */
class Codec {
 public:
  // Encodes a list of strings to a single string.
  std::string encode(std::vector<std::string>& strs) {
    std::ostringstream encoded;
    encoded << std::setfill('0');  // pad with leading '0's, persistent flag.

    for (const std::string& str : strs) {
      std::size_t n = str.length();
      encoded << std::setw(headerLength) << n << str;
    }

    return encoded.str();
  }

  // Decodes a single string to a list of strings.
  std::vector<std::string> decode(std::string s) {
    std::vector<std::string> decoded;
    std::size_t i = 0;
    while (i < s.length()) {
      int strLen = std::stoi(s.substr(i, headerLength));
      decoded.emplace_back(s.substr(i + headerLength, strLen));
      i += headerLength + strLen;
    }
    return decoded;
  }

 private:
  const std::size_t headerLength = 3;
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
