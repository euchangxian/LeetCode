#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr std::string_view LINE_START{"//"};
constexpr std::string_view BLOCK_START{"/*"};
constexpr std::string_view BLOCK_END{"*/"};

auto isLineComment = [](std::string_view line, int col) {
  return col + 1 < line.size() && line.substr(col, 2) == LINE_START;
};

auto isBlockCommentStart = [](std::string_view line, int col) {
  return col + 1 < line.size() && line.substr(col, 2) == BLOCK_START;
};

auto isBlockCommentEnd = [](std::string_view line, int col) {
  return col + 1 < line.size() && line.substr(col, 2) == BLOCK_END;
};

class Solution {
 public:
  std::vector<std::string> removeComments(std::vector<std::string>& source) {
    // source[i] is the ith line of the source code, representing the result
    // of splitting the original source code string by '\n';
    // "//" represents a line comment, the characters to the right till EOL
    // should be ignored.
    // "/*" indicate the start of a block comment. All characters until the
    // next occurence of "*/" should be ignored.
    // Do not output a line if its empty.
    //
    // The issue is dealing with block comments...
    // With the implicit newlines being deleted, a currLine should be used so
    // that we can add to this buffer.
    const auto n = static_cast<int>(source.size());
    std::vector<std::string> result;
    for (int lineIdx = 0; lineIdx < n;) {
      std::string currLine;
      for (int col = 0; col < source[lineIdx].size();) {
        if (isLineComment(source[lineIdx], col)) {
          break;
        } else if (isBlockCommentStart(source[lineIdx], col)) {
          col += 2;  // to move past the "/*" pattern

          // we are guaranteed a matching */, hence no need to check lineIdx < n
          while (true) {
            if (col >= source[lineIdx].size()) {
              ++lineIdx;
              col = 0;
            }

            if (isBlockCommentEnd(source[lineIdx], col)) {
              col += 2;  // move past the "*/" pattern
              break;
            }

            ++col;
          }
        } else {
          currLine += source[lineIdx][col++];
        }
      }

      if (!currLine.empty()) {
        result.push_back(std::move(currLine));
      }
      ++lineIdx;
    }

    return result;
  }
};
