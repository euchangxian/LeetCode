#include <cstddef>
#include <cstdlib>
#include <ranges>
#include <string_view>

class Solution {
 public:
  bool canBeValid(std::string_view s, std::string_view locked) {
    // A valid parentheses string must have all '(' and ')' paired.
    // Given s and locked, where s.length == locked.length, and locked is a
    // binary string, where locked[i] == 1 means that s[i] can not be changed,
    // determine if s can be made a valid parentheses string.
    // ()))
    // 1011
    // Hm, optimal solution may involve changing already-paired parentheses.
    //
    // What would a naive solution look like?
    // O(n) check isValid
    // if not valid, recursively invert each unlocked parentheses, resulting
    // in a O(n * 2^n) runtime.
    // Okay. Monotonic-stack seems possible. Observe that for locked
    // parentheses, we can treat them as-is, '(' or ')', as they can never
    // change.
    // For unlocked parenthese, we can change them to whatever we need, i.e.,
    // encountering an unpaired ')'.
    // Thus, assign +1 to '(' and -1 to ')' (locked ones only).
    // Keep track of the number of prefix and suffix unlocked parentheses.
    // If the sum goes negative < 0, indicating there are unpaired ')', then
    // subtract from the prefix parentheses. Otherwise, subtract from suffix.
    // If either prefix/suffix are <0, then return false.
    if (s.size() & 1) {
      // early exit for odd length, can never pair.
      return false;
    }

    constexpr auto assignParentheses = [](char c) -> int {
      return c == '(' ? 1 : -1;
    };
    constexpr auto assignLocked = [](char c) -> bool { return c == '1'; };

    // map parentheses to integer values and locked to boolean.
    // First pass, check that any excess locked closed parentheses ')' can be
    // paired with unlocked.
    int balance = 0;
    int unlocked = 0;
    auto checkClosedPairs =
        std::views::zip(s | std::views::transform(assignParentheses),
                        locked | std::views::transform(assignLocked));
    for (const auto [type, isLocked] : checkClosedPairs) {
      if (!isLocked) {
        ++unlocked;
        continue;
      }

      balance += type;
      if (balance < 0) {
        if (unlocked <= 0) {
          // unable to change any previous parentheses to pair with this ')'.
          return false;
        }
        ++balance;
        --unlocked;
      }
    }

    // Second pass, check that any excess locked open parentheses '(' can be
    // paired with unlocked.
    balance = 0;
    unlocked = 0;
    auto checkOpenPairs = checkClosedPairs | std::views::reverse;
    for (const auto [type, isLocked] : checkOpenPairs) {
      if (!isLocked) {
        ++unlocked;
        continue;
      }

      balance += type;
      if (balance > 0) {
        if (unlocked <= 0) {
          return false;
        }
        --balance;
        --unlocked;
      }
    }
    return true;
  }
};
