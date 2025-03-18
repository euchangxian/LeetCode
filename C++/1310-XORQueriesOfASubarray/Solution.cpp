#include <vector>

class Solution {
 public:
  std::vector<int> xorQueries(std::vector<int>& arr,
                              std::vector<std::vector<int>>& queries) {
    std::size_t n = arr.size();

    std::vector<int> prefixXOR(n, 0);
    prefixXOR[0] = arr[0];
    for (int i = 1; i < n; ++i) {
      prefixXOR[i] = arr[i] ^ prefixXOR[i - 1];
    }

    std::size_t m = queries.size();
    std::vector<int> answer(m, 0);
    for (int i = 0; i < m; ++i) {
      int start = queries[i][0];
      int end = queries[i][1];

      // queries include starting index
      answer[i] = prefixXOR[end] ^ prefixXOR[start] ^ arr[start];
    }

    return answer;
  }
};
