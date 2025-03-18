#include <algorithm>
#include <vector>

class Solution {
 public:
  double averageWaitingTime(std::vector<std::vector<int>>& customers) {
    if (customers.size() < 1) {
      return 0;
    }
    double totalWaitingTime = 0;

    // indicates the time when the customer's order is finished
    int nextIdleTime = 0;

    for (int i = 0; i < customers.size(); ++i) {
      int arrival = customers[i][0];
      int waitingTime = customers[i][1];
      nextIdleTime = std::max(arrival, nextIdleTime) + waitingTime;

      totalWaitingTime += nextIdleTime - arrival;
    }
    return totalWaitingTime / customers.size();
  }
};
