#include <algorithm>
#include <iterator>
#include <limits>
#include <ranges>
#include <utility>
#include <vector>

constexpr int MAX_POTION_VAL = 1E5;

class Solution {
 public:
  std::vector<int> successfulPairs(std::vector<int>& spells,
                                   std::vector<int>& potions,
                                   long long success) {
    const auto n = static_cast<int>(spells.size());

    int maxPotion = std::numeric_limits<int>::min();
    std::array<int, MAX_POTION_VAL + 1> freq{};
    for (auto x : potions) {
      ++freq[x];
      maxPotion = std::max(maxPotion, x);
    }

    for (int x = maxPotion - 1; x >= 0; --x) {
      freq[x] += freq[x + 1];
    }

    std::vector<int> pairs;
    pairs.reserve(n);
    for (long long spell : spells) {
      auto minStrength = (success + spell - 1) / spell;
      if (minStrength > maxPotion) {
        pairs.emplace_back(0);
      } else {
        pairs.emplace_back(freq[minStrength]);
      }
    }

    return pairs;
  }

  std::vector<int> successfulPairsTwoPointer(std::vector<int>& spells,
                                             std::vector<int>& potions,
                                             long long success) {
    const auto n = static_cast<int>(spells.size());
    const auto m = static_cast<int>(potions.size());

    std::vector<std::pair<int, long long>> sortedSpells;
    sortedSpells.reserve(n);
    for (int i = 0; i < n; ++i) {
      sortedSpells.emplace_back(i, spells[i]);
    }

    std::ranges::sort(sortedSpells, {}, &std::pair<int, long long>::second);
    std::ranges::sort(potions);

    auto j = m - 1;
    std::vector<int> pairs(n);
    for (const auto [i, spell] : sortedSpells) {
      while (j >= 0 && spell * potions[j] >= success) {
        --j;
      }
      pairs[i] = m - (j + 1);
    }

    return pairs;
  }

  std::vector<int> successfulPairsBinarySearch(std::vector<int>& spells,
                                               std::vector<int>& potions,
                                               long long success) {
    // spells[i] represent the strength of the ith spell.
    // potions[j[] represent the strength of the jth potion.
    // A spell-potion pair is successful if their product is at least success.
    // Return pairs such that pairs[i] is the number of potions that can form
    // a successful pair with the ith spell.
    //
    // spells[i] * potions[j] >= success
    // potions[j] >= success/spells[i]
    //
    // At a glance, seems like sorting potions, then Binary Search for each
    // spell[i].
    // Can we do better?
    //
    // Asymptotically no. But we can sort both spells and potions, and use a
    // two-pointer approach, i.e., an amortized O(1) time for each spells[i],
    // which takes longer since two sorting process are required.
    const auto n = static_cast<int>(spells.size());

    std::vector<int> pairs;
    pairs.reserve(n);
    std::ranges::sort(potions);
    for (long long spell : spells) {
      // ceil div
      auto minStrength = (success + spell - 1) / spell;
      auto it = std::ranges::lower_bound(potions, minStrength);
      pairs.emplace_back(std::ranges::distance(it, std::ranges::end(potions)));
    }

    return pairs;
  }
};
