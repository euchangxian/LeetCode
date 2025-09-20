#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
 public:
  // Return true if this NestedInteger holds a single integer, rather than
  // a nested list.
  bool isInteger() const;

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer
  // The result is undefined if this NestedInteger holds a nested list
  int getInteger() const;

  // Return the nested list that this NestedInteger holds, if it holds a
  // nested list
  // The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger>& getList() const;
};

/**
 * First glance seemed simple. But realize that Each NestedInteger can have an
 * arbitrary amount of nesting.
 * What about making NestedIterator a recursive Class?
 * i.e., each NestedInteger instance holds a pointer to another NestedInteger
 * instance.
 */
class NestedIterator {
 private:
  vector<NestedInteger>::iterator flatIter;
  const vector<NestedInteger>::iterator flatEnd;

 public:
  // NestedInteger is essentially an optional?
  NestedIterator(vector<NestedInteger>& nestedList)
      : flatIter(nestedList.begin()), flatEnd(nestedList.end()) {}

  int next() {}

  bool hasNext() {}
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
