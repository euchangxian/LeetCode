#include <string_view>
#include <vector>

class WordDictionary {
 private:
  std::vector<WordDictionary*> children;
  bool isWord;

 public:
  WordDictionary() : isWord(false), children(26, nullptr) {}

  void addWord(std::string_view word) {
    WordDictionary* iter = this;
    for (char c : word) {
      if (!iter->children[c - 'a']) {
        iter->children[c - 'a'] = new WordDictionary();
      }
      iter = iter->children[c - 'a'];
    }
    iter->isWord = true;
  }

  bool search(std::string_view word) {
    WordDictionary* iter = this;
    for (int i = 0; i < word.length(); ++i) {
      char c = word[i];

      if (c == '.') {
        bool hasWord = false;
        for (const auto& child : iter->children) {
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
