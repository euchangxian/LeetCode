#include <algorithm>
#include <array>
#include <bitset>
#include <vector>

constexpr int MAX_NM = 500;

class Solution {
 public:
  int minimumTeachings(int n,
                       std::vector<std::vector<int>>& languages,
                       std::vector<std::vector<int>>& friendships) {
    // n languages labelled 1 through n. m users.
    // languages[i] = set of languages ith user knows
    // friendships[i] = [u, v] indicate a symmetric friendship between u and v.
    // Choose ONE language and teach it to some users such that all friends can
    // communicate with each other.
    // Return the minimum number of users to teach.
    // Friendships are not transitive.
    //
    // Note the small constraints:
    // - 2 <= n <= 500
    // - 1 <= m <= 500
    // u can communicate with v if they share a common language, i.e.,
    // set intersection >= 1
    // Process each user's known language into a lookup table.
    // We can collect the list of problematic edges.
    // Then, for each user in the set, we collect the known most-languages,
    // teach those that dont know that language.
    const auto m = static_cast<int>(languages.size());

    std::vector<std::bitset<MAX_NM + 1>> knownLanguages(m);
    for (int i = 0; i < m; ++i) {
      for (int j : languages[i]) {
        knownLanguages[i][j] = 1;
      }
    }

    std::bitset<MAX_NM + 1> problematic;
    for (const auto& friendship : friendships) {
      const auto u = friendship[0] - 1;
      const auto v = friendship[1] - 1;

      if ((knownLanguages[u] & knownLanguages[v]).any()) {
        continue;
      }
      problematic[u] = 1;
      problematic[v] = 1;
    }

    int needToTeach = 0;
    int mostKnown = 0;
    std::array<int, MAX_NM + 1> frequency{};
    for (int i = 0; i < m; ++i) {
      if (problematic[i]) {
        ++needToTeach;
        for (int lang : languages[i]) {
          mostKnown = std::max(mostKnown, ++frequency[lang]);
        }
      }
    }
    return needToTeach - mostKnown;
  }
};
