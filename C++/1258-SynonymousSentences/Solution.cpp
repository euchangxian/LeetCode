#include <cstddef>
#include <cstdlib>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class UnionFind {
 public:
  void add(std::string_view x) {
    if (parent_.find(x) == parent_.end()) {
      parent_[x] = x;
      rank_[x] = 0;
    }
  }

  std::string_view find(std::string_view x) {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }
    return parent_[x];
  }

  bool connected(std::string_view x, std::string_view y) {
    return find(x) == find(y);
  }

  void unite(std::string_view x, std::string_view y) {
    add(x);
    add(y);
    std::string_view px = find(x);
    std::string_view py = find(y);

    if (px == py) {
      return;
    }

    // Union by rank_
    if (rank_[px] < rank_[py]) {
      parent_[px] = py;
    } else if (rank_[px] > rank_[py]) {
      parent_[py] = px;
    } else {
      parent_[py] = px;
      rank_[px]++;
    }
  }

 private:
  std::unordered_map<std::string_view, std::string_view> parent_;
  std::unordered_map<std::string_view, int> rank_;
};

class Solution {
 public:
  std::vector<std::string> generateSentences(
      std::vector<std::vector<std::string>>& synonyms,
      std::string_view text) {
    // synonyms[i] = {u, v} => word u is synonym of word v.
    // Graphy-like question.
    // For each word in the text, replace it with its neighbours and output it.
    // Could use an adjacency list?
    // Need UF to model transitive relationships.
    UnionFind uf;
    std::unordered_set<std::string_view> distinct;
    for (const auto& edge : synonyms) {
      distinct.insert(edge[0]);
      distinct.insert(edge[1]);
      uf.unite(edge[0], edge[1]);
    }

    std::unordered_map<std::string_view, std::vector<std::string_view>> adj;
    for (std::string_view word1 : distinct) {
      for (std::string_view word2 : distinct) {
        if (word1 == word2) {
          continue;
        }
        if (uf.connected(word1, word2)) {
          adj[word1].push_back(word2);
        }
      }
    }

    // DFS/backtrack.
    std::vector<std::string> words = split(text);
    std::set<std::string> sentences;

    dfs(adj, sentences, words, 0);
    return {sentences.begin(), sentences.end()};
  }

 private:
  void dfs(const std::unordered_map<std::string_view,
                                    std::vector<std::string_view>>& adj,
           std::set<std::string>& sentences,
           std::vector<std::string>& words,
           int i) {
    if (i >= words.size()) {
      sentences.insert(join(words));
      return;
    }

    auto it = adj.find(words[i]);
    if (it != adj.end()) {
      std::string original = std::move(words[i]);
      for (std::string_view next : it->second) {
        words[i] = std::string(next);
        dfs(adj, sentences, words, i + 1);
      }
      words[i] = std::move(original);
    }

    dfs(adj, sentences, words, i + 1);
  }

  std::vector<std::string> split(std::string_view text) {
    std::vector<std::string> words;
    for (auto word : text | std::ranges::views::split(' ')) {
      words.push_back(std::string{word.begin(), word.end()});
    }
    return words;
  }

  std::string join(std::vector<std::string>& words) {
    std::ostringstream oss;
    for (int i = 0; i < words.size() - 1; ++i) {
      oss << words[i] << ' ';
    }
    oss << words.back();
    return oss.str();
  }
};
