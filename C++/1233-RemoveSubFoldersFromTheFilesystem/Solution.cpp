#include <algorithm>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

using namespace std;
class Solution {
 private:
  bool isSubFolderOf(string_view f1, string_view f2) {
    // No need to check length validity. The input array will be sorted.
    // Append a '/' to f1, then check if f2 has f1 as prefix.
    // The prefix check could be done using C++20 std::string::starts_with
    // Alternatively, use std::mismatch, or std::string::compare
    bool isPrefix = f2.compare(0, f1.size(), f1) == 0;

    // Check existence of '/'
    bool isSubFolder =
        isPrefix && (f2.size() >= f1.size() + 1) && (f2[f1.size()] == '/');
    return isSubFolder;
  }

 public:
  vector<string> removeSubfolders(vector<string>& folder) {
    // The input is an array of strings representing the full path to a folder.
    // To remove all folders which are nested in other folders.
    // The root folder "/" is not valid in this context.
    // More precisely, folder[j] is a subfolder of folder[i] if folder[j] starts
    // with folder[i].
    // At first glance, sorting the input, then comparing prefixes seem to solve
    // this problem.
    // I.e., sort, then have a pointer i starting from 0. This represents the
    // top-level folder.
    // for j in [1..n]:
    //   if folder[j] has prefix folder[i]; then remove j
    //   else i += 1 // because there are no nested folders in this top-level.
    //
    // There are a few edge cases. Mainly on the prefix comparison.
    // E.g., "/a/b/c", "/a/b/ca". Both are not subfolders of each other.
    // The key is to add a '/' to the prefix, then compare.
    const size_t n = folder.size();
    std::sort(folder.begin(), folder.end());

    std::vector<string> topLevelFolders;
    topLevelFolders.reserve(n);
    topLevelFolders.emplace_back(folder[0]);
    for (size_t i = 1; i < n; ++i) {
      if (isSubFolderOf(topLevelFolders.back(), folder[i])) {
        continue;
      }
      topLevelFolders.emplace_back(folder[i]);
    }
    return topLevelFolders;
  }
};
