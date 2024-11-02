#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  std::vector<int> decrypt(std::vector<int>& code, int k) {
    // Given constraints, an extremely naive solution would work too, i.e.,
    // summing the next k elements at each index i.
    // Fixed size sliding window of size k
    // 1 <= n <= 100
    // 1 <= code[i] <= 100
    // -(n-1) <= k <= n-1
    // For both negative and positive values of k, only the starting
    // position matters. In both scenarios, the window still slides rightwards.
    if (k == 0) {
      return std::vector<int>(code.size(), 0);
    }

    const size_t n = code.size();

    // initialize the starting indices of the window
    int start = k > 0 ? 1 : n + k;  // wont overflow. -k <= n-1
    int end = k > 0 ? k : n - 1;

    int windowSum = 0;
    for (int i = start; i <= end; ++i) {
      windowSum += code[i];
    }

    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = windowSum;

      windowSum -= code[(start++) % n];
      windowSum += code[(++end) % n];
    }
    return result;
  }
};
