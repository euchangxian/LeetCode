#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class ValidWordAbbr {
 public:
  ValidWordAbbr(std::vector<std::string>& dictionary) {
    for (const std::string& word : dictionary) {
      dict[abbreviate(word)].insert(word);
    }
  }

  bool isUnique(std::string word) {
    std::string abbrev = abbreviate(word);

    auto iter = dict.find(abbrev);
    if (iter == dict.end()) {
      // abbreviation is not in the dictionary
      return true;
    }

    if (iter->second.count(word) && iter->second.size() == 1) {
      // abbreviation is in the dictionary, and the word is the only one
      // with that abbreviation
      return true;
    }

    return false;
  }

 private:
  std::unordered_map<std::string, std::unordered_set<std::string>> dict;

  std::string abbreviate(const std::string& word) {
    const size_t len = word.length();
    std::string key;
    key += word.front();
    if (len > 2) {
      key += std::to_string(len);
    }

    if (len > 1) {
      key += word.back();
    }

    return key;
  }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
