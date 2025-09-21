#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

// N shops. Implement a system that supports Searching, Booking and Returning
// Movies.
// entries[i] = [shop, movie, price] indicate that there is a movie_i at shop_i
// with a rental price_i. Each shop has at most one copy of movie_i.
// - search: find cheapest 5 shops that have an unrented copy of a given movie.
//           The shops should be sorted by price in ascending order. Tiebreak
//           by smaller shop_i.
// - rent: rent an unrented copy of a given movie
// - drop: return a rented copy at a given shop
// - report: return the 5 cheapest rented movies as a 2D list result, where
//           result[j] = [shop, movie] indicating that the jth cheapest movie
//           was rented from shop_j. Sorted by ascending order of price, and
//           tie break by smaller shop_i, then smaller movie_i.
// Note that test cases are generated such that `rent` will only be invoked
// if the shop has an unrented copy - no need to check, and likewise for drop,
// only if the shop had PREVIOUSLY lent out the movie,
//
// Initial thoughts: A Priority Queue, or a Sorted Map to implement the
// cheapest-5.
// A bunch of space and bookkeeping to be done.
// Very similar to 1500-DesignAFileSharingSystem, but with an extra dimension
// of price.
// We need to track the movement of movies in/out. Not between shops, because
// rent-drop are paired, based off the constraints.
// Each shop has movies.
// Each movie has a price.
//
// We want to be able to query the cheapest unrented copy of a movie across all
// shops,
// and also the cheapest rented movies across all shops.
// We also want to keep track of movies rented/available at a shop? I dont
// think this is necessary.
// For unrented movies: std::multimap<MovieID, (Price, ShopID)>, allowing us
// to quickly query the cheapest-5 unrented.
// But for rent/drop to update this map, we need to store the Price of a Movie
// in a shop. Given that each shop only stores at most one copy of a movie,
// we can use a map for this. i.e., std::unordered_map<ShopID, Movies>, where
// we can either use a std::vector<(MovieID, Price)> and do a search, or a
// std::unordered_map<MovieID, Price>. This table will be static.
// Next, for querying the cheapest rented out copy of movies, we only need to
// store at most 5, since we dont need any other information. We can store
// tuples (Price, ShopID, MovieID).
//
// Hm. Does this mean we can do the same for the unrented? Nope, we kinda need a
// source of truth. Wait, thats our static map.
// We initialize with the cheapest-5 unrented, and then bookkeep throughout
// operations.
// Priority Queue for each movie across all shops: (Price, ShopID)
// Ah. Shit. What if the movie to-be-rented is part of the cheapest?
// I suppose this means we need to store the entire 3-tuple itself, in a
// std::set. And that means we need to be able to find the next-cheapest.
// This means we are back to storing the whole set of unrented movies.
// Similarly, what if we return a movie that is part of the cheapest...
// We also need to store the entire set of rented movies.
// Then, use the static shopMovies map to form the complete key for indexing
// into the map.
//
// Optimisation: Use std::array/vector instead of an unordered_map.
// For movies owned, depending on the density, a std::unordered_map may be
// better to avoid memory overflows.
constexpr int MAX_SHOPS = 3E5;
class MovieRentingSystem {
 private:
  using i64 = long long;

  using MovieID = int;
  using ShopID = int;
  using Price = int;

 public:
  MovieRentingSystem(int n, std::vector<std::vector<int>>& entries) {
    for (const auto& entry : entries) {
      auto shop = entry[0];
      auto movie = entry[1];
      auto price = entry[2];

      prices.emplace(key(shop, movie), price);
      cheapestUnrented[movie].emplace(price, shop);
    }
  }

  std::vector<int> search(int movie) {
    std::vector<int> result;
    const auto& copies = cheapestUnrented[movie];
    for (const auto [_, shop] : copies) {
      result.emplace_back(shop);
      if (result.size() >= 5) {
        break;
      }
    }

    return result;
  }

  void rent(int shop, int movie) {
    auto price = prices[key(shop, movie)];

    cheapestUnrented[movie].erase({price, shop});
    cheapestRented.emplace(price, shop, movie);
  }

  void drop(int shop, int movie) {
    auto price = prices[key(shop, movie)];

    cheapestRented.erase({price, shop, movie});
    cheapestUnrented[movie].emplace(price, shop);
  }

  std::vector<std::vector<int>> report() {
    std::vector<std::vector<int>> result;
    for (const auto& [price, shop, movie] : cheapestRented) {
      result.push_back({shop, movie});
      if (result.size() >= 5) {
        break;
      }
    }
    return result;
  }

 private:
  i64 key(ShopID shop, MovieID movie) {
    return (static_cast<i64>(shop) << 32) | movie;
  }
  // NOTE: instead of
  // std::unordered_map<ShopID, std::unordered_map<MovieID, Price>> which has
  // extremely poor cache locality, we pack (ShopID|MovieID) into a single
  // 64-bit integer to index. This works, because each shop has at most a single
  // movieID.
  std::unordered_map<i64, Price> prices;

  using UnrentedNode = std::pair<Price, ShopID>;
  std::unordered_map<MovieID, std::set<UnrentedNode>> cheapestUnrented;
  using RentedNode = std::tuple<Price, ShopID, MovieID>;
  std::set<RentedNode> cheapestRented;
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
