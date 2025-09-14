#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  std::vector<std::string> spellchecker(std::vector<std::string>& wordlist,
                                        std::vector<std::string>& queries) {
    // Implement a spellchecker that converts a query word into a correct word.
    // For a given query, the spellchecker handles Capitalization and Vowel
    // mistakes.
    // Capitalization: if the query matches a word in the wordlist
    // (case-insensitive), then the query word is returned with the same case
    // as specified in the wordlist.
    // Vowel: if after replacing the vowels of the query with any vowel
    // individually, it matches a word in the wordlist, return the matched.
    // Precedence:
    // - Match case-sensitively => return same word
    // - Match capitalization => return first match in the wordlist.
    // - Match vowel errors => return first match
    // - Otherwise, empty string.
    // Return answer[i] = matched word.
    //
    // To check capitalization, use a hashtable storing lower-cased word -> idx
    // Lookup the lowercased variants of each query.
    // Hm. Not correct.
    // First store the exact wordlist. This allows us to meet the first
    // precedent requirement.
    constexpr auto toLower = [](std::string_view word) {
      std::string result;
      result.reserve(word.size());
      for (char c : word) {
        result += std::tolower(c);
      }
      return result;
    };

    constexpr auto substituteVowels = [](std::string_view word) {
      std::string result;
      result.reserve(word.size());
      for (char c : word) {
        c = std::tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
          c = '#';
        }
        result += c;
      }
      return result;
    };

    std::unordered_set<std::string_view> words;
    words.reserve(wordlist.size());
    std::unordered_map<std::string, std::string_view> lowerCased, wildcardVowel;
    lowerCased.reserve(wordlist.size()), wildcardVowel.reserve(wordlist.size());
    for (std::string_view word : wordlist) {
      words.emplace(word);
      auto lower = toLower(word);
      lowerCased.emplace(lower, word);

      auto wildcard = substituteVowels(word);
      wildcardVowel.emplace(wildcard, word);
    }

    for (auto& query : queries) {
      if (words.contains(query)) {
        continue;
      }

      if (auto lower = toLower(query); lowerCased.contains(lower)) {
        query = std::string{lowerCased[lower]};
      } else if (auto wildcard = substituteVowels(query);
                 wildcardVowel.contains(wildcard)) {
        query = std::string{wildcardVowel[wildcard]};
      } else {
        query = "";
      }
    }
    return queries;
  }
};
