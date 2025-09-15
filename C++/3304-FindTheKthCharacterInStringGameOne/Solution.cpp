#include <bit>

class Solution {
 public:
  char kthCharacter(int k) {
    // Start with "a".
    // Given k > 0.
    // Generate a new string by changing each character in word to its next
    // character in the alphabet, and append that character.
    // Return the value of the kth character after enough operations have been
    // done for word to have at least k characters.
    //
    // An earlier variant didnt require keeping track of the string.
    // Brute force for this constraint works.
    //
    // Notice that after each operation, the length of the string doubles.
    // Recursively, the character at the kth position is given by the
    // character at the k' position, which is given by k''...
    return std::popcount(static_cast<unsigned int>(k) - 1) + 'a';
  }
};
