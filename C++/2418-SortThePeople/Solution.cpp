#include <algorithm>
#include <string>
#include <vector>

class Solution {
 private:
 public:
  std::vector<std::string> sortPeople(std::vector<std::string>& names,
                                      std::vector<int>& heights) {
    std::vector<int> indices(names.size());
    for (int i = 0; i < names.size(); ++i) {
      indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(),
              [&heights](int i, int j) { return heights[i] > heights[j]; });

    std::vector<std::string> result(names.size());
    for (int i = 0; i < names.size(); ++i) {
      result[i] = names[indices[i]];
    }

    return result;
  }
};
