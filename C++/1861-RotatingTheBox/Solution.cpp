#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<char>> rotateTheBox(
      std::vector<std::vector<char>>& box) {
    // Hm. Seems like two pointers. The output dimensions is a transpose of the
    // input.
    //
    // Initialize the output n x m.
    // Then, initialize two pointers i_in, i_out, to the last position of the
    // first row and the last position of the first column respectively.
    //
    // Check i_in. If i_in is a stone, move the stone to i_out, advance both
    // pointers.
    // If i_in is a obstacle, then advance i_out to the corresponding index of
    // i_in in the output, where if i_in = (r, c), then i_out = (c, r), i.e.,
    // move i_out to the column pointed to by i_in.
    // If i_in is an empty space, then advance i_in only.
    //
    // Repeat for all columns in the new output.
    // Tricky(?) part is the rotation.
    // (r, c) --rotate 90degrees-> (c, m - 1 - r)
    const std::size_t rows = box.size();
    const std::size_t cols = box[0].size();
    std::vector<std::vector<char>> rotated(cols,
                                           std::vector<char>(rows, EMPTY));

    // for each row in the input grid (which corresponds to the columns in the
    // output grid)
    for (int r = 0; r < rows; ++r) {
      int writeRow = cols - 1;
      for (int c = cols - 1; c >= 0; --c) {
        if (box[r][c] == STONE) {
          // 90 degrees: (r, c) --> (c, rows - 1 - r)
          rotated[writeRow][rows - 1 - r] = STONE;
          --writeRow;
          continue;
        }

        if (box[r][c] == OBSTACLE) {
          // Obstacles stay in the rotated position.
          rotated[c][rows - 1 - r] = OBSTACLE;
          writeRow = c - 1;
        }

        // EMPTY case already handled by initialization, just move the read
        // pointer, i.e,. --c.
      }
    }

    return rotated;
  }

 private:
  static constexpr char STONE = '#';
  static constexpr char OBSTACLE = '*';
  static constexpr char EMPTY = '.';
};
