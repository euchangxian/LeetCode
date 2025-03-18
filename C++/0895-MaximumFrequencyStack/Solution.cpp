#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

/**
 * Immediately, seems like an Ordered Set, ordered by frequency.
 * But how to deal with the LIFO behaviour?
 *
 * Probably another Ordered Set, ordered by insertion order. Or rather, use
 * a tuple {frequency, insertionOrder, value}. But this does not preserve the
 * insertion order of multiple same-values.
 *
 * What about something like LFU? Keep track of the highest frequency.
 *
 * NOTE: Tapped out...weakkkkkk
 * Visualize as Groups of Frequencies.
 * When pushing an element, update its frequency with a Map.
 * Using another Map<Frequency, Stack>, push the element onto the respective
 * frequency's Stack.
 *
 * Optimization: Instead of using an Ordered Map/Set to retrieve the maximum
 * frequency, an unordered Map, along with a variable to keep track of the
 * current maximum frequency can be used.
 * This works, because suppose our current maxFrequency is 3. Then, after
 * popping this element, either there are other elements with frequency=3, or
 * we can simply decrement the maxFrequency to 2. The element MUST have occurred
 * at 2 times, and is in the frequency=2 group too.
 */
class FreqStack {
 public:
  FreqStack() {}

  void push(int val) {
    int freq = ++frequency[val];
    groups[freq].push_back(val);

    maxFreq = std::max(maxFreq, freq);
  }

  int pop() {
    std::vector<int>& maxFreqStack = groups[maxFreq];

    int val = maxFreqStack.back();
    maxFreqStack.pop_back();

    if (--frequency[val] == 0) {
      frequency.erase(val);
    }

    if (maxFreqStack.empty()) {
      groups.erase(maxFreq--);
    }
    return val;
  }

 private:
  int maxFreq{0};

  // {val, freq}
  std::unordered_map<int, int> frequency;

  // {freq, stack}
  std::unordered_map<int, std::vector<int>> groups;
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
