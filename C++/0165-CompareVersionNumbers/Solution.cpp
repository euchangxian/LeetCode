#include <string_view>

class Solution {
 public:
  int compareVersion(std::string_view version1, std::string_view version2) {
    // Give two version strings, compare them.
    // The value of the revision is its integer conversion ignoring leading
    // zeroes.
    // Empty revision strings are treated as 0.
    // if version1 < version2 -> return -1
    // if version1 > version2 -> return 1
    // else return 0
    auto getNextRevision = [](std::string_view version, int& idx) {
      if (idx >= version.size()) {
        return 0;
      }

      while (idx < version.size() && version[idx] == '0') {
        // skip leading zeroes.
        ++idx;
      }

      int parsed = 0;
      while (idx < version.size() && version[idx] != '.') {
        parsed = (parsed * 10) + (version[idx] - '0');
        ++idx;
      }

      ++idx;  // skip '.'
      return parsed;
    };

    int idx1 = 0;
    int idx2 = 0;
    while (idx1 < version1.size() || idx2 < version2.size()) {
      auto revision1 = getNextRevision(version1, idx1);
      auto revision2 = getNextRevision(version2, idx2);

      if (revision1 < revision2) {
        return -1;
      }
      if (revision1 > revision2) {
        return 1;
      }
    }
    return 0;
  }
};
