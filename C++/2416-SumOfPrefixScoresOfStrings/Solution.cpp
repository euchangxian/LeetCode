#include <array>
#include <string>
#include <vector>

struct TrieNode {
  bool isWord;
  int32_t count;
  std::array<TrieNode*, 26> children;

  TrieNode() : isWord(false), count(0), children{} {}
};

class Trie {
 private:
  TrieNode* root;

 public:
  Trie() : root(new TrieNode()) {}

  void insert(const std::string word) {
    TrieNode* iter = root;
    for (const char& c : word) {
      if (!iter->children[c - 'a']) {
        iter->children[c - 'a'] = new TrieNode();
      }

      iter = iter->children[c - 'a'];
      ++iter->count;
    }
    iter->isWord = true;
    return;
  }

  int countPrefixes(const std::string word) {
    TrieNode* iter = root;
    int count = 0;
    for (const char& c : word) {
      iter = iter->children[c - 'a'];
      count += iter->count;
    }
    return count;
  }
};

class Solution {
 public:
  std::vector<int> sumPrefixScores(const std::vector<std::string>& words) {
    Trie trie{};

    for (const std::string& word : words) {
      trie.insert(word);
    }

    const std::size_t n = words.size();
    std::vector<int> count(n);
    for (std::size_t i = 0; i < n; ++i) {
      count[i] = trie.countPrefixes(words[i]);
    }

    return count;
  }
};
