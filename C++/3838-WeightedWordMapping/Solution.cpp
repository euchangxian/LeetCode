#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::string mapWordWeights(std::vector<std::string>& words,
                             std::vector<int>& weights) {
    // Given a list of words.
    // weights[i] represent the weight of the ith lowercase letter.
    // Weight of a word = sum of the weights.
    // For each word, take its weight mod26, map the result to an english
    // lowercase letter using reverse alphabetical order.
    // Return the concatenated mapped characters.
    auto map = [&weights](std::string_view word) {
      auto sum = 0;
      for (char c : word) {
        sum += weights[c - 'a'];
      }

      sum = 25 - (sum % 26);
      return static_cast<char>(sum + 'a');
    };

    std::string result;
    for (std::string_view word : words) {
      result += map(word);
    }
    return result;
  }
};
