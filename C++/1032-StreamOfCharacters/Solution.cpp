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

// Very very interesting.
// First naive idea: maintain a pointer to each of the initial words.
// If an incoming letter matches any of the pointer, increment that respective
// pointer.
// Otherwise, reset the pointer.
//
// This is essentially an O(N) check for each query, resulting in a total
// of O(NQ).
// Not too bad, considering N<=2000, Q<=4*10'000
//
// Can we do better though?
class StreamChecker {
 public:
  StreamChecker(std::vector<std::string>& words) {}

  bool query(char letter) {}
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
