#include <bitset>
#include <cstddef>

/**
 * Lol. Given the constraints of this problem, where 0 <= key <= 10^6, there is
 * more than enough space to accomodate all possible keys without having to
 * hash.
 * Since no values need to be stored, a BitSet is sufficient.
 * The size of the bitset would simply be 1,000,001 bits, 126 bytes, or 0.2KB,
 * well within the conventional size of a Stack on Linux (8MB).
 */
class MyHashSet {
 private:
  static constexpr size_t numKeys = 1000000 + 1;
  std::bitset<numKeys> set;  // not hashset. just set!

 public:
  MyHashSet() : set{} {}

  void add(int key) { set.set(key); }

  void remove(int key) { set.reset(key); }

  bool contains(int key) { return set.test(key); }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
