class Solution {
 public:
  int totalMoney(int n) {
    // Start with putting $1 on Monday.
    // Each subsequent day from Tuesday to Sunday, put $1 extra more
    // than previous day.
    // On every subsequent Monday, put $1 more than previous Monday.
    // Given n, return total amount of money at the end of nth
    // day.
    // (1 + 2 + ... + 7) + (2 + ... + 8) + ...
    // First Week: 7*8/2 = 28
    // Second Week: 28+7 = 35
    //
    // 7 (0 + 1 + ... + weeks-1)
    constexpr auto base = 28;

    auto fullWeeks = n / 7;
    auto sum = (base * fullWeeks) + (7 * (fullWeeks * (fullWeeks - 1) / 2));

    auto remaining = n % 7;
    for (int i = 0, start = 1 + fullWeeks; i < remaining; ++i, ++start) {
      sum += start;
    }
    return sum;
  }
};
