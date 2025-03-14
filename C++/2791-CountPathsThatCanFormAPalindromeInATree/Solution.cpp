#include <string_view>
#include <unordered_map>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 countPalindromePaths(std::vector<int>& parent, std::string_view s) {
    // parent[i] is the parent of node i.
    // s[i] is the character assigned to the edge between i and parent[i].
    // ignore s[0].
    //
    // Return the number of pairs of nodes (u, v) such that u < v and the
    // characters assigned to edges on the path from u to v can be REARRANGED
    // to form a palindrome.
    //
    // Since we can rearrange arbitrarily, the condition for a palindrome is:
    // - the number of characters with odd frequencies is either 0 or 1.
    //
    // Hmm...
    // Frequency array at each node? But we can only count root-to-node, and
    // not node-to-node.
    // Also, we only need the parity of frequencies; we can reduce to using a
    // bitmask of size 26.
    // Then, we assign odd parities to ON bits, and use __builtin_popcount to
    // determine how many odd-frequencies are there.
    //
    // What if we start from the leaves and aggregate at parents?
    // Think a state needs to be maintained. i.e., DP.
    // Something like dp[i]=mask indicating the parity of characters from
    // root to node i.
    // Still doesnt help count node-to-node.
    // Maybe an O(N^2) iteration then? Constraints kinda suggest otherwise tho:
    // n <= 10e5.
    // Hmm. Can we do better for this?
    // Note that for a given mask/parity, there is only a valid path to another
    // mask/parity if the resultant XOR of the masks: mask1^mask2 results in
    // at most a single set bit.
    // Does this help?
    const int n = parent.size();

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
      adj[parent[i]].push_back(i);  // only root-to-leaf directed edge.
    }

    std::vector<int> masks(n, 0);
    std::unordered_map<int, int> count;  // {mask, count}
    count[0] = 1LL;
    return dfs(0, adj, s, masks, count, 0);
  }

 private:
  i64 dfs(int u,
          const std::vector<std::vector<int>>& adj,
          std::string_view s,
          std::vector<int>& masks,
          std::unordered_map<int, int>& count,
          int mask) {
    i64 result = 0;
    masks[u] = mask;
    for (int v : adj[u]) {
      int newMask = mask ^ (1 << (s[v] - 'a'));

      // Count identical masks.
      result += count[newMask];

      // check for existing masks that differ by exactly one bit,
      // i.e., palindromes with a single odd character.
      for (int bit = 0; bit < 26; ++bit) {
        int other = 1 << bit;
        if (count.contains(newMask ^ other)) {
          result += count[newMask ^ other];
        }
      }

      ++count[newMask];
      result += dfs(v, adj, s, masks, count, newMask);
    }
    return result;
  }
};
