#include <cstdint>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

using std::string, std::string_view, std::unordered_map, std::unordered_set,
    std::list, std::pair;
class AllOne {
private:
  unordered_map<string, list<pair<int32_t, unordered_set<string>>>::iterator>
      frequency;

  list<pair<int32_t, unordered_set<string>>> minmax;

public:
  AllOne() {}

  void inc(string key) {
    auto mapIter = frequency.find(key);
    if (mapIter == frequency.end()) {
      // If the key does not already exist, create a new ListNode
      // The safety of the minmax.front().front() check can only be guaranteed
      // if the lists are erased when empty
      if (minmax.empty() || minmax.front().first > 1) {
        // insert new node if there is not already a list header for frequency
        // of one.
        // This List header will be for keys with frequency of 1
        minmax.emplace_front(1, unordered_set<string>{});
      }

      // Add to the bucket
      minmax.front().second.insert(key);

      // Map the bucket to the key.
      frequency[key] = minmax.begin();
      return;
    }

    // Key already exists. Check the next list header. If it does
    // not exist, or it has a different frequency, then create a new list.
    // Otherwise, insert into the next list.
    auto &listIter = mapIter->second;
    auto &oldBucket = listIter->second;
    const int32_t newFreq = listIter->first + 1;

    auto nextIter = std::next(listIter);
    if (nextIter == minmax.end() || nextIter->first > newFreq) {
      // Insert a new list at the next position
      nextIter = minmax.insert(nextIter, {newFreq, unordered_set<string>{}});
    }

    // Remove the old key from the oldBucket.
    oldBucket.erase(key);

    // Book-keeping
    if (oldBucket.empty()) {
      minmax.erase(listIter);
    }

    // Add the current listIter to the next Bucket
    nextIter->second.insert(key);

    // Update the current map entry to point to the correct listNode.
    mapIter->second = nextIter;
  }

  void dec(string key) {
    // Question guarantees dec will only be called when the key exists in the
    // data structure
    auto mapIter = frequency.find(key);
    auto listIter = mapIter->second;
    const int32_t oldFreq = listIter->first;
    const int32_t newFreq = oldFreq - 1;

    // Remove the key from the current bucket.
    listIter->second.erase(key);

    // Check if the key should still remain in the data structures.
    if (newFreq == 0) {
      // Remove from map
      frequency.erase(key);
    } else {
      // Else, check if the current list is the left-most. If so, add a
      // new list to the left.
      // Otherwise, check if the bucket to the left has the same frequency as
      // newFreq. If same, then add to that bucket. Otherwise, add a newBucket

      auto newBucketIter = listIter;
      if (listIter == minmax.begin() || std::prev(listIter)->first < newFreq) {
        // Insert a new list to the left of the listIter.
        newBucketIter =
            minmax.insert(listIter, {newFreq, unordered_set<string>{}});
      } else {
        // set the newBucketIter to the existing left listNode.
        newBucketIter = std::prev(listIter);
      }

      // Insert into the new/existing bucket on the left
      newBucketIter->second.insert(key);

      // Update the current map entry
      mapIter->second = newBucketIter;
    }

    // Book-keeping.
    if (listIter->second.empty()) {
      minmax.erase(listIter);
    }
  }

  string getMaxKey() {
    if (frequency.empty()) {
      return "";
    }

    return *minmax.back().second.begin();
  }

  string getMinKey() {
    if (frequency.empty()) {
      return "";
    }

    return *minmax.front().second.begin();
  }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
