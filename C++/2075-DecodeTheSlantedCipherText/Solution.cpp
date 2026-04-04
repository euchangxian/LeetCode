#include <string>
#include <string_view>

class Solution {
 public:
  std::string decodeCiphertext(std::string_view encodedText, int rows) {
    // originalText is placed in a top-left to bottom-right manner.
    // i.e., fill out the diagonals, left-to-right.
    // The number of columns in the 2D matrix is chosen such that the
    // bottom-right cell will be non-empty.
    //
    // - Whitespaces are valid characters and must be restored.
    // - the number of filled-in whitespaces between words is always 3? Nope.
    const auto n = static_cast<int>(encodedText.size());
    auto cols = n / rows;
    std::string result;
    result.reserve(n);

    for (int c = 0; c < cols; ++c) {
      for (int r = 0; r < rows; ++r) {
        // text is 2D encoded as 1D.
        auto offsetCol = c + r;
        if (offsetCol >= cols) {
          continue;
        }
        auto idx = r * cols + offsetCol;
        result += encodedText[idx];
      }
    }

    // remove trailing
    while (!result.empty() && result.back() == ' ') {
      result.pop_back();
    }
    return result;
  }
};
