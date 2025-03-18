#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> relativeSortArray(std::vector<int>& arr1,
                                     std::vector<int>& arr2) {
    std::unordered_map<int, int> freq;
    for (int num : arr2) {
      ++freq[num];
    }

    int i = 0;
    int j = arr2.size();
    std::vector<int> result = std::vector<int>(arr1.size());
    for (int num : arr1) {
      if (freq[num]) {
        result[i] = num;
        ++i;
        --freq[num];
      } else {
        result[j] = num;
        ++j;
      }
    }
    return result;
  }
};
