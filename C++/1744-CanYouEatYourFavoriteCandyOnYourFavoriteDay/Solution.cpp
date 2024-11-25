#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<bool> canEat(std::vector<int>& candiesCount,
                           std::vector<std::vector<int>>& queries) {
    // Convoluted question...
    // Seems like prefix sums. Essentially, queries are [type, day, dailyLimit].
    // Given array of candies where candies[i] indicate the amount of type i
    // candies.
    // Candies of type i can not be eaten unless all candies of type i-1 are
    // eaten.
    // On each day, multiple types of candies can be eaten.
    // At least one candy must be eaten per day.
    // As such, by getting the prefix sums, i.e., the total number of candies
    // required to eat before getting to the favorite candy, we can calculate
    // how many days at minimum is required to finish eating the prerequisite
    // candies.

    // calculate prefixes.
    std::vector<long long> prefix(candiesCount.size() + 1);
    long long sum = 0;
    for (int i = 0; i < candiesCount.size(); ++i) {
      sum += candiesCount[i];
      prefix[i + 1] = sum;
    }

    std::vector<bool> result(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      int type = queries[i][0];
      long long day = queries[i][1];
      long long cap = queries[i][2];

      long long minEaten = (day + 1);  // eat 1-per-day
      long long maxEaten = (day + 1) * cap;

      // Must clear the prerequisite, and still eat at least 1 candy of favorite
      long long prerequisite = prefix[type] + 1;
      long long typeEnd = prefix[type + 1];  // safe, since size + 1

      // check if theres an overlap between [minEaten, maxEaten] and
      // [prerequisite, typeEnd]
      // i.e., check that the minimum eaten will not exceed the total number
      // of candies up till and including the favorite candy.
      // Also check that the maxEaten, at the very least can exceed the minimum
      // required candies.
      result[i] = minEaten <= typeEnd && maxEaten > prerequisite;
    }

    return result;
  }
};
