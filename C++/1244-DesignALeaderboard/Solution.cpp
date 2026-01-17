#include <algorithm>
#include <functional>
#include <ranges>
#include <set>
#include <unordered_map>
#include <utility>

// A {playerId: score}
// Then, a std::multiset of the universe of scores.
class Leaderboard {
 public:
  Leaderboard() {}

  // add score to the given playerId. If the player does not yet exist, add
  // to the leaderboard.
  void addScore(int playerId, int score) {
    if (auto it = players.find(playerId); it != players.end()) {
      auto handle = scores.extract(it->second);
      handle.value() += score;

      auto setIt = scores.insert(std::move(handle));
      it->second = setIt;
    } else {
      auto setIt = scores.insert(score);
      players.emplace(playerId, setIt);
    }
  }

  // Return the score sum of the top K players.
  int top(int K) {
    return std::ranges::fold_left(
        scores | std::views::reverse | std::views::take(K), 0, std::plus<>{});
  }

  // Reset the score of the player to 0. It is guaranteed to exist.
  void reset(int playerId) {
    auto it = players.extract(playerId);
    scores.erase(it.mapped());
  }

 private:
  using Node = std::multiset<int>::iterator;
  std::unordered_map<int, Node> players;

  std::multiset<int> scores;
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */
