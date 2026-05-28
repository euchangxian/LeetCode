#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr int MAX_N = 1E4;
constexpr int INF = 1E9;

using LenAndIdx = std::pair<int, int>;

struct Node {
  // length, idx
  LenAndIdx lenIdx{INF, INF};
  std::array<int, 26> children;
  Node() { std::ranges::fill(children, -1); }
};

struct Trie {
  Trie() {
    nodes.reserve(MAX_N);
    nodes.emplace_back();
  }

  void insert(auto&& word, LenAndIdx lenIdx) {
    auto curr = 0;
    nodes[curr].lenIdx = std::min(nodes[curr].lenIdx, lenIdx);  // empty suffix
    for (auto c : word) {
      // we can use a reference here, and not worry about iterator invalidation
      // on vector resize, assuming we correctly reserve the vector capacity.
      auto next = nodes[curr].children[c - 'a'];
      if (next == -1) {
        next = static_cast<int>(nodes.size());
        nodes.emplace_back();

        nodes[curr].children[c - 'a'] = next;
      }
      curr = next;
      nodes[curr].lenIdx = std::min(nodes[curr].lenIdx, lenIdx);
    }
  }

  [[nodiscard]] int lcp(auto&& word) const {
    auto curr = 0;
    auto result = nodes[curr].lenIdx;
    for (auto c : word) {
      auto next = nodes[curr].children[c - 'a'];
      if (next == -1) {
        break;
      }
      curr = next;
      result = nodes[curr].lenIdx;
    }
    return result.second;
  }

  std::vector<Node> nodes;
};

class Solution {
 public:
  std::vector<int> stringIndices(std::vector<std::string>& wordsContainer,
                                 std::vector<std::string>& wordsQuery) {
    // For every wordsQuery[i], find a string from wordsContainer that has the
    // longest common suffix.
    // - tie-break by shorter length
    // - then earlier index.
    // Return ans[i] = index in wordsContainer.
    //
    // Hm. definitely need to preprocess suffix in some form.
    // Can we just transform this into a longest common prefix, by reversing
    // every string?
    // Then, build a Trie from wordsContainer.
    //
    // Doesn't seem too difficult. What am I missing?
    const auto n = static_cast<int>(wordsContainer.size());
    Trie trie{};
    for (auto i = 0; i < n; ++i) {
      std::string_view word = wordsContainer[i];
      trie.insert(word | std::views::reverse,
                  {static_cast<int>(word.size()), i});
    }

    std::vector<int> result;
    result.reserve(wordsQuery.size());
    for (std::string_view word : wordsQuery) {
      result.push_back(trie.lcp(word | std::views::reverse));
    }
    return result;
  }
};
