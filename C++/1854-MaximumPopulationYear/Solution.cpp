#include <cstddef>
#include <cstdlib>
#include <map>
#include <vector>

class Solution {
 public:
  int maximumPopulation(std::vector<std::vector<int>>& logs) {
    // logs[i] = [birth, death], birth/death year of the ith person.
    // population is the number of people alive during that year.
    // i-th person is counted in year x population if x is in the inclusive
    // range [birth, death-1],
    // Want: earliest year with the maximum population.
    // Line Sweep.
    // Events are the birth/death years. If birth, add 1 to the prefix sum,
    // if death, -1. Take the max of the sum.

    // {year, count}
    std::map<int, int> events;
    for (const auto& log : logs) {
      int birth = log[0];
      int death = log[1];

      ++events[birth];
      --events[death];
    }

    int maxPop = 0;
    int maxYear = 0;

    int pop = 0;
    for (const auto [year, count] : events) {
      pop += count;
      if (pop > maxPop) {
        maxPop = pop;
        maxYear = year;
      }
    }
    return maxYear;
  }
};
