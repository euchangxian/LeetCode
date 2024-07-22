#include <algorithm>
#include <vector>

using namespace std;
class Solution {
public:
  int maxScoreWords(vector<string> &words, vector<char> &letters,
                    vector<int> &score) {
    vector<int> lettersCount = vector<int>(score.size(), 0);
    for (char c : letters) {
      lettersCount[c - 'a']++;
    }

    vector<int> wordScores = vector<int>(words.size(), 0);
    vector<vector<int>> wordLetterFreq = vector<vector<int>>(words.size());
    for (const string &word : words) {
      int wordScore = 0;
      vector<int> lettersFreq = vector<int>(score.size(), 0);
      for (const char &c : word) {
        wordScore += score[c - 'a'];
        lettersFreq[c - 'a']++;
      }
      wordScores.push_back(wordScore);
      wordLetterFreq.push_back(lettersFreq);
    }

    int maxScore =
        getMaxScore(words, lettersCount, wordScores, wordLetterFreq, 0);
    return maxScore;
  }

private:
  int getMaxScore(vector<string> const &words, vector<int> &count,
                  vector<int> const &wordScores,
                  vector<vector<int>> const &wordLetterCount, int idx) {}
};
