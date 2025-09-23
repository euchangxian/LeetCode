#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename Tuple, typename Callable, std::size_t... Indices>
auto forEachImpl(Tuple&& tuple,
                 Callable&& func,
                 std::index_sequence<Indices...>) {
  return (func(Indices, std::get<Indices>(tuple)), ...);
}

template <typename Tuple, typename Callable>
auto forEach(Tuple&& tuple, Callable&& func) {
  constexpr auto N = std::tuple_size_v<std::decay_t<Tuple>>;
  return forEachImpl(std::forward<Tuple>(tuple), std::forward<Callable>(func),
                     std::make_index_sequence<N>());
}

using Pattern =
    std::tuple<std::string_view, std::string_view, std::string_view>;

template <>
struct std::hash<Pattern> {
  std::size_t operator()(const Pattern& pattern) const {
    const auto h1 = std::hash<std::string_view>{}(std::get<0>(pattern));
    const auto h2 = std::hash<std::string_view>{}(std::get<1>(pattern));
    const auto h3 = std::hash<std::string_view>{}(std::get<2>(pattern));
    return h1 ^ (h2 << 1) ^ (h3 << 2);
  }
};

class Solution {
 public:
  std::vector<std::string> mostVisitedPattern(
      std::vector<std::string>& username,
      std::vector<int>& timestamp,
      std::vector<std::string>& website) {
    // (username[i], website[i], timestamp[i]) indicate that the ith user with
    // the username visited the website at timestamp.
    // A pattern is a list of three websites (not necessarily distinct)
    // The score of a pattern is the number of users that visited all the
    // website in the same order they occur in the pattern.
    // Return the pattern with the largest score.
    //
    // Hmmm.
    // Note the small constraints:
    // - 3<=N<=50
    // Therefore, enumerating all possible patterns will be O(N^3), then
    // checking for each possible pattern its score will be about O(N^4)
    // in total - for each user, count how many times the pattern exists.
    //
    // But note that we MUST visit in timestamp ascending order.
    // Suppose we sort our 3-tuple (username, website, timestamp) by their
    // timestamps, ascending.
    const auto n = static_cast<int>(username.size());

    // {username : {timestamp, website}}
    std::unordered_map<std::string_view, std::map<int, std::string_view>>
        userActivity;
    // {(w1, w2, w3): count}
    std::unordered_map<Pattern, int> freq;
    for (int i = 0; i < n; ++i) {
      userActivity[username[i]][timestamp[i]] = website[i];
    }

    int maxFreq = 0;
    Pattern maxPattern;
    for (const auto& [username, websiteVisited] : userActivity) {
      std::unordered_set<Pattern> seenPatterns;
      for (auto it1 = websiteVisited.begin(); it1 != websiteVisited.end();
           ++it1) {
        for (auto it2 = std::next(it1); it2 != websiteVisited.end(); ++it2) {
          for (auto it3 = std::next(it2); it3 != websiteVisited.end(); ++it3) {
            seenPatterns.emplace(it1->second, it2->second, it3->second);
          }
        }
      }

      for (const auto& pattern : seenPatterns) {
        auto currFreq = ++freq[pattern];
        if (currFreq > maxFreq) {
          maxFreq = freq[pattern];
          maxPattern = pattern;
        } else if (currFreq == maxFreq && pattern < maxPattern) {
          maxPattern = pattern;
        }
      }
    }

    std::vector<std::string> result(3);
    forEach(maxPattern, [&result](auto idx, std::string_view pattern) {
      result[idx] = std::string{pattern};
    });
    return result;
  }
};
