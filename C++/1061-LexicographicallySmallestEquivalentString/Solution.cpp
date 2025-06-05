#include <array>
#include <ranges>
#include <string>
#include <string_view>

class UnionFind {
 public:
  UnionFind() : rank{} {
    for (char c = 'a'; c <= 'z'; ++c) {
      parent[c] = c;
      smallest[c] = c;
    }
  }

  char find(char c) {
    if (parent[c] != c) {
      parent[c] = find(parent[c]);
    }
    return parent[c];
  }

  bool connected(char x, char y) { return find(x) == find(y); }

  void unite(char x, char y) {
    char rootX = find(x);
    char rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    if (smallest[rootX] < smallest[rootY]) {
      smallest[rootY] = smallest[rootX];
    } else {
      smallest[rootX] = smallest[rootY];
    }

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
      return;
    }

    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
    parent[rootY] = rootX;
  };

  char smallestEquivalent(char c) { return smallest[find(c)]; }

 private:
  std::array<int, 256> parent;
  std::array<int, 256> rank;
  std::array<int, 256> smallest;
};

class Solution {
 public:
  std::string smallestEquivalentString(std::string_view s1,
                                       std::string_view s2,
                                       std::string_view baseStr) {
    // s1.length == s2.length
    // s1[i] and s2[i] are said to be equivalent characters.
    // Equivalent characters:
    // - reflexivity
    // - symmetry
    // - transitivity
    // Return the lexicographically smallest equivalent string of baseStr,
    // given s1 and s2.
    // Seems like building an graph G, where the nodes are characters.
    // Connect characters by a bidirectional edge for each s1[i], s2[i]
    // Then, we can find the lexicographically smallest character for each
    // character, and greedily assign to characters in the base string.
    // This seems to be Union Find? Where we do not care about the distance,
    // but only whether they are "equivalent".
    // We can augment the DSU to maintain the lexicographically smallest
    // character in each group.
    UnionFind G;
    for (auto [c1, c2] : std::views::zip(s1, s2)) {
      G.unite(c1, c2);
    }

    std::string result;
    result.reserve(baseStr.size());
    for (char c : baseStr) {
      result += G.smallestEquivalent(c);
    }
    return result;
  }
};
