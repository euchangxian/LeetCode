#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
template <typename Key, typename Value> class LRUCache {
  // Can be thought of as the ListNode
  // typename is used to specify that the identifier that follows is a type
  using ListIterator = typename list<pair<Key, Value>>::iterator;
  using MapIterator = typename unordered_map<Key, ListIterator>::iterator;

private:
  // Capacity of the LRU Cache. Items are evicted using the Least-Recently-Used
  // strategy if the number of items exceed the capacity
  size_t const capacity;

  // Map Keys to their Values. A std::list::iterator is used to encapsulate
  // information such as the Key for the LRU strategy.
  unordered_map<Key, ListIterator> cache;

  // List to maintain information on insertion order. The front item is the
  // Least-Recently-Used, while the back is the Most-Recently-Used
  list<pair<Key, Value>> lru;

public:
  LRUCache<Key, Value>(size_t capacity) : capacity(capacity) {}

  optional<Value> get(Key const &key) {
    MapIterator found = cache.find(key);
    if (found == cache.end()) {
      return nullopt;
    }

    // Move the Item to the back of the list
    // unordered_map<..>::iterator->second represents the ListIterator
    lru.splice(lru.end(), lru, found->second);

    // Return the value stored in the pair
    return (found->second)->second;
  }

  void put(Key const &key, Value const &value) {
    MapIterator found = cache.find(key);

    if (found != cache.end()) {
      // If its already in the cache, then update the value, move the node to
      // the back
      ListIterator mru = found->second;
      mru->second = value;
      lru.splice(lru.end(), lru, mru);
      return;
    }

    // Otherwise, check if the cache is already at capacity. Evict if so.
    if (cache.size() >= capacity) {
      cache.erase(lru.front().first);
      lru.pop_front();
    }

    lru.emplace_back(key, value);
    cache.emplace(key, std::prev(lru.end()));
    return;
  }

  void erase(Key const &key) {
    MapIterator found = cache.find(key);
    if (found == cache.end()) {
      throw runtime_error("key does not exist");
    }

    ListIterator node = found->second;
    lru.erase(node);
    cache.erase(key);
  }

  pair<int, int> front() { return lru.front(); }

  void pop_front() {
    cache.erase(lru.front().first);
    lru.pop_front();
  }

  bool empty() { return cache.size() == 0; }
};

class LFUCache {
private:
  size_t capacity;

  // key: {value, frequency}
  unordered_map<int, pair<int, uint32_t>> cache;

  // frequency: {key1, key2}
  // Used for quick lookups for the Key that has the least frequency
  // Can be visualized as a sorted, multi-level set of lists
  unordered_map<int, LRUCache<int, int> *> frequency;

  // Stores the minimum frequency in the cache.
  uint32_t minFreq;

  // Helper function to safely insert a key with {value, freq}
  void insert(int key, int value, uint32_t freq) {
    if (!frequency.count(freq)) {
      frequency[freq] = new LRUCache<int, int>(capacity);
    }
    frequency[freq]->put(key, value);
    cache[key] = {value, freq};
  }

public:
  LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

  int get(int key) {
    auto const foundIter = cache.find(key);
    if (foundIter == cache.end()) {
      // If the key is not in the cache
      return -1;
    }

    // Erase the key from the current frequency list, since it no longer has
    // the same frequency
    uint32_t freq = (foundIter->second).second;
    frequency[freq]->erase(key);

    // Check if the given frequency bucket still has nodes.
    if (frequency[freq]->empty()) {
      frequency.erase(freq);

      // Update minFreq if necessary
      if (minFreq == freq) {
        ++minFreq;
      }
    }

    int value = (foundIter->second).first;
    ++foundIter->second.second;

    insert(key, value, freq + 1);
    return value;
  }

  void put(int key, int value) {
    auto const foundIter = cache.find(key);
    if (foundIter != cache.end()) {
      // If already in the cache, update the value and the frequency
      (foundIter->second).first = value;
      this->get(key);
      return;
    }

    // check if capacity is exceeded
    if (cache.size() >= capacity) {
      // evict the lowest frequency, least recently used node.
      cache.erase(frequency[minFreq]->front().first);
      frequency[minFreq]->pop_front();

      if (frequency[minFreq]->empty()) {
        frequency.erase(minFreq);
      }
    }

    // Update minFreq. Since this is a newly added node, minFreq can be set to 1
    minFreq = 1;
    insert(key, value, 1);
  }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
