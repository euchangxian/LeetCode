#include <vector>

using namespace std;
class Solution {
public:
  int countTriplets(vector<int> &arr) {
    // xor(arr[i..k]) == 0
    int count = 0;
    for (int i = 0; i < arr.size(); ++i) {
      int prefixXOR = 0;
      for (int k = i; k < arr.size(); ++k) {
        prefixXOR ^= arr[k];
        if (prefixXOR == 0) {
          // Problem constraint allows j to be same as k
          count += k - i; // k-i possible combinations of j
        }
      }
    }
    return count;
  }
};
