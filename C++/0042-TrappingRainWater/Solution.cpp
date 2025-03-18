#include <stack>
#include <vector>

class Solution {
 public:
  // Water cannot be trapped at boundaries
  int trap(const std::vector<int>& height) {
    if (height.size() < 3) {
      return 0;
    }

    int l = 0;
    int r = height.size() - 1;

    int leftBoundary = height[l];
    int rightBoundary = height[r];
    int result = 0;
    while (l < r) {
      // if-checks guarantee somewhat of a monotonic property.
      if (leftBoundary < rightBoundary) {
        leftBoundary = std::max(leftBoundary, height[++l]);
        result += leftBoundary - height[l];
      } else {
        rightBoundary = std::max(rightBoundary, height[--r]);
        result += rightBoundary - height[r];
      }
    }
    return result;
  }

  int trapStack(std::vector<int>& height) {
    if (height.size() < 3) {
      return 0;  // Water cannot be trapped
    }

    // Monotonically non-increasing stack (same or decreasing)
    std::stack<int> indices;
    int result = 0;
    for (int i = 0; i < height.size(); ++i) {
      if (indices.empty() || height[i] <= height[indices.top()]) {
        indices.push(i);
        continue;
      }

      while (!indices.empty() && height[i] > height[indices.top()]) {
        int popIndex = indices.top();
        indices.pop();

        // Handle boundaries (literally edge cases) and adjacent bars.
        if (indices.empty()) {
          break;
        }

        int leftBoundaryIndex = indices.top();
        // Take the min of the leftBoundary and rightBoundary (height[i]),
        // minus the depth of the poppedIndex, then multiply by the distance
        // between the left and right bounds. Visualize it as adding horizontal
        // layers of water instead of vertical layers.
        result += (std::min(height[leftBoundaryIndex], height[i]) -
                   height[popIndex]) *
                  (i - leftBoundaryIndex - 1);
      }

      indices.push(i);
    }

    return result;
  }
};
