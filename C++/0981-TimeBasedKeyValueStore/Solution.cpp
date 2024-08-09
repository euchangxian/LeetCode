#include <algorithm>
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
class TimeMap {
private:
  unordered_map<string, vector<pair<int, string>>> store;

public:
  TimeMap() {}

  void set(string key, string value, int timestamp) {
    store[key].push_back({timestamp, value});
    return;
  }

  string get(string key, int timestamp) {
    if (!store.count(key)) {
      return "";
    }

    vector<pair<int, string>> const &values = store[key];

    int left = 0;
    int right = values.size() - 1;
    // look for k, where k is the largest value <= timestamp
    // [T, T, T, F, F], where we want the right-most T
    while (left < right) {
      // IMPORTANT: Use ceiling division instead.
      // This is because we want to bias the value of mid towards the right,
      // and also avoid infinite loops in the update of left = mid.
      int mid = left + (right - left + 1) / 2;

      auto const &[ts, val] = values[mid];
      if (ts <= timestamp) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return values[left].first <= timestamp ? values[left].second : "";
  }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
