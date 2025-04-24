#include <cmath>

class Solution {
 public:
  int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
    // N buckets, one is poisoned.
    // In each round:
    // 1. For each pig, feed a subset of buckets to it.
    // 2. Wait minutesToDie minutes.
    // 3. If a pig dies, then it was fed the poisoned bucket.
    // Find the minimum number of pigs to find the poisoned bucket in
    // minutesToTest time.
    //
    // If one pig, linear search.
    // If there are two pigs, ternary search?
    // SuperEggDrop?
    //
    // NOTE: Went to see answer.
    // Cool asf. Note the original approach didnt naturally account for the
    // number of tests possible.
    // Model the pig as a qbit (quantum bit).
    // Then, the number of states the pig can have is determined by the
    // number of tests possible, minutesToTest/minutesToDie.
    // if tests=0, then no tests can be made, the pig can only be alive. 1 state
    // if tests=1, then the pig can possibly die. Alive | Dead. 2 state
    // if tests=2, then Alive | Dead after 1st test | Dead after 2nd test
    // Consider 2 tests.
    // If there is 1 pig, then it can test 2 buckets.
    // If there is 2 pigs, then they can test 2^2 = 4 buckets.
    // Thus, the number of buckets that can be tested is 2^x
    // Intuitively, generalizing to p pigs, the number of buckets that can
    // be tested is p^x.
    // Thus, we want to satisfy p^x >= buckets => x >= log_p(buckets)
    //                                         => x >= log(buckets)/log(p)
    //                                         => p >= log(buckets)/x
    int states = minutesToTest / minutesToDie + 1;
    return std::ceil(std::log2(buckets) / std::log2(states));
  }
};
