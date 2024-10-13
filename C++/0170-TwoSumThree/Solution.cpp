#include <cstddef>
#include <unordered_map>

using namespace std;
/**
 * Naively, add() can just add the number to a hashmap in constant time.
 * find() can then implement the two-sum algorithm which runs in linear time.
 * Can we do better?
 */
class TwoSum {
 private:
  std::unordered_map<long long, int> occurences;

 public:
  TwoSum() {}

  void add(int number) { ++occurences[number]; }

  bool find(int value) {
    for (const auto& [num, occurence] : occurences) {
      const long long complement = static_cast<long long>(value) - num;

      auto it = occurences.find(complement);
      if (it == occurences.end()) {
        continue;
      }

      if (num != complement) {
        return true;
      }

      // case where the current num and the complement is the same.
      if (occurence > 1) {
        return true;
      }
    }
    return false;
  }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */
