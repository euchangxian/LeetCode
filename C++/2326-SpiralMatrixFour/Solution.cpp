#include <vector>

#ifdef LOCAL
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
#endif  // LOCAL

class Solution {
 public:
  std::vector<std::vector<int>> spiralMatrix(int m, int n, ListNode* head) {
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));

    int rowStart = 0, colStart = 0, rowEnd = m - 1, colEnd = n - 1;
    while (rowStart <= rowEnd && colStart <= colEnd && head) {
      // top row, left to right
      for (int col = colStart; col <= colEnd && head; ++col) {
        matrix[rowStart][col] = head->val;
        head = head->next;
      }
      ++rowStart;

      // right column, top to bottom
      for (int row = rowStart; row <= rowEnd && head; ++row) {
        matrix[row][colEnd] = head->val;
        head = head->next;
      }
      --colEnd;

      // bottom row, right to left
      if (rowStart <= rowEnd) {
        for (int col = colEnd; col >= colStart && head; --col) {
          matrix[rowEnd][col] = head->val;
          head = head->next;
        }
        --rowEnd;
      }

      // left column, bottom to up
      if (colStart <= colEnd) {
        for (int row = rowEnd; row >= rowStart && head; --row) {
          matrix[row][colStart] = head->val;
          head = head->next;
        }
        ++colStart;
      }
    }

    return matrix;
  }
};
