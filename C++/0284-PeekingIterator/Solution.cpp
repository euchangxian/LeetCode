#include <cstddef>
#include <vector>

using namespace std;
/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 */
class Iterator {
  struct Data;
  Data* data;

 public:
  Iterator(const vector<int>& nums);
  Iterator(const Iterator& iter);

  // Returns the next element in the iteration.
  int next();

  // Returns true if the iteration has more elements.
  bool hasNext() const;
};

/**
 * Naively, 'cache' the result of Iterator::next(), such that multiple
 * peeks would not invoke Iterator::next and advance the iterator.
 * This means that hasNext would also need to be cached.
 * In other words, maintain a boolean flag isCached which is modified by
 * PeekingIterator::next.
 * A call to PeekingIterator::peek would check the flag. If not yet cached,
 * then save the values of Iterator::hasNext and Iterator::next (in order!).
 *
 * Subsequent PeekingIterator::peek and PeekingIterator::hasNext invocations
 * will then return the cached values.
 * If PeekingIterator::next is invoked, then invalidate the cached values.
 *
 */
class PeekingIterator : public Iterator {
 private:
  int cachedVal;
  bool cachedHasNext;

  bool invalid;

 public:
  PeekingIterator(const vector<int>& nums) : Iterator(nums), invalid(true) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() {
    if (invalid) {
      cachedHasNext = Iterator::hasNext();
      cachedVal = Iterator::next();
      invalid = false;
    }
    return cachedVal;
  }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() {
    if (invalid) {
      peek();
    }
    invalid = true;
    return cachedVal;
  }

  bool hasNext() const {
    if (!invalid) {
      return cachedVal;
    }
    return Iterator::hasNext();
  }
};
