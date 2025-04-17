#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> findBuildings(std::vector<int>& heights) {
    // Buildings have an ocean view if all the buildings to its right have
    // a smaller height.
    // Monotonic stack? Iterate from right.
    const int n = heights.size();
    std::vector<int> st;
    st.reserve(n);
    st.push_back(n - 1);

    for (int i = n - 2; i >= 0; --i) {
      if (heights[i] > heights[st.back()]) {
        st.push_back(i);
      }
    }

    std::reverse(st.begin(), st.end());
    return st;
  }
};
