#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> reconstructQueue(
      std::vector<std::vector<int>>& people) {
    // Notice that finding the kth empty spot is costly; we are doing
    // order statistics on dynamic data.
    // Fenwick/Segment Trees!
    // We can start with an array of all '1's, indicating empty. Thus, finding
    // the k-th empty will be a matter of binary searching using RSQs.
    // Then, update that point (point-update) to 0, so subsequent RSQs will
    // be adjusted accordingly.
    const int n = people.size();

    // build FT, O(n + m).
    std::vector<int> ft(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
      int parent = i + (i & -i);
      if (parent <= n) {
        ft[parent] += ft[i];
      }
    }

    // range sum query
    auto rsq = [&ft](int l, int r) -> int {
      auto prefix = [&ft](int i) -> int {
        int sum = 0;
        while (i > 0) {
          sum += ft[i];
          i -= i & -i;
        }
        return sum;
      };

      return prefix(r + 1) - prefix(l);
    };

    // point update
    auto pu = [n, &ft](int i, int v) -> void {
      ++i;
      while (i <= n) {
        ft[i] += v;
        i += i & -i;
      }
    };

    // kth element.
    auto selectBSTA = [n, &ft, &rsq](int k) -> int {
      int l = 0;
      int r = n - 1;

      while (l < r) {
        int mid = l + (r - l) / 2;

        if (rsq(0, mid) < k) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      return l;
    };

    auto select = [n, &ft, &rsq](int k) -> int {
      int idx = 0;
      int sum = 0;
      int step = 1 << (31 - __builtin_clz(n));

      while (step > 0) {
        int next = idx + step;

        if (next <= n && sum + ft[next] < k) {
          idx = next;
          sum += ft[next];
        }
        step >>= 1;  // halve the step size.
      }

      return idx;
    };

    std::sort(people.begin(), people.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
                return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
              });

    std::vector<std::vector<int>> result(n);
    for (int i = 0; i < n; ++i) {
      // WARNING:
      // people[i][1] is 0-indexed. Instead of saying we want the 0th empty
      // spot, if people[i][1] = 0, it should be 1st empty slot.
      int j = select(people[i][1] + 1);
      result[j] = people[i];
      pu(j, -1);
    }
    return result;
  }

  std::vector<std::vector<int>> reconstructQueueSlots(
      std::vector<std::vector<int>>& people) {
    // Another way would be to sort by ascending order of h, then tie broken
    // by descending order of k.
    // Then, iterating through, count the empty slots = k, and insert the
    // current person there.
    std::sort(people.begin(), people.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
                return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
              });

    // vector of length 0 to indicate empty slot.
    std::vector<std::vector<int>> result(people.size(), std::vector<int>{});

    for (int i = 0; i < people.size(); ++i) {
      int empty = 0;
      int j = 0;

      while (j < people.size() && empty < people[i][1]) {
        if (result[j].empty()) {
          ++empty;
        }
        ++j;
      }

      // avoid inserting into an already-filled spot.
      while (j < people.size() && !result[j].empty()) {
        ++j;
      }
      result[j] = people[i];
    }
    return result;
  }

  std::vector<std::vector<int>> reconstructQueueInsert(
      std::vector<std::vector<int>>& people) {
    // people[i] = [h, k], representing the ith person of height h, with
    // exactly k other people in front who have a height greater than or equal
    // to h.
    // Reconstruct the Queue, such that queue[i] = [h, k] is the attribute of
    // the jth person in the queue.
    // First glance, looked like sort/mono-stack like question.
    // i.e., if shortest person has no one in front, then that person will be
    // at the front of the queue, recursively.
    // If the tallest person has no one in front, then that person could both
    // be at the front, or the back. If the second tallest person has someone
    // in front, then that person must be behind the tallest person.
    // In this manner, we can sort of topologically insert and fulfil the
    // tightest constraints first.
    // Kinda expensive though? std::sort, first by descending order of h,
    // then tiebroken by ascending order of k.
    // Then insertion-sort.
    //
    std::sort(people.begin(), people.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
                return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
              });

    std::vector<std::vector<int>> result;
    result.reserve(people.size());
    for (int i = 0; i < people.size(); ++i) {
      // insert the current biggest, with the constraints accordingly.
      result.insert(result.begin() + people[i][1], people[i]);
    }
    return result;
  }
};
