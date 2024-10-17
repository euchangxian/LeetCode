#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class ValidWordAbbr {
 private:
  unordered_map<string, unordered_set<string>> dict;

  string abbreviate(const string& word) {
    const size_t len = word.length();
    string key;
    key += word.front();
    if (len > 2) {
      key += to_string(len);
    }

    if (len > 1) {
      key += word.back();
    }

    return key;
  }

 public:
  ValidWordAbbr(vector<string>& dictionary) {
    for (const string& word : dictionary) {
      dict[abbreviate(word)].insert(word);
    }
  }

  bool isUnique(string word) {
    string abbrev = abbreviate(word);

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
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
