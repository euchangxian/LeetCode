#include <algorithm>
#include <array>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

constexpr std::array<std::string_view, 4> VALID_BUSINESS_LINES{{
    "electronics",
    "grocery",
    "pharmacy",
    "restaurant",
}};

class Solution {
 public:
  std::vector<std::string> validateCoupons(
      std::vector<std::string>& code,
      std::vector<std::string>& businessLine,
      std::vector<bool>& isActive) {
    // n coupons.
    // code[i]: coupon identifier
    // businessLines[i]: business category of coupon i
    // isActive[i]: active status
    // A coupon is valid if:
    // - code[i] is non-empty and consists only alphanumeric and underscores.
    // - businessLine[i] = "electronics"|"grocery"|"pharmacy"|"restaurant"
    // - isActive[i]  = true
    //
    // Return an array of codes of all valid coupons, sorted by their
    // businessLine in the order: electronics->grocery->pharmacy->restaurant
    // and then by code in lexicographically ascending order within each
    // category.
    const auto n = static_cast<int>(code.size());
    auto active = [&isActive](int i) { return isActive[i]; };

    auto validBusinessLine = [&businessLine](int i) {
      return std::ranges::contains(VALID_BUSINESS_LINES, businessLine[i]);
    };

    auto validCode = [&code](int i) {
      return !code[i].empty() && std::ranges::all_of(code[i], [](auto c) {
        return std::isalnum(c) || c == '_';
      });
    };

    auto indices = std::views::iota(0, n);
    auto valid = indices | std::views::filter(active) |
                 std::views::filter(validBusinessLine) |
                 std::views::filter(validCode) |
                 std::ranges::to<std::vector<int>>();

    std::ranges::sort(valid, [&code, &businessLine](auto i, auto j) {
      auto posI = std::ranges::distance(
          VALID_BUSINESS_LINES.begin(),
          std::ranges::find(VALID_BUSINESS_LINES, businessLine[i]));

      auto posJ = std::ranges::distance(
          VALID_BUSINESS_LINES.begin(),
          std::ranges::find(VALID_BUSINESS_LINES, businessLine[j]));

      if (posI == posJ) {
        return code[i] < code[j];
      }
      return posI < posJ;
    });

    return valid | std::views::transform([&code](auto i) { return code[i]; }) |
           std::ranges::to<std::vector<std::string>>();
  }
};
