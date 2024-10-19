#include <algorithm>
#include <cstddef>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Since duplicates are allowed, the map of indices must be modified
 * slightly. Either using C++ multimap or a map to vectors. Since we want to
 * maintain the order of insertion somewhat, because when we check the last
 * element's index, in case there are multiple elements that have the same
 * value, we can easily find the correct entry.
 *
 * However, to achieve this, we can use a map of sets instead. This allows O(1)
 * erase on a specific index; in this case, we want to erase the entry of the
 * last idx.
 */
class RandomizedCollection {
 private:
  std::vector<int> nums;
  std::unordered_map<int, std::unordered_set<int>> indices;

  std::mt19937 gen;

 public:
  RandomizedCollection() : gen(std::random_device{}()) {}

  bool insert(int val) {
    bool notPresent = !indices.count(val);

    nums.push_back(val);
    indices[val].insert(nums.size() - 1);
    return notPresent;
  }

  bool remove(int val) {
    if (!indices.count(val)) {
      return false;
    }

    const int valIdx = *indices[val].begin();
    indices[val].erase(valIdx);
    indices[nums.back()].insert(valIdx);  // update the to-be-swapped idx
    indices[nums.back()].erase(nums.size() - 1);  // order is important

    if (indices[val].empty()) {
      indices.erase(val);
    }

    if (indices.find(nums.back()) != indices.end() &&
        indices[nums.back()].empty()) {
      indices.erase(nums.back());
    }

    std::swap(nums[valIdx], nums.back());
    nums.pop_back();
    return true;
  }

  int getRandom() {
    std::uniform_int_distribution<> distr(0, nums.size() - 1);
    return nums[distr(gen)];
  }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
