#include <algorithm>
#include <deque>
#include <functional>
#include <ranges>
#include <set>
#include <vector>

class Solution {
 public:
  int maxTaskAssign(std::vector<int>& tasks,
                    std::vector<int>& workers,
                    int pills,
                    int strength) {
    // Question is worded like BSTA.
    // At first glance, not so trivial to determine which woker should receive
    // the pill.
    // However, if we sort by ascending order, it becomes clearer.
    // If, a worker[j] + pill < tasks[i], then we can be sure that this worker
    // can never be matched to a task. We can greedily exclude it.
    // No. Naive greedy does not work...
    // Consider the case:
    // tasks = {5, 5, 100}
    // workers={1, 6, 6}
    // pills=1, strength=100
    // Then, the algorithm will naively match 0th and 1st worker to the first
    // two task, by giving the 0th woker a pill.
    //
    // We need to break this down.
    // BSTA is correct. To be more specific, BSTA on k, the maximum number of
    // matches.
    // Thus, it makes sense to greedily pick the smallest K tasks, and the
    // largest K workers.
    const int n = tasks.size();
    const int m = workers.size();
    std::sort(tasks.begin(), tasks.end());
    std::sort(workers.begin(), workers.end(), std::greater<>{});

    auto feasibleNaive = [pills, strength](std::span<int> tasks,
                                           std::span<int> w) -> bool {
      int remaining = pills;
      std::multiset<int> workers{w.begin(), w.end()};
      for (int task : tasks | std::ranges::views::reverse) {
        // no pill usage:
        bool canAssign = false;
        auto nopill = workers.lower_bound(task);
        if (nopill != workers.end()) {
          canAssign = true;
          workers.erase(nopill);
        } else if (remaining > 0) {
          // need use pill
          auto pill = workers.lower_bound(task - strength);
          if (pill != workers.end()) {
            workers.erase(pill);
            --remaining;
            canAssign = true;
          }
        }

        if (!canAssign) {
          return false;
        }
      }
      return true;
    };
    auto feasible = [pills, strength](std::span<int> tasks,
                                      std::span<int> workers) -> bool {
      // note that tasks are sorted in ascending, workers in descending order.
      int remaining = pills;
      auto tIt = tasks.begin();
      std::deque<int> canAssign;

      // We greedily attempt to assign a task to the workers, starting from
      // the weakest one.
      // Try to find the minimum possible task such that  worker >= task.
      // Otherwise, assign the maximum possible task s.t. worker+strength>=task
      // Since we are iterating from smallest to biggest task, we can
      // add tasks to a Deque while worker+strength >= task.
      // Then, the choices are clear:
      // - if the easiest task can be done by the worker, assign it.
      // - Otherwise, assign the rightmost task.
      // - Otherwise, the worker cannot be assigned a task. Return false.
      for (int worker : workers | std::ranges::views::reverse) {
        while (tIt != tasks.end() && worker + strength >= *tIt) {
          canAssign.push_back(*tIt);
          ++tIt;
        }

        if (canAssign.empty()) {
          return false;
        }

        if (worker >= canAssign.front()) {
          canAssign.pop_front();
        } else if (remaining > 0 && worker + strength >= canAssign.back()) {
          --remaining;
          canAssign.pop_back();
        } else {
          return false;
        }
      }
      return true;
    };

    int l = 0;
    int r = std::min(n, m);
    while (l < r) {
      int mid = l + (r - l + 1) / 2;
      if (feasible(std::span{tasks.begin(), tasks.begin() + mid},
                   std::span{workers.begin(), workers.begin() + mid})) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    return l;
  }
};
