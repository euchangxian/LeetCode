#include <algorithm>
#include <cstddef>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;
/**
 * Insert is almost always trivial to get constant time.
 * A set data structure can be used to determine set inclusion.
 *
 * GetRandom is difficult. To getRandom in O(1), an underlying array data
 * structure should be used, so that rand(0, arr.size()-1) can be used to get
 * a random IDx and return the value at that index.
 *
 * As such, remove is made complicated, since random removal from an array is
 * not so straightforward.
 *
 * However, taking inspiration from heaps, we can swap the element to be removed
 * to the back and pop it.
 *
 * A map data structure can be used to determine the index of the to-remove
 * element.
 *
 * In conclusion, use a vector and an unordered_map.
 *
 */
class RandomizedSet {
 private:
  vector<int> nums;
  unordered_map<int, int> indices;

  std::mt19937 gen;

 public:
  RandomizedSet() : gen(std::random_device{}()) {}

  bool insert(int val) {
    if (indices.count(val)) {
      return false;
    }

    nums.push_back(val);
    indices[val] = nums.size() - 1;
    return true;
  }

  bool remove(int val) {
    if (indices.count(val) == 0) {
      return false;
    }

    const int idx = indices[val];

    // update the to-be-swapped element's index
    indices[nums.back()] = indices[val];

    swap(nums[idx], nums.back());
    nums.pop_back();
    indices.erase(val);

    return true;
  }

  int getRandom() {
    std::uniform_int_distribution<> distr(0, nums.size() - 1);
    return nums[distr(gen)];
  }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
