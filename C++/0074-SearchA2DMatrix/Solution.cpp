#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    // Utilise the sorted property of the matrix + modulo/division arithmetic
    // to "flatten" the 2D matrix into a 1D search space
    int m = matrix.size();
    int n = matrix[0].size();

    int left = 0;
    int right = m * n - 1; // Index of the last element in a 1D array
    while (left < right) {
      int mid = left + (right - left) / 2;

      // Find the row/column index of the element given its 1D index.
      // For row, use floor division and take the result: (i / n).
      // For column, modulo it and take the remainder: (i % n).
      // Given that n refer to the number of elements in each row,
      // (i / n) gives us how many complete rows crossed,
      // and (i % n) gives us far into the current row we are.
      if (matrix[mid / n][mid % n] < target) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return matrix[left / n][left % n] == target;
  }
};
