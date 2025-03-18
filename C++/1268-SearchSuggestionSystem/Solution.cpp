#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

class Trie {
 public:
  Trie() : root(new Node()) {}

  void insert(std::string_view str) {
    Node* iter = root;
    for (char c : str) {
      if (!iter->children[c - 'a']) {
        iter->children[c - 'a'] = new Node();
      }
      iter = iter->children[c - 'a'];
    }
    iter->isWord = true;
  }

  // return the 3 lexicographically minimum strings with the given prefix.
  std::vector<std::string> search(std::string_view prefix) {
    // First, iterate through to match the prefix.
    Node* iter = root;
    for (char c : prefix) {
      if (!iter->children[c - 'a']) {
        // if there is nothing matching the prefix, then return early.
        return {};
      }
      iter = iter->children[c - 'a'];
    }

    // At this point, iter will be at the "root" of the search tree. DFS down
    std::vector<std::string> matches;
    matches.reserve(3);

    std::string baseWord = std::string(prefix);
    dfs(matches, baseWord, iter);

    return matches;
  }

 private:
  struct Node {
    bool isWord{false};
    std::array<Node*, 26> children{};
  };

  Node* root{};

  void dfs(std::vector<std::string>& matches, std::string& word, Node* iter) {
    if (matches.size() >= 3) {
      // prune and return early
      return;
    }

    if (iter->isWord) {
      matches.push_back(word);
    }

    for (int i = 0; i < 26; ++i) {
      if (iter->children[i]) {
        word += (i + 'a');
        dfs(matches, word, iter->children[i]);
        word.pop_back();  // backtrack
      }
    }
  }
};

class Solution {
 public:
  std::vector<std::vector<std::string>> suggestedProducts(
      std::vector<std::string>& products,
      std::string_view searchWord) {
    std::sort(products.begin(), products.end());

    std::vector<std::vector<std::string>> suggestions;
    suggestions.reserve(searchWord.size());

    auto startIter = products.begin();
    for (int len = 1; len <= searchWord.size(); ++len) {
      std::vector<std::string> matches;
      matches.reserve(3);

      std::string_view prefix = searchWord.substr(0, len);

      // Seach for the first 3 words that matches the prefix, i.e., >= prefix.
      auto it = std::lower_bound(startIter, products.end(), prefix);
      for (int i = 0; i < 3 && it + i != products.end(); ++i) {
        std::string& s = *(it + i);

        // Check if the current string has the prefix using std::string::compare
        // which returns a non-zero value if the compared string and comparing
        // string is non-equal. <0 if compared string is lexicographically
        // smaller (non-matching char is smaller, or s is shorter), >0 otherwise
        if (s.compare(0, prefix.size(), prefix) != 0) {
          break;
        }
        matches.push_back(s);
      }

      suggestions.push_back(std::move(matches));
      startIter = it;  // shrink the search range for subsequent searches.
    }
    return suggestions;
  }

  std::vector<std::vector<std::string>> suggestedProductsTrie(
      std::vector<std::string>& products,
      std::string searchWord) {
    // Given array of products, and target word.
    // Suggest at most three products after each character of the searchWord is
    // typed. Suggested products should have common prefix.
    // Return the three lexicographically minimum.
    // Prefixes => Trie
    // Essentially, initialize the Trie with all the products inserted.
    // Then traverse the Trie character-by-character of the searchWord, using
    // a DFS with the current character as the root of this DFS.
    // This also handles our lexicographically minimum requirement.
    // Time Complexity:
    // Suppose n products, each product has length L. searchWord is also L.
    // Then, building the Trie will take us O(nL) time.
    // DFS-ing the Tree will take us O(L * (26 * L)) == O(L^2) time.
    // Insert each product into the Trie
    Trie prefixes;
    for (std::string_view product : products) {
      prefixes.insert(product);
    }

    std::vector<std::vector<std::string>> suggestions;
    suggestions.reserve(searchWord.size());

    // Convert searchWord to a string_view, allowing cheap substr operations.
    std::string_view target{searchWord.data(), searchWord.size()};
    for (int len = 1; len <= searchWord.size(); ++len) {
      suggestions.emplace_back(prefixes.search(target.substr(0, len)));
    }
    return suggestions;
  }
};
