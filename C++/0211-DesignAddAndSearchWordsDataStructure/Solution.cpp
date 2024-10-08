#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class WordDictionary {
 private:
  vector<WordDictionary*> children;
  bool isWord;

 public:
  WordDictionary() : isWord(false), children(26, nullptr) {}

  void addWord(string word) {
    WordDictionary* iter = this;
    for (auto const& c : word) {
      if (!iter->children[c - 'a']) {
        iter->children[c - 'a'] = new WordDictionary();
      }
      iter = iter->children[c - 'a'];
    }
    iter->isWord = true;
  }

  bool search(string word) {
    WordDictionary* iter = this;
    for (int i = 0; i < word.length(); ++i) {
      char c = word[i];

      if (c == '.') {
        bool hasWord = false;
        for (auto const& child : iter->children) {
          if (!child) {
            continue;
          }
          hasWord = hasWord || child->search(word.substr(i + 1));
        }
        return hasWord;
      }

      if (!iter->children[c - 'a']) {
        return false;
      }
      iter = iter->children[c - 'a'];
    }
    return iter->isWord;
  }
};
