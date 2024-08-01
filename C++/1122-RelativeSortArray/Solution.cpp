#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
    unordered_map<int, int> freq;
    for (int num : arr2) {
      ++freq[num];
    }

    int i = 0;
    int j = arr2.size();
    vector<int> result = vector<int>(arr1.size());
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
