#include <vector>

class TrieNode {
 public:
  bool isWord;
  std::vector<TrieNode*> children;
  TrieNode() : isWord(false), children(26, nullptr) {}
};

class Trie {
 public:
  Trie() : root(new TrieNode()) {};

  void insert(std::string_view word) {
    TrieNode* iter = root;
    for (char c : word) {
      if (!iter->children[c - 'a']) {
        iter->children[c - 'a'] = new TrieNode();
      }
      iter = iter->children[c - 'a'];
    }
    iter->isWord = true;
  }

  bool search(std::string_view word) {
    TrieNode* iter = root;
    for (char c : word) {
      if (!iter->children[c - 'a']) {
        return false;
      }
      iter = iter->children[c - 'a'];
    }
    return iter->isWord;
  }

  bool startsWith(std::string_view prefix) {
    TrieNode* iter = root;
    for (char c : prefix) {
      if (!iter->children[c - 'a']) {
        return false;
      }
      iter = iter->children[c - 'a'];
    }
    return true;
  }

 private:
  TrieNode* root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 * word and prefix consists of only lowercase English letters
 */
