#include <cstddef>
#include <string>

using namespace std;
class StringIterator {
  char c;
  int repeats;

  const std::string compressedString;
  size_t idx;

 public:
  // No need to check
  StringIterator(string compressedString)
      : c(' '),
        repeats(0),
        compressedString(std::move(compressedString)),
        idx(0) {}

  char next() {
    // the compressed string has the format CharDigit
    if (!hasNext()) {
      return ' ';
    }

    if (repeats > 0) {
      --repeats;
      return c;
    }

    // Otherwise, there is no more repeats.
    // Advance the iterator, parse the next set of characters..
    // There is no need to check that the iterator is at the end. Covered by
    // the hasNext check above.
    c = compressedString[idx++];

    // parse the number of repeats
    while (isdigit(compressedString[idx])) {
      repeats = (repeats * 10) + (compressedString[idx++] - '0');
    }
    --repeats;
    return c;
  }

  bool hasNext() { return repeats > 0 || idx < compressedString.length(); }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
