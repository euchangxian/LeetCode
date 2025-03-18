#include <cstddef>
#include <set>
#include <unordered_map>

/**
 * Seems to be a many-to-one relationship between Buckets/Containers and
 * Numbers.
 * Each Container can store only one Number, but each Number may be stored in
 * multiple Containers.
 *
 * 1 <= index, number <= 10^9. => 4MB of integers possible => unordered_map
 * should be used instead of an array.
 *
 * Naively, seems like two unordered_map is sufficient.
 * One for bucket -> number
 * The other for number -> {bucket1, ...}
 *
 * For the number -> buckets, use an ordered Set.
 */
class NumberContainers {
 public:
  NumberContainers() {}

  void change(int index, int number) {
    auto iter = containers.find(index);
    if (iter != containers.end()) {
      int original = iter->second;
      numbers[original].erase(index);

      if (numbers[original].empty()) {
        numbers.erase(original);
      }
    }
    containers[index] = number;
    numbers[number].insert(index);
  }

  int find(int number) {
    auto iter = numbers.find(number);
    if (iter == numbers.end()) {
      return -1;
    }

    return *(iter->second).begin();
  }

 private:
  std::unordered_map<int, int> containers;
  std::unordered_map<int, std::set<int>> numbers;
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
