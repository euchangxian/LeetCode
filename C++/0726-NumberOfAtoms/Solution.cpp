#include <cctype>
#include <map>
#include <stack>
#include <string>

class Solution {
 public:
  std::string countOfAtoms(std::string formula) {
    // A( BC (DE)2 FG)3
    int n = formula.size();

    std::map<std::string, int> frequencies;
    std::stack<int> multiplicity;
    int multiplier = 1;

    std::string currentElement;
    std::string currentCount;
    int i = n - 1;
    while (i >= 0) {
      if (std::isdigit(formula[i])) {
        currentCount = formula[i] + currentCount;
      } else if (std::islower(formula[i])) {
        currentElement = formula[i] + currentElement;
      } else if (formula[i] == ')') {
        int count = 1;
        if (!currentCount.empty()) {
          count = std::stoi(currentCount);
          currentCount.clear();
        }
        multiplier *= count;
        multiplicity.push(count);
      } else if (formula[i] == '(') {
        multiplier /= multiplicity.top();
        multiplicity.pop();
      } else if (std::isupper(formula[i])) {
        int count = 1;
        if (!currentCount.empty()) {
          count = std::stoi(currentCount);
          currentCount.clear();
        }

        currentElement = formula[i] + currentElement;
        frequencies[currentElement] += count * multiplier;
        currentElement.clear();
      }
      --i;
    }

    std::string result;
    for (auto& [elem, freq] : frequencies) {
      if (freq < 2) {
        result += elem;
        continue;
      }
      result += elem + std::to_string(freq);
    }

    return result;
  }
};
