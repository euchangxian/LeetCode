#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> fullJustify(std::vector<std::string>& words,
                                       int maxWidth) {
    // Array of string words.
    // Take maxWidth characters in each line, and pad if necessary.
    // The extra ' ' to pad should be distributed as evenly as possible,
    // within the line.
    //
    // Hm. First, determine the words on each line. Then, determine how many
    // words are in each line, so we can determine the amount of padding to add.
    // math-y
    // Each word requires at least s.length + 1 characters, except for the last
    // in the line.
    //
    // i.e., 3 words => 2 spaces.
    // if maxWidth = 16, characters used = 10
    // remaining to pad is maxWidth-used = 6, to be distributed as evenly to
    // the spaces.
    // First, #remaining/#spaces gives us the minimum padding for each space.
    // Then, #remaining%#spaces gives us the extra padding for each space
    // starting from the left.

    // words.length<=300, words[i].length<=20
    std::vector<std::string> sentence;
    std::queue<int> buf;
    int i = 0;
    int currLen = 0;

    auto flushBuf = [&](bool isLastLine = false) {
      --currLen;  // to remove the extra natural space from the last word.
      std::string line;
      line.reserve(maxWidth);

      int remaining = maxWidth - currLen;
      int numWords = buf.size();
      if (isLastLine || numWords == 1) {
        // Justify-left
        while (!buf.empty()) {
          line += words[buf.front()];
          buf.pop();
          if (!buf.empty()) {
            line += ' ';
          }
        }
        line += std::string(remaining, ' ');
      } else {
        int spaces = std::max(numWords - 1, 1);
        //  does not include the natural space between words
        int minSpace = remaining / spaces;
        int extra = remaining % spaces;
        while (!buf.empty()) {
          line += std::move(words[buf.front()]);
          buf.pop();

          if (!buf.empty()) {
            line += std::string(1 + minSpace + (extra-- > 0 ? 1 : 0), ' ');
          }
        }
      }
      sentence.push_back(std::move(line));
      currLen = 0;
      return;
    };

    while (i < words.size()) {
      if (currLen + words[i].size() > maxWidth) {
        flushBuf();
      }
      buf.push(i);
      currLen += words[i].size() + 1;
      ++i;
    }

    flushBuf(true);
    return sentence;
  }
};
