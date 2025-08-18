#include <cmath>
#include <vector>

constexpr double EPSILON = 1E-6;

class Solution {
 public:
  bool judgePoint24(std::vector<int>& cards) {
    // Given integer array cards of length 4.
    // card[i] = [1..9]
    // Arrange the numbers in an expression using the BINARY operators +-*/, and
    // parentheses () to get the value 24.
    // Return true if possible, false if not.
    //
    // Constraints look like a complete-search.
    // Parentheses complicates the choices available to us.
    //
    // Hm. From another perspective, we can abstract, by picking two numbers,
    // performing an operation on them, then placing the result back.
    // Our choices become: ((4*3) * 4) * ((3*2)*4) * ((2*1)*4)
    // => 4^3 * 4! * 3!
    std::vector<double> intermediate(cards.begin(), cards.end());

    auto getPossible = [](double a, double b) {
      std::vector<double> result{a + b, a - b, b - a, a * b};
      if (a != 0.0) {
        result.push_back(b / a);
      }

      if (b != 0.0) {
        result.push_back(a / b);
      }

      return result;
    };

    auto dfs = [&getPossible](this auto&& dfs,
                              std::vector<double>& cards) -> bool {
      if (cards.size() == 1) {
        return std::fabs(24 - cards[0]) < EPSILON;
      }
      for (int i = 0; i < cards.size(); ++i) {
        for (int j = i + 1; j < cards.size(); ++j) {
          // operate and recurse
          std::vector<double> next;
          for (int k = 0; k < cards.size(); ++k) {
            if (k == i || k == j) {
              continue;
            }
            next.emplace_back(cards[k]);
          }

          for (auto possible : getPossible(cards[i], cards[j])) {
            next.emplace_back(possible);

            if (dfs(next)) {
              return true;
            }
            next.pop_back();
          }
        }
      }
      return false;
    };
    return dfs(intermediate);
  }
};
