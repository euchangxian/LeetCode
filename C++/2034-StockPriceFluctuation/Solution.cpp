#include <iterator>
#include <map>
#include <set>
#include <utility>

// Seems pretty trivial? Just maintain a table {timestamp, value}.
// Separately, maintain the max/min price seen.
// Does the max/min need to be corrected?
// Yeap. So, naively, iterate over the table to get the max/min price, which
// is definitely unoptimal.
// Alternatively, a multiset of values.
// Can possibly be optimized further.
class StockPrice {
 public:
  StockPrice() {}

  void update(int timestamp, int price) {
    auto it = timeprice.find(timestamp);
    if (it != timeprice.end()) {
      prices.extract(it->second);
    }

    timeprice[timestamp] = price;
    prices.insert(price);
  }

  int current() { return timeprice.rbegin()->second; }

  int maximum() { return *prices.rbegin(); }

  int minimum() { return *prices.begin(); }

 private:
  std::map<int, int> timeprice;
  std::multiset<int> prices;
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
