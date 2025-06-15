#include <array>
#include <charconv>

class Solution {
 public:
  int maxDiff(int num) {
    // apply two times independently:
    // - pick a digit 0 <= x <= 9
    // - pick another digit 0 <= y <= 9
    // - Replace all occurences of x in the decimal representation of num by y.
    // Let a and b be the result from applying independently.
    // Return the max difference. Neither may have any leading zeroes, and
    // must not be 0.
    // That means the leading digit cannot be greedily changed to 0 to obtain
    // the minimum. So, change the first non-one to 1?
    // No. if the first digit is not one, then change to one. Else, change the
    // next non-one to zeroes.
    // For maximum, can still be greedily changed to 9
    std::array<char, 10> buffer;
    auto result =
        std::to_chars(buffer.data(), buffer.data() + buffer.size(), num);
    const int n = result.ptr - buffer.data();

    auto small = [&]() {
      int result = 0;
      int i = 0;
      if (buffer.front() == '1') {
        while (i < n && (buffer[i] == '1' || buffer[i] == '0')) {
          result = (result * 10) + (buffer[i] - '0');
          ++i;
        }

        // map first non-1 to 0
        char map = buffer[i];
        while (i < n) {
          result *= 10;
          if (buffer[i] == map) {
            result += 0;
          } else {
            result += buffer[i] - '0';
          }
          ++i;
        }
        return result;
      }

      char map = buffer[i];
      while (i < n) {
        result *= 10;
        if (buffer[i] == map) {
          result += 1;
        } else {
          result += buffer[i] - '0';
        }
        ++i;
      }
      return result;
    }();

    auto big = [&]() {
      int result = 0;
      int i = 0;

      while (i < n && buffer[i] == '9') {
        result = (result * 10) + (buffer[i] - '0');
        ++i;
      }

      char map = buffer[i];
      while (i < n) {
        result *= 10;
        if (buffer[i] == map) {
          result += 9;
        } else {
          result += buffer[i] - '0';
        }
        ++i;
      }
      return result;
    }();

    return big - small;
  }
};
