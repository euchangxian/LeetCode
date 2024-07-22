#include <cctype>
#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;
class Solution {
public:
  string countOfAtoms(string formula) {
    // A( BC (DE)2 FG)3
    int n = formula.size();

    map<string, int> frequencies;
    stack<int> multiplicity;
    int multiplier = 1;

    string currentElement;
    string currentCount;
    int i = n - 1;
    while (i >= 0) {
      if (isdigit(formula[i])) {
        currentCount = formula[i] + currentCount;
      } else if (islower(formula[i])) {
        currentElement = formula[i] + currentElement;
      } else if (formula[i] == ')') {
        int count = 1;
        if (!currentCount.empty()) {
          count = stoi(currentCount);
          currentCount.clear();
        }
        multiplier *= count;
        multiplicity.push(count);
      } else if (formula[i] == '(') {
        multiplier /= multiplicity.top();
        multiplicity.pop();
      } else if (isupper(formula[i])) {
        int count = 1;
        if (!currentCount.empty()) {
          count = stoi(currentCount);
          currentCount.clear();
        }

        currentElement = formula[i] + currentElement;
        frequencies[currentElement] += count * multiplier;
        currentElement.clear();
      }
      --i;
    }

    string result;
    for (auto &[elem, freq] : frequencies) {
      if (freq < 2) {
        result += elem;
        continue;
      }
      result += elem + to_string(freq);
    }

    return result;
  }
};

int main(int argc, char *argv[]) {
  cout << Solution().countOfAtoms("H2O") << endl;
  cout << Solution().countOfAtoms("Mg(OH)2") << endl;
  cout << Solution().countOfAtoms("K4(ON(SO3)2)2") << endl;
  return 0;
}
