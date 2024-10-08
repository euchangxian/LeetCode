#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
  bool isPalindrome(const string& s, int start, int end) {
    // Return true if the substring s[start:end] (inclusive) is a palindrome.
    while (start <= end) {
      if (s[start] != s[end]) {
        return false;
      }
      ++start;
      --end;
    }
    return true;
  }

  vector<int> kmpPrefixTable(const string& pattern) {
    const size_t m = pattern.length();

    // Longest Proper Prefix which is also a suffix
    vector<int> lps(m, 0);

    // Base case. The substring s[0] will not have a proper prefix / suffix
    lps[0] = 0;  // Not necessary since we initialized to 0. For explicitness

    for (int i = 1; i < m; ++i) {
      int length = lps[i - 1];

      // While the suffix does not match the prefix, look for a shorter prefix
      while (length > 0 && pattern[i] != pattern[length]) {
        length = lps[length - 1];
      }

      if (pattern[i] == pattern[length]) {
        ++length;
      }

      lps[i] = length;
    }

    return lps;
  }

 public:
  string shortestPalindrome(string s) {
    // The problem is finding the longest palindromic prefix.
    // The key to this is using KMP to find the palindromic prefix efficiently.
    //
    // KMP builds an array, LPS (Longest Proper Prefix which is also Suffix).
    // LPS[i] represents the length of the longest proper prefix of of the
    // substring s[0..i] which is also a suffix of this substring.
    //
    // E.g., for a pattern:     "ABABCABAB",
    // the substring at i=7 is: "ABABCABA"
    // LPS[7]=3 because "ABA" is the longest proper prefix that is also a suffix
    //
    // Given the definition of a Palindrome, whose prefix is equal to its
    // suffix, we can construct a string combined =  s + '#' + reverse(s).
    // This allows us to use KMP to find the longest proper prefix, of this
    // string combined, which will tell us the longest palindromic prefix.
    const size_t n = s.length();

    string reversed = string(s.rbegin(), s.rend());
    string combined = s + '#' + reversed;
    vector<int> prefixTable = kmpPrefixTable(combined);

    int longestPrefixPalindromeLength = prefixTable.back();

    // Get the suffix after the longest palindromic prefix, in reverse order.
    string prepend = reversed.substr(0, n - longestPrefixPalindromeLength);

    // Add to the front of the original string
    return prepend + s;
  }

  string shortestPalindromeTLE(string s) {
    // Naively, check each substring s[:i]. If s[:i] is a palindrome, then
    // add s[i:] (which violates the palindromic property) to the front of
    // the string in reverse order.
    const size_t n = s.length();

    int i = n - 1;
    while (i < n && !isPalindrome(s, 0, i)) {
      --i;
    }

    if (i == n - 1) {
      return s;
    }

    string palindrome = s.substr(i);
    reverse(palindrome.begin(), palindrome.end());

    return palindrome + s.substr(0, i);
  }
};
