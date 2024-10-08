#include <algorithm>
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
  const vector<string> belowTen = {"",     "One", "Two",   "Three", "Four",
                                   "Five", "Six", "Seven", "Eight", "Nine"};

  const vector<string> belowTwenty = {
      "Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
      "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

  const vector<string> belowHundred = {"",       "Ten",   "Twenty", "Thirty",
                                       "Forty",  "Fifty", "Sixty",  "Seventy",
                                       "Eighty", "Ninety"};

  string toWords(int num) {
    if (num < 10) {
      return belowTen[num];
    }
    if (num < 20) {
      return belowTwenty[num - 10];
    }
    if (num < 100) {
      // account for the ones place too
      return belowHundred[num / 10] + (num % 10 ? " " + toWords(num % 10) : "");
    }
    if (num < 1000) {
      return toWords(num / 100) + " Hundred" +
             (num % 100 ? " " + toWords(num % 100) : "");
    }
    if (num < 1000000) {
      // < 1 million
      return toWords(num / 1000) + " Thousand" +
             (num % 1000 ? " " + toWords(num % 1000) : "");
    }
    if (num < 1000000000) {
      // < 1 billion
      return toWords(num / 1000000) + " Million" +
             (num % 1000000 ? " " + toWords(num % 1000000) : "");
    }

    return toWords(num / 1000000000) + " Billion" +
           (num % 1000000000 ? " " + toWords(num % 1000000000) : "");
  }

 public:
  string numberToWords(int num) {
    if (num == 0) {
      return "Zero";
    }
    return toWords(num);
  }
};
