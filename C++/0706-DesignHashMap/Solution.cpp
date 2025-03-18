#include <array>
#include <cstddef>

/**
 * Problem constraints means provisioning buckets for each possible keys will
 * still be manageable space.
 *
 * Space required: numKeys * 32  / 8 / 1024 ~= 4MB
 * Fits within a Linux stack.
 */
class MyHashMap {
 private:
  static constexpr size_t numKeys = 1000000 + 1;
  std::array<int, numKeys> set;

 public:
  MyHashMap() { set.fill(-1); }

  void put(int key, int value) { set[key] = value; }

  int get(int key) { return set[key]; }

  void remove(int key) { set[key] = -1; }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
