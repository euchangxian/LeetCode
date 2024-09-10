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

class MedianFinder {
private:
  // at most 5 * 10^4, divide by two and round up

  //  Max Heap that stores the lower half of the stream of numbers.
  priority_queue<int, vector<int>, less<int>> lowerHalf;

  // Min Heap that stores the upper half of the stream of numbers.
  priority_queue<int, vector<int>, greater<int>> upperHalf;

public:
  // The key invariant to maintain is the difference in sizes of the two
  // priority queue.
  //
  // The difference in size should never exceed 1. i.e., if the number
  // of elements in the stream is even, then the difference should be zero.
  // If the number of elements in the stream is odd, then the difference
  // should be 1.
  //
  // This will allow us to efficiently lookup the median of the stream, since
  // peeking at the top of the heap is O(1)/constant time.
  MedianFinder() : lowerHalf(), upperHalf() {}

  // addNum must maintain the invariant.
  void addNum(int num) {
    if (lowerHalf.empty()) {
      lowerHalf.push(num);
      return;
    }

    if (lowerHalf.size() > upperHalf.size()) {
      if (num >= lowerHalf.top()) {
        upperHalf.push(num);
        return;
      }

      // Move lowerHalf top to upperHalf, since num is smaller
      upperHalf.push(lowerHalf.top());
      lowerHalf.pop();
      lowerHalf.push(num);
      return;
    }

    // both heaps are equal in length
    // move the smaller of num and the top of the upperHalf heap
    // to the lowerHalf heap. This allows us to keep the lowerHalf heap
    // consistently GTE the upperHalf heap.
    if (num <= upperHalf.top()) {
      lowerHalf.push(num);
      return;
    }

    lowerHalf.push(upperHalf.top());
    upperHalf.pop();
    upperHalf.push(num);
    return;
  }

  // If even-length stream, simply return the average of the two elements at
  // the top of each heap.
  // Otherwise, return the element at the top of the lowerHalf heap.
  double findMedian() {
    if (lowerHalf.size() > upperHalf.size()) {
      // Odd-case is simpler
      return lowerHalf.top();
    }

    if (upperHalf.size() > lowerHalf.size()) {
      return upperHalf.top();
    }

    // the case where findMedian is called when no numbers are in the stream
    // yet do not need to be handled, due to question constraints/guarantees.
    return static_cast<double>(lowerHalf.top() + upperHalf.top()) / 2.0;
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
