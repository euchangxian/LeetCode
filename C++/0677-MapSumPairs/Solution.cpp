#include <array>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

struct Node {
  std::array<std::unique_ptr<Node>, 26> children{};
  int sum{0};
  bool end{false};
};

class Trie {
 public:
  Trie() : root(std::make_unique<Node>()) {}

  void insert(std::string_view word, int val) {
    auto it = root.get();
    for (char c : word) {
      if (!it->children[c - 'a']) {
        it->children[c - 'a'] = std::make_unique<Node>();
      }
      it = it->children[c - 'a'].get();
      it->sum += val;
    }
    it->end = true;
  }

  int prefix(std::string_view prefix) const {
    auto it = root.get();
    for (char c : prefix) {
      if (!it->children[c - 'a']) {
        return 0;
      }
      it = it->children[c - 'a'].get();
    }
    return it->sum;
  }

 private:
  std::unique_ptr<Node> root;
};

// 1. Map a string key to a given value.
// 2. Return the sum of values that have a key with a prefix equal to the
//    given string.
// Requirement 1 can be satisfied with a HashMap. Requirement 2, a Trie.
// Though, it is possible that an Ordered Map can be used.
//
// A Trie is simpler. Augment each TreeNode with a sum.
class MapSum {
 public:
  MapSum() : trie{} {}

  void insert(std::string key, int val) {
    if (auto it = mp.find(key); it != mp.end()) {
      // get the difference to adjust the duplicate key's value
      val = val - std::exchange(it->second, val);
    } else {
      mp.emplace(key, val);
    }
    trie.insert(key, val);
  }

  int sum(std::string_view prefix) { return trie.prefix(prefix); }

 private:
  std::unordered_map<std::string, int> mp;
  Trie trie;
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
