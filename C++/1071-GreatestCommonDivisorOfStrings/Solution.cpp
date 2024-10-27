#include <cstddef>
#include <string>
#include <string_view>

using namespace std;
class Solution {
 private:
  int euclidsGCD(int a, int b) {
    if (b == 0) {
      return a;
    }

    return euclidsGCD(b, a % b);
  }

 public:
  string gcdOfStrings(string_view str1, string_view str2) {
    // This whole part is just to avoid allocation.
    const size_t total = str1.size() + str2.size();
    std::string concat1;
    concat1.reserve(total);
    concat1.append(str1);
    concat1.append(str2);

    std::string concat2;
    concat2.reserve(total);
    concat2.append(str2);
    concat2.append(str1);

    if (concat1 != concat2) {
      return "";
    }

    int gcd = euclidsGCD(str1.length(), str2.length());
    string_view gcdStr = str1.substr(0, gcd);

    return std::string(gcdStr.begin(), gcdStr.end());
  }
};
