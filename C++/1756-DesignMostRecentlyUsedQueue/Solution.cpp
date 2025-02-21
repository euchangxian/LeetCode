#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

template <typename T = long long>
class FenwickTree {
 public:
  FenwickTree(int n, int capacity) : n_(capacity), ft_(capacity + 1, 0) {
    for (int i = 1; i <= n; ++i) {
      update(i, 1);
    }
  }

  constexpr T query(int l, int r) const { return prefix(r) - prefix(l - 1); }

  constexpr T prefix(int i) const {
    T sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += ft_[i];
    }
    return sum;
  }

  constexpr void update(int i, T diff) {
    for (; i <= n_; i += i & -i) {
      ft_[i] += diff;
    }
  }

  // Returns the 1-indexed Index.
  constexpr int kthElement(T k) const {
    // Faster, O(logn) binary lifting.
    if (k <= 0 || k > prefix(n_)) {
      return -1;
    }

    int idx = 0;
    T sum = 0;
    for (int step = 1 << (31 - __builtin_clz(n_)); step > 0; step >>= 1) {
      int next = idx + step;
      if (next <= n_ && sum + ft_[next] < k) {
        idx = next;
        sum += ft_[next];
      }
    }
    return idx + 1;
  }

 private:
  // i is 1-indexed, as this can only be invoked internally.
  std::size_t n_;
  std::vector<T> ft_;
};

/**
 * FIFO-like.
 * fetch(k) moves the k-th element to the end of the queue and returns it.
 *
 * An Augment LinkedList with a HashMap to the nodes would work, in O(1) time
 * per fetch.
 * Ah, not really. The positions in the hashmap would be difficult to update.
 *
 * Alternatively, Fenwick Trees. Observe that the act of selecting the kth
 * element and placing it at the front does two things:
 * - For elements in front of the kth-element, i.e., [1..k-1], their positions
 *   remain the same.
 * - For elements behind, [k+1, n], they get shifted left one position.
 *
 * See 1505. Minimum Possible Integer after at most K Adjacent Swaps on Digits,
 * and 2659. Make Array Empty which have similar concepts of counting the
 * shifts.
 *
 * In essence, a presence array can be used, with size n + 2000 (2000 calls to
 * fetch).
 * Then, kth-element will return the index in the FenwickTree where the prefix
 * sum is equal to k, which can be used to index into another array storing
 * values, with the same size.
 */
class MRUQueue {
 public:
  static constexpr int MAX_N = 4000;

  MRUQueue(int n) : back(n + 1), ft(n, n + 2000) {
    for (int i = 1; i <= n; ++i) {
      values[i] = i;
    }
  }

  int fetch(int k) {
    int idx = ft.kthElement(k);
    ft.update(idx, -1);
    values[back] = values[idx];
    ft.update(back, 1);

    return values[back++];
  }

 private:
  int back;  // points to one past the last element
  std::array<int, MAX_N + 1> values{};
  FenwickTree<int> ft;
};

/**
 * Your MRUQueue object will be instantiated and called as such:
 * MRUQueue* obj = new MRUQueue(n);
 * int param_1 = obj->fetch(k);
 */
