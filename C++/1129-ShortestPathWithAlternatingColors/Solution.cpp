#include <algorithm>
#include <array>
#include <queue>
#include <ranges>
#include <utility>
#include <vector>

constexpr int INF = 1e9;
enum Color {
  Red,
  Blue,
  Count,
};

class Solution {
 public:
  std::vector<int> shortestAlternatingPaths(
      int n,
      std::vector<std::vector<int>>& redEdges,
      std::vector<std::vector<int>>& blueEdges) {
    // n nodes labelled 0 to n-1.
    // Each edge is red/blue, where
    // red|blueEdges[i] = [a, b] indicate a directed edge from a to b.
    // There may be self-edges and parallel edges (i assume repeated).
    // Return answer[i] whihc indicate the shortest path from node 0 to node x
    // such that the edge colors alternate, or -1.
    //
    // Create two graphs, G_red and G_blue, which respectively contains the
    // edges of each color only.
    // Then, traversing an edge in G_red will go to G_blue.
    // BFS on two Graphs.
    std::vector<std::vector<int>> rG(n), bG(n);
    for (const auto& edge : redEdges) {
      rG[edge[0]].push_back(edge[1]);
    }
    for (const auto& edge : blueEdges) {
      bG[edge[0]].push_back(edge[1]);
    }
    std::array<std::vector<std::vector<int>>, Color::Count> G;
    G[Color::Red] = std::move(rG), G[Color::Blue] = std::move(bG);

    // std::vector<int> result(n, -1);
    // dist[color][node]
    std::vector<std::array<int, Color::Count>> dist(
        n, std::array<int, 2>{INF, INF});

    std::queue<std::pair<int, Color>> frontier;  // {node, color}
    frontier.emplace(0, Color::Red);
    frontier.emplace(0, Color::Blue);
    dist[0][Color::Red] = 0;
    dist[0][Color::Blue] = 0;

    // result[0] = 0;
    while (!frontier.empty()) {
      int sz = frontier.size();
      while (sz--) {
        auto [curr, color] = frontier.front();
        frontier.pop();

        Color nextColor = static_cast<Color>(1 - color);
        for (int next : G[nextColor][curr]) {
          if (dist[curr][color] + 1 < dist[next][nextColor]) {
            dist[next][nextColor] = dist[curr][color] + 1;
            frontier.emplace(next, nextColor);
          }
        }
      }
    }

    return std::ranges::views::transform(
               dist,
               [](const auto& d) {
                 int distance = std::min(d[Color::Red], d[Color::Blue]);
                 return distance == INF ? -1 : distance;
               }) |
           std::ranges::to<std::vector<int>>();
  }
};
