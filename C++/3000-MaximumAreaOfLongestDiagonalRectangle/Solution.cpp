#include <algorithm>
#include <vector>

class Solution {
 public:
  int areaOfMaxDiagonal(std::vector<std::vector<int>>& dimensions) {
    // dimensions[i] = {length, width}
    // Return area of longest diagonal.
    //
    // Diagonal = sqrt(length^2 + width^2)
    // Therefore, proportional to their square.
    auto maxRect =
        *std::max_element(dimensions.begin(), dimensions.end(),
                          [](const auto& dim1, const auto& dim2) {
                            auto diag1 = dim1[0] * dim1[0] + dim1[1] * dim1[1];
                            auto diag2 = dim2[0] * dim2[0] + dim2[1] * dim2[1];
                            if (diag1 != diag2) {
                              return diag1 < diag2;
                            }

                            auto area1 = dim1[0] * dim1[1];
                            auto area2 = dim2[0] * dim2[1];
                            return area1 < area2;
                          });
    return maxRect[0] * maxRect[1];
  }
};
