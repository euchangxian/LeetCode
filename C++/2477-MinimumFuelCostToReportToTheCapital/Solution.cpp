#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 minimumFuelCost(std::vector<std::vector<int>>& roads, int seats) {
    // n cities from 0 to n-1.
    // The capital city is city 0.
    // roads[i] = [a, b] indicating a bidirectional road between a and b.
    // Each city has a representative.
    // Each representative travels to the capital on a Car.
    // Each Car has a seat capacity.
    // At each city, a representative can use the car in their city to travel,
    // or ride with another representative.
    // Each edge is 1 litre of fuel.
    // Return minimum litre of fuel to reach the capital.
    //
    // Hm. We want to aggregate as many representatives on a car as possible.
    // Something like LCA?
    // Hm. Input graph is a tree. Thus there is only one path to the
    // capital - the shortest path.
    // Hmmm. Rooting the tree at the capital: node 0, we can get the distance
    // to the leaves, along with their number of children (postorder).
    // Then, we can probably derive the fuel cost as a function of the distance
    // and children (and seat capacity).
    // i.e., the number of cars needed.
    //
    // Hm. notice we do not need the distance from root.
    // We can determine how much fuel is needed to traverse the current edge as
    // a function of seats and number of children, allowing us to derive the
    // number of cars, and hence the amount of fuel.
    i64 result = 0;

    const int n = roads.size() + 1;
    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : roads) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }

    // return number of children
    auto postorder = [&](this auto&& postorder, int curr,
                         int parent = -1) -> int {
      int ppl = 1;
      for (int child : adj[curr]) {
        if (child == parent) {
          continue;
        }

        int subtree = postorder(child, curr);
        i64 cars = (subtree + seats - 1) / seats;
        result += cars;
        ppl += subtree;
      }
      return ppl;
    };

    postorder(0);
    return result;
  }
};
