#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int isPrefixOfWord(std::string_view sentence, std::string_view searchWord) {
    // Could split. Could also find ' ' to indicate new words.
    // iteratively find the whitespace, which also acts as the start of a new
    // word.
    int wordIdx = 1;  // we want to return the index of the WORD, 1-indexed.
    auto begin = sentence.begin();
    while (begin != sentence.end()) {
      auto whitespace = std::find(begin, sentence.end(), ' ');

      // may be end, may be whitespace, regardless, we have a new word from curr
      // to end
      std::string_view word = std::string_view{begin, whitespace};

      // C++17, using substr
      // bool isPrefix = word.size() >= searchWord.size() &&
      //                 word.substr(0, searchWord.size()) == searchWord;
      if (word.starts_with(searchWord)) {
        return wordIdx;
      }

      begin =
          std::min(sentence.end(), whitespace + 1);  // skip the ' ' character
      ++wordIdx;
    }

    return -1;
  }
};
