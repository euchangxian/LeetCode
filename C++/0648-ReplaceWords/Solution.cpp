#include <sstream>
#include <string>
#include <vector>

class TrieNode {
 public:
  bool isEnd;
  std::vector<TrieNode*> children;

  TrieNode() : children(26, nullptr) { isEnd = false; }
};

class Trie {
 public:
  Trie() { root = new TrieNode(); }

  void insert(std::string_view word) {
    TrieNode* current = root;
    for (char c : word) {
      if (current->children[c - 'a'] == nullptr) {
        current->children[c - 'a'] = new TrieNode();
      }
      current = current->children[c - 'a'];
    }
    current->isEnd = true;
  }

  std::string findShortestRoot(std::string word) {
    std::stringstream shortestRoot;
    TrieNode* current = root;
    for (char c : word) {
      if (current->children[c - 'a'] == nullptr) {
        return word;
      }

      current = current->children[c - 'a'];
      shortestRoot << c;

      if (current->isEnd) {
        return shortestRoot.str();
      }
    }
    return word;
  }

 private:
  TrieNode* root;
};

class Solution {
 public:
  std::string replaceWords(std::vector<std::string>& dictionary,
                           std::string sentence) {
    // add each root in the dictionary into the Trie
    Trie dictTrie;
    for (std::string word : dictionary) {
      dictTrie.insert(word);
    }

    std::stringstream resultStream;
    std::istringstream sentenceStream(sentence);

    std::string currWord;
    while (sentenceStream >> currWord) {
      std::string root = dictTrie.findShortestRoot(currWord);
      resultStream << root << " ";
    }
    std::string result = resultStream.str();
    result.pop_back();  // remove extra space
    return result;
  }
};
