#include <cstddef>
#include <string_view>

using namespace std;
class Solution {
 public:
  bool isCircularSentence(std::string_view sentence) {
    for (size_t i = 0; i < sentence.length(); ++i) {
      if (sentence[i] == ' ') {
        // space delimited marks the end of the previous word and the start of
        // the next word
        if (sentence[i - 1] != sentence[i + 1]) {
          return false;
        }
      }
    }

    // final check first character of the first word and last character of the
    // last word
    return sentence[0] == sentence.back();
  }
};
