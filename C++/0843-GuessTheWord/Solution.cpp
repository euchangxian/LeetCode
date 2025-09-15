#include <random>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#ifdef LOCAL
class Master {
 public:
  int guess(std::string);
};
#endif

constexpr int ALLOWED_GUESSES = 30;
class Solution {
 public:
  void findSecretWord(std::vector<std::string>& words, Master& master) {
    // Given a set of words, each word is 6 letters long.
    // One word is chosen as the secret.
    // Given Master.guess(word), which returns:
    // - -1 if word is not from words,
    // - integer representing the number of exact matches (value and position)
    //   of your guess to the secret word.
    // There is an allowedGuess parameter (where??).
    //
    // What is the strategy?
    // Brute Force would be to guess each word?? words.size() times.
    // We already have quite a big advantage given that we have all the possible
    // words in the set.
    // All lowercase makes it easier too.
    //
    // Naively, gather the frequency of characters at each position.
    // But how can we eliminate?
    // NOTE: we must guess a word from the given list. Not any arbitrary
    // combination of characters.
    //
    // when we get x = master.guess(word), we know that word must match
    // exactly x characters in the secret word.
    // We can eliminate words from our pool of candidate.
    // Iteratively do so, picking a random word each time.
    constexpr auto isCandidate = [](std::string_view guessed,
                                    std::string_view word,
                                    int requiredMatches) {
      int matches = 0;
      for (int i = 0; i < 6; ++i) {
        matches += guessed[i] == word[i];
      }
      return matches == requiredMatches;
    };

    std::mt19937 gen{std::random_device{}()};
    auto getRandomCandidate = [&gen](std::vector<std::string>& candidates) {
      std::uniform_int_distribution<> dist{
          0, static_cast<int>(candidates.size()) - 1};
      auto idx = dist(gen);
      return candidates[idx];
    };

    for (int i = 0; i < ALLOWED_GUESSES; ++i) {
      auto guess = getRandomCandidate(words);
      auto x = master.guess(guess);
      if (x == 6) {
        break;
      }

      std::vector<std::string> nextCandidates;
      nextCandidates.reserve(words.size());
      for (auto& word : words) {
        if (isCandidate(guess, word, x)) {
          nextCandidates.emplace_back(std::move(word));
        }
      }
      words = std::move(nextCandidates);
    }
  }
};
