#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
  deque<string> split(const string& s, const char delimiter) {
    istringstream iss(s);

    deque<string> result;
    string token;
    while (getline(iss, token, delimiter)) {
      result.push_back(token);
    }
    return result;
  }

 public:
  bool areSentencesSimilar(const string& sentence1, const string& sentence2) {
    // Sentence: list of words that are separated by a single space.
    // Similar: if it is possible to insert an arbitrary sentence inside one
    // of the sentence such that the two sentences become equal.
    // The inserted sentence must be separated from existing words by spaces.
    //
    // This means that the existing sentence must have the same words.
    // Only one sentence can be inserted. I.e. the places where the words are
    // the same should either be at the front and/or the back.
    // I.e., A sentence can be seen as a concatenation of a prefix and suffix
    // from the other sentence.
    deque<string> words1 = split(sentence1, ' ');
    deque<string> words2 = split(sentence2, ' ');

    // Compare prefixes
    while (!words1.empty() && !words2.empty() &&
           words1.front() == words2.front()) {
      words1.pop_front();
      words2.pop_front();
    }

    // Compare suffixes
    while (!words1.empty() && !words2.empty() &&
           words1.back() == words2.back()) {
      words1.pop_back();
      words2.pop_back();
    }

    return words1.empty() || words2.empty();
  }
};
