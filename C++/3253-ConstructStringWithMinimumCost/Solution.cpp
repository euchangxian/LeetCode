#include <algorithm>
#include <array>
#include <climits>
#include <string>
#include <string_view>
#include <vector>

struct Node {
  bool word{false};
  int cost{INT_MAX};
  std::array<Node*, 26> children{};
};

class Trie {
 public:
  Node* root;

  Trie() : root(new Node()) {}

  void insert(std::string_view word, int cost) {
    auto it = root;
    for (char c : word) {
      if (!it->children[c - 'a']) {
        it->children[c - 'a'] = new Node();
      }
      it = it->children[c - 'a'];
    }
    it->word = true;
    it->cost = std::min(it->cost, cost);
  }

  Node* next(Node* root, char c) const {
    auto it = root;
    if (!it->children[c - 'a']) {
      return nullptr;
    }
    return it->children[c - 'a'];
  }
};

class Solution {
 public:
  int minimumCost(std::string_view target,
                  std::vector<std::string>& words,
                  std::vector<int>& costs) {
    // Starting from an empty string s, perform any number of times:
    // - Pick a word from words
    // - append to string s with cost = costs[i]
    // Return minimum cost, or -1 if impossible.
    //
    // Feels DP-like/backtracking.
    // Note that words/costs.length <= 50
    //
    // Naively, pick a word, pop(or increment a pointer) the prefix matching
    // characters. Then, DFS to the next word.
    // DP[i] should be sufficient, representing the min cost to make up the
    // prefix of target[i].
    // Not simple too... Need to do substring comparisons.
    // A trie? Augmented with the minimum cost.
    Trie trie;
    for (int i = 0; i < words.size(); ++i) {
      trie.insert(words[i], costs[i]);
    }

    std::vector<int> memo(target.size(), INT_MAX);
    int minCost = dfs(trie, target, memo, 0);
    if (minCost == INT_MAX) {
      return -1;
    }
    return minCost;
  }

 private:
  int dfs(const Trie& trie,
          std::string_view target,
          std::vector<int>& memo,
          int idx) {
    if (idx >= target.size()) {
      return 0;
    }

    int& ans = memo[idx];
    if (ans != INT_MAX) {
      return ans;
    }

    Node* curr = trie.root;
    for (int i = idx; i < target.size(); ++i) {
      curr = trie.next(curr, target[i]);
      if (!curr) {
        break;
      }

      if (curr->word) {
        int cost = dfs(trie, target, memo, i + 1);
        if (cost != INT_MAX) {
          ans = std::min(ans, curr->cost + cost);
        }
      }
    }

    return ans;
  }
};
