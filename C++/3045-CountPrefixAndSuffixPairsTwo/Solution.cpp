#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using i64 = long long;

struct Node {
  // Given that we want to insert a pair of characters, each representing the
  // corresponding (original, reversed) characters, there are 26*26
  // possibilities. Using a HashMap would work, but we can make it vastly more
  // efficient by using an array and using the formula:
  // given a pair of characters (orig, rev), where both are lowercase chars,
  // idx = ((orig - 'a')*26) + (rev - 'a')
  // However, Given the total number of words, this will encounter a Memory
  // Limit Exceeded...
  std::unordered_map<int, Node*> children;
  i64 count{};  // if 0, no words has this as prefix.
};

class Trie {
 public:
  Trie() : root(new Node{}) {}

  void insert(std::string_view word) {
    const int n = static_cast<int>(word.size());

    auto iter = root;
    for (int i = 0; i < word.size(); ++i) {
      int idx = ((word[i] - 'a') * 26) + word[n - 1 - i] - 'a';
      if (!iter->children[idx]) {
        iter->children[idx] = new Node{};
      }
      iter = iter->children[idx];
      ++iter->count;
    }
  }

  i64 countPrefix(std::string_view word) {
    const int n = static_cast<int>(word.size());
    auto iter = root;

    for (int i = 0; i < word.size(); ++i) {
      int idx = ((word[i] - 'a') * 26) + word[n - 1 - i] - 'a';
      if (!iter->children[idx]) {
        return 0;
      }

      iter = iter->children[idx];
    }
    return iter->count;
  }

 private:
  Node* root{};
};

class Solution {
 public:
  i64 countPrefixSuffixPairs(std::vector<std::string>& words) {
    // isPrefixAndSuffix(s1, s2) returns true if s1 is a prefix AND suffix of
    // s2.
    // Find all pairs (i, j) where isPrefixAndSuffix(words[i], words[j]) is
    // true.
    // Constraints are tighter. Brute force approach used in the first variant
    // will not work.
    // Trie? Counting prefixes can be done in O(NL) time.
    // Iterating from the back, since we want ordered pairs, check if the
    // current word is a prefix of any other already inserted words by checking
    // the trie-flag (we want to maintain a count of words that have that prefix
    // too).
    // For Suffixes, intuitively, reversing the words will work. This takes
    // O(NL) time to reverse every word.
    // However, this may result in double counting, if the original and reversed
    // words are inserted in the same trie.
    //
    // NOTE: saw the answer sort-of.
    // The original and reversed can be inserted in a zip(original, reverse)
    // manner into the trie. That way, counting is straightforward.
    Trie trie{};

    trie.insert(words.back());

    i64 count = 0LL;
    for (int i = static_cast<int>(words.size()) - 2; i >= 0; --i) {
      count += trie.countPrefix(words[i]);
      trie.insert(words[i]);
    }

    return count;
  }
};
