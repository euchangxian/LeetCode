#include <cstddef>
#include <set>

/**
 * Input constraints make this problem trivial. 1 <= num <= 1000.
 * Simply generate an array of size 1000. Then utilize std::make_heap,
 * std::pop_heap, std::push_heap.
 *
 * Clearly that is not learning anything worthwhile.
 * Infinite set indicates that we cannot simply store all the numbers in
 * memory.
 *
 * Naively, start with just the smallest number (in a minHeap).
 * popSmallest will just pop the min, and add the next smallest number.
 *
 * Now, we encounter a problem with addBack. addBack can be called with any
 * arbitrary number, and we want to avoid adding duplicates, or "polluting" the
 * heap.
 * For example, our heap is {4} (from 3 consecutive popSmallest)
 *
 * addBack(6): intuitively, we know that we shouldn't add 6, since we have not
 * popped it. But it is non-trivial (at this point) to determine that 6 should
 * not be added.
 *
 * addBack(2): We know that 2 has been popped, since the top of the heap is 4.
 * Thus, our heap is now {2, 4}
 *
 * addBack(3): Similarly, we know that 3 should be added, since we have reached
 * 4. But again, it is non-trivial to determine that. Following the logic in
 * addBack(2), it seems that 3 is greater than the top of the heap, and we
 * should not add 3.
 *
 * It seems that we are interested in the "bottom" of the heap. Can we track it
 * then? The bottom will be updated whenever we popSmallest and the heap is
 * empty.
 *
 * Lets try again with heap = {4} => bottom = 4.
 * addBack(6): 6 > bottom=4 => skip
 * addBack(2): 2 < bottom=4 => push_heap
 * addBack(3): 3 < bottom=4 => push_heap
 *
 * Now, popSmallest will also only add the next element, smallest + 1 if the
 * heap is empty. Seems fine.
 *
 * Oh. it does not account for multiple addBack of the same number..
 * Seems easily fixed by using C++ set, which can act as an ADT heap.
 *
 */
class SmallestInfiniteSet {
 public:
  SmallestInfiniteSet() { minHeap.insert(1); }

  int popSmallest() {
    int smallest = *minHeap.begin();
    minHeap.erase(smallest);

    if (minHeap.empty()) {
      minHeap.insert(smallest + 1);
    }
    return smallest;
  }

  void addBack(int num) {
    if (num >= *std::prev(minHeap.end())) {
      return;
    }

    minHeap.insert(num);
  }

 private:
  std::set<int> minHeap;
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
