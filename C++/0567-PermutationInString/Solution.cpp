#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    if (s1.length() > s2.length()) {
      return false;
    }

    vector<int> s1Frequency(26, 0);
    vector<int> s2Frequency(26, 0);
    for (int i = 0; i < s1.length(); ++i) {
      ++s1Frequency[s1[i] - 'a'];
      ++s2Frequency[s2[i] - 'a'];
    }

    if (s1Frequency == s2Frequency) {
      return true;
    }

    for (int i = s1.length(); i < s2.length(); ++i) {
      --s2Frequency[s2[i - s1.length()] - 'a'];
      ++s2Frequency[s2[i] - 'a'];

      if (s1Frequency == s2Frequency) {
        return true;
      }
    }

    return false;
  }
};
