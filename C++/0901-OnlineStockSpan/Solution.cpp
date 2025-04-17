#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

constexpr int MAX_N = 1e5;

constexpr auto lessThanOrEqualTo(int price) {
  return [price](int p) -> bool { return p <= price; };
}

// Return the span of the Stock's price for the current day.
// The span of a stock on day i is the maximum number of consecutive days j,
// j < i, --j for which the price was less than or equal to the price on day i
// Naively, maintain a vector of prices. Whenever next(price) is called,
// iterate from the back in reverse, counting while prevPrice <= price.
// Essentially O(N^2).
// Can we do better? Range queries, ordered by price. But this only gives us
// the number of days for which the prevPrice <= price, not consecutive days.
//
// First, notice that the naive method involves checking the same price multiple
// times.
// When a new price is added, can we avoid this recomputed work?
// Monotonically decreasing stack.
// When we have a new price, we can pop all previous price that are less than
// or equal to this newPrice. Then, store the newPrice along with the span.
class StockSpanner {
 public:
  StockSpanner() { prices.reserve(MAX_N); }

  int next(int price) {
    int span = 1;
    while (!prices.empty() && prices.back().first <= price) {
      span += prices.back().second;
      prices.pop_back();
    }
    prices.emplace_back(price, span);
    return span;
  }

 private:
  std::vector<std::pair<int, int>> prices;
};

class StockSpannerNaive {
 public:
  StockSpannerNaive() { prices.reserve(MAX_N); }

  int next(int price) {
    int span = 1 + std::ranges::distance(prices | std::ranges::views::reverse |
                                         std::ranges::views::take_while(
                                             lessThanOrEqualTo(price)));
    prices.push_back(price);
    return span;
  }

 private:
  std::vector<int> prices;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
