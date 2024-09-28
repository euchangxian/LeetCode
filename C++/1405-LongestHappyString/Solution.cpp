#include <cstdint>
#include <string>

using std::string, std::min;
class Solution {
private:
  string generate(int largePile, int mediumPile, int smallPile, char largeChar,
                  char mediumChar, char smallChar) {
    // Re-order the piles first.
    if (largePile < mediumPile) {
      return generate(mediumPile, largePile, smallPile, mediumChar, largeChar,
                      smallChar);
    }

    if (mediumPile < smallPile) {
      return generate(largePile, smallPile, mediumPile, largeChar, smallChar,
                      mediumChar);
    }

    // Base case, no more padding. The above are preconditions.
    // This is because if mediumPile is 0, that means smallPile must also be 0.
    if (mediumPile == 0) {
      return string(min(2, largePile), largeChar);
    }

    const int32_t takeLargest = min(2, largePile);

    // Only pad with the mediumPile if, after taking from the largePile, the
    // largePile is still larger.
    const int32_t takeMedium = largePile - takeLargest >= mediumPile ? 1 : 0;

    return string(takeLargest, largeChar) + string(takeMedium, mediumChar) +
           generate(largePile - takeLargest, mediumPile - takeMedium, smallPile,
                    largeChar, mediumChar, smallChar);
  }

public:
  string longestDiverseString(int a, int b, int c) {
    return generate(a, b, c, 'a', 'b', 'c');
  }
};
