#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
struct TrieNode {
  bool isWord;
  int32_t count;
  std::array<TrieNode *, 26> children;

  TrieNode() : isWord(false), count(0), children{} {}
};

class Trie {
private:
  TrieNode *root;

public:
  Trie() : root(new TrieNode()) {}

  void insert(const std::string word) {
    TrieNode *iter = root;
    for (const char &c : word) {
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
    TrieNode *iter = root;
    int count = 0;
    for (const char &c : word) {
      iter = iter->children[c - 'a'];
      count += iter->count;
    }
    return count;
  }
};

class Solution {
private:
public:
  vector<int> sumPrefixScores(const vector<string> &words) {
    Trie trie{};

    for (const std::string &word : words) {
      trie.insert(word);
    }

    const size_t n = words.size();
    std::vector<int> count(n);
    for (size_t i = 0; i < n; ++i) {
      count[i] = trie.countPrefixes(words[i]);
    }

    return count;
  }
};
