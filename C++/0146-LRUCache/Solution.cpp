#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class LRUCache {
private:
  struct Node {
    int key;
    int value;
    Node *next;
    Node *prev;

    Node(int key, int value)
        : key(key), value(value), next(nullptr), prev(nullptr) {}
  };

  const int capacity;

  // Dummy nodes to simplify nullptr checks
  Node *lru;
  Node *mru;

  unordered_map<int, Node *> cache;

  void remove(Node *node) {
    (node->prev)->next = node->next;
    (node->next)->prev = node->prev;
    return;
  }

  void insert(Node *node) {
    node->prev = mru->prev;
    node->next = mru;
    (mru->prev)->next = node;
    mru->prev = node;
  }

public:
  LRUCache(int capacity)
      : capacity(capacity), lru(new Node(-1, -1)), mru(new Node(-1, -1)) {
    lru->next = mru;
    mru->prev = lru;
  }

  int get(int key) {
    if (!cache.count(key)) {
      return -1;
    }

    remove(cache[key]);
    insert(cache[key]);
    return cache[key]->value;
  }

  void put(int key, int value) {
    if (cache.size() >= capacity && !cache.count(key)) {
      Node *evict = lru->next;
      remove(evict);
      cache.erase(evict->key);
      delete evict;
    }

    if (cache.count(key)) {
      remove(cache[key]);
      delete cache[key];
    }
    // Redundant reconstruction if the key was already present, but
    // acceptable trade-off for cleaner code
    cache[key] = new Node(key, value);
    insert(cache[key]);
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
