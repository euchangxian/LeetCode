#include <ranges>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// Design a Food Rating System that can:
// - Modify Rating of a food item in the system
// - Return the highest rated food item for a type of cuisine in the system.
//
// Given that changeRating has no cuisine information, we can use extra space
// to map the name to its cuisine.
// This way, we can maintain a sorted data structure for each cuisine,
// so that we can retrieve the max-rated.
// A hashmap to store the cuisine, to index into a sorted map.
//
// Depending on the request patterns, a vector may indeed be apt, but this is
// obviously out-of-scope.
//
// Hm, slight problem. If we store (name: rating) in the std::map, we would
// have to sort by value using a custom comparator.
// This is not exactly idiomatic or ideal.
// Using a pair {rating, name}, then storing iterators to this pair for update
// should work.
//
// In conclusion:
// - To maintain the sorted order of the foods of a cuisine, we need to store:
//   (food: cuisine).
// - Then, to retrieve the max-rated food of a certain cuisine, we need to
//   store: {-rating, food}. Note that we store negative, retrieve the
//   beginning of the map, so we can tie-break lexicographically.
// ModifyRating -> O(logn) to "erase" and "insert" into the sorted map.
// HighestRated -> O(1) to access the extreme elements in a sorted map.
// ConstructionCost -> 1 time cost of O(nlogn) to initialise a sorted data
// structure.
//
// All can be optimised further by allocating an integer index to each food
// and cuisine.
class FoodRatings {
 public:
  // Given n foods,
  // food[i] - name of the ith food
  // cuisines[i] - cuisine of the ith food
  // ratings[i] - initial rating of the ith food
  FoodRatings(std::vector<std::string>& foods,
              std::vector<std::string>& cuisines,
              std::vector<int>& ratings) {
    const auto n = static_cast<int>(foods.size());
    for (auto [food, cuisine, rating] :
         std::views::zip(foods, cuisines, ratings)) {
      ratingOf[food] = -rating;
      cuisineOf[food] = cuisine;
      cuisineRatings[cuisine].emplace(-rating, food);
    }
  }

  // Given the name of the food, change the rating to newRating.
  void changeRating(std::string food, int newRating) {
    // Constraints guarantee food exists in the system.
    auto cuisine = cuisineOf[food];
    auto& ratings = cuisineRatings[cuisine];
    auto& oldRating = ratingOf[food];

    ratings.erase({oldRating, food});
    ratings.emplace(-newRating, food);

    oldRating = -newRating;
  }

  // Return the name of the food item that has the highest rating for the
  // given cuisine.
  // If tied, return lexicographically smallest.
  std::string highestRated(std::string cuisine) {
    auto& ratings = cuisineRatings[cuisine];
    auto [_, food] = *ratings.begin();
    return food;  // should be NRVO-ed
  }

 private:
  std::unordered_map<std::string, int> ratingOf;
  std::unordered_map<std::string, std::string> cuisineOf;

  using Ratings = std::set<std::pair<int, std::string>>;
  std::unordered_map<std::string, Ratings> cuisineRatings;
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
