#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void splitAndCount(const string &s, const char &delimiter,
                   unordered_map<string, int> &frequency) {
  stringstream ss(s);

  string token;
  while (getline(ss, token, delimiter)) {
    ++frequency[token];
  }
}

class Solution {
public:
  vector<string> uncommonFromSentences(string s1, string s2) {
    unordered_map<string, int> frequency;
    splitAndCount(s1, ' ', frequency);
    splitAndCount(s2, ' ', frequency);

    vector<string> result;
    result.reserve(frequency.size());
    for (auto const &[word, freq] : frequency) {
      if (freq == 1) {
        result.push_back(word);
      }
    }
    return result;
  }
};
