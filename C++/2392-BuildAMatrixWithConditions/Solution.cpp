#include <queue>
#include <vector>

class Solution {
 public:
  // Contains 1 to k
  std::vector<std::vector<int>> buildMatrix(
      int k,
      std::vector<std::vector<int>>& rowConditions,
      std::vector<std::vector<int>>& colConditions) {
    std::vector<int> rowOrder = topologicalSort(k, rowConditions);
    if (rowOrder.empty()) {
      return {};
    }

    std::vector<int> columnOrder = topologicalSort(k, colConditions);
    if (columnOrder.empty()) {
      return {};
    }

    // Stores the index where the k-th integer should be placed
    std::vector<int> rowPosition(k);
    std::vector<int> columnPosition(k);
    for (int i = 0; i < k; ++i) {
      rowPosition[rowOrder[i] - 1] = i;
      columnPosition[columnOrder[i] - 1] = i;
    }

    std::vector<std::vector<int>> matrix(k, std::vector<int>(k, 0));
    for (int num = 1; num <= k; ++num) {
      int row = rowPosition[num - 1];
      int col = columnPosition[num - 1];

      matrix[row][col] = num;
    }

    return matrix;
  }

 private:
  // Kahn's algorithm: enqueue and process zero in-degree nodes iteratively
  std::vector<int> topologicalSort(
      const int k,
      const std::vector<std::vector<int>>& conditions) {
    std::vector<std::vector<int>> graph(k);
    std::vector<int> inDegree(k, 0);
    for (const auto& condition : conditions) {
      // Sort from top-to-bottom / left-to-right
      // convert 1-indexed to 0-index
      int from = condition[0] - 1;
      int to = condition[1] - 1;

      graph[from].push_back(to);
      ++inDegree[to];
    }

    std::queue<int> zeroDegree;
    for (int i = 0; i < k; ++i) {
      if (inDegree[i] == 0) {
        zeroDegree.push(i);
      }
    }

    std::vector<int> result;
    result.reserve(k);
    while (!zeroDegree.empty()) {
      int v = zeroDegree.front();
      zeroDegree.pop();

      result.push_back(v + 1);  // convert back to 1-index

      for (int neighbour : graph[v]) {
        if (--inDegree[neighbour] == 0) {
          zeroDegree.push(neighbour);
        }
      }
    }

    if (result.size() != k) {
      return {};  // Cycle detection
    }
    return result;
  }
};
