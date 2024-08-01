#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> frequency;

    for (int num : nums) {
      frequency[num]++;
    }

    auto cmp = [&frequency](int a, int b) {
      return frequency[a] < frequency[b];
    };

    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    for (const auto &pair : frequency) {
      pq.push(pair.first);
    }

    vector<int> result;
    for (int i = 0; i < k && !pq.empty(); i++) {
      result.push_back(pq.top());
      pq.pop();
    }

    return result;
  }
};
