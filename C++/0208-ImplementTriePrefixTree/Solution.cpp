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
class TrieNode {
 public:
  bool isWord;
  vector<TrieNode*> children;
  TrieNode() : isWord(false), children(26, nullptr) {}
};

class Trie {
 private:
  TrieNode* root;

 public:
  Trie() : root(new TrieNode()) {};

  void insert(string word) {
    TrieNode* iter = root;
    for (auto const& c : word) {
      if (!iter->children[c - 'a']) {
        iter->children[c - 'a'] = new TrieNode();
      }
      iter = iter->children[c - 'a'];
    }
    iter->isWord = true;
  }

  bool search(string word) {
    TrieNode* iter = root;
    for (auto const& c : word) {
      if (!iter->children[c - 'a']) {
        return false;
      }
      iter = iter->children[c - 'a'];
    }
    return iter->isWord;
  }

  bool startsWith(string prefix) {
    TrieNode* iter = root;
    for (auto const& c : prefix) {
      if (!iter->children[c - 'a']) {
        return false;
      }
      iter = iter->children[c - 'a'];
    }
    return true;
  }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 * word and prefix consists of only lowercase English letters
 */
