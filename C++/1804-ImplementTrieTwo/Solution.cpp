#include <array>
#include <memory>
#include <string_view>

struct Node {
  std::array<std::unique_ptr<Node>, 26> children{};
  int count{0};
  int end{0};
};

// We want to count number of prefixes, instead of just finding whether a prefix
// exists.
// Thus, augment TrieNode with a count.
class Trie {
 public:
  Trie() : root(new Node()) {}

  void insert(std::string_view word) {
    Node* it = root.get();
    for (char c : word) {
      if (!it->children[c - 'a']) {
        it->children[c - 'a'] = std::make_unique<Node>();
      }

      it = it->children[c - 'a'].get();
      ++it->count;
    }
    ++it->end;
  }

  // check end count
  int countWordsEqualTo(std::string_view word) {
    Node* it = root.get();
    for (char c : word) {
      if (!it->children[c - 'a']) {
        return 0;
      }
      it = it->children[c - 'a'].get();
    }

    return it->end;
  }

  int countWordsStartingWith(std::string_view prefix) {
    Node* it = root.get();
    for (char c : prefix) {
      if (!it->children[c - 'a']) {
        return 0;
      }
      it = it->children[c - 'a'].get();
    }

    return it->count;
  }

  // word must exist in the trie
  void erase(std::string_view word) {
    Node* it = root.get();
    for (char c : word) {
      // if (!it->children[c - 'a']) {
      //   return;
      // }
      it = it->children[c - 'a'].get();
      --it->count;
    }

    --it->end;
  }

 private:
  std::unique_ptr<Node> root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */
