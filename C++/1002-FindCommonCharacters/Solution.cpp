#include <climits>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  vector<string> commonChars(vector<string> &words) {
    vector<vector<int>> present =
        vector<vector<int>>(26, vector<int>(words.size(), 0));
    for (int i = 0; i < words.size(); ++i) {
      for (char c : words[i]) {
        ++present[c - 'a'][i];
      }
    }

    vector<string> result;
    for (int i = 0; i < present.size(); ++i) {
      int occurences = INT_MAX;
      for (int freq : present[i]) {
        occurences = min(occurences, freq);
      }
      // Not really convention to use _
      for (int _ = 0; _ < occurences; ++_) {
        // C++ char to string conversion is more cumbersome than expected...
        result.push_back(string(1, i + 'a'));
      }
    }
    return result;
  }
};
