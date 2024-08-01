#include <sstream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
public:
  bool isEnd;
  vector<TrieNode *> children;

  TrieNode() : children(26, nullptr) { isEnd = false; }
};

class Trie {
private:
  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode *current = root;
    for (char c : word) {
      if (current->children[c - 'a'] == nullptr) {
        current->children[c - 'a'] = new TrieNode();
      }
      current = current->children[c - 'a'];
    }
    current->isEnd = true;
  }

  string findShortestRoot(string word) {
    stringstream shortestRoot;
    TrieNode *current = root;
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
};

class Solution {
public:
  string replaceWords(vector<string> &dictionary, string sentence) {
    // add each root in the dictionary into the Trie
    Trie dictTrie;
    for (string word : dictionary) {
      dictTrie.insert(word);
    }

    stringstream resultStream;
    istringstream sentenceStream(sentence);

    string currWord;
    while (sentenceStream >> currWord) {
      string root = dictTrie.findShortestRoot(currWord);
      resultStream << root << " ";
    }
    string result = resultStream.str();
    result.pop_back(); // remove extra space
    return result;
  }
};
