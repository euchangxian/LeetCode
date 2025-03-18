#include <array>
#include <cstddef>
#include <cstdlib>

/**
 * k is a variable.
 * Running prefix product.
 * nums[i] can be 0 though, prefix product will then be useless.
 * Given that we always want the LAST k, we can restart the count upon
 * encountering a 0
 */
class ProductOfNumbers {
 public:
  ProductOfNumbers() {}

  void add(int num) {
    if (num == 0) {
      n = 0;
      return;
    }

    nums[n++] = num;
    prefix[n] = num * prefix[n - 1];
  }

  int getProduct(int k) {
    if (k > n) {
      return 0;
    }

    // Product of last K nums.
    return prefix[n] / prefix[n - k];
  }

 private:
  constexpr static int MAX_K = 4 * 10000;
  int n{0};
  std::array<int, MAX_K + 1> nums;

  // prefix[i] indicates the prefix product from nums[0] to nums[i-1]
  // i.e., 1-indexed
  std::array<int, MAX_K + 1> prefix{1};
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
