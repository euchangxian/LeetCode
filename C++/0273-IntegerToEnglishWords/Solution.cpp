#include <string>
#include <vector>

class Solution {
 public:
  std::string numberToWords(int num) {
    if (num == 0) {
      return "Zero";
    }
    return toWords(num);
  }

  const std::vector<std::string> belowTen = {"",      "One",  "Two", "Three",
                                             "Four",  "Five", "Six", "Seven",
                                             "Eight", "Nine"};

  const std::vector<std::string> belowTwenty = {
      "Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
      "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

  const std::vector<std::string> belowHundred = {
      "",      "Ten",   "Twenty",  "Thirty", "Forty",
      "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

  std::string toWords(int num) {
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
};
