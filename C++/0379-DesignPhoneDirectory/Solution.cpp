#include <set>

constexpr int MAX_N = 1e4;

// Numbers can be assigned and free-ed.
// Want to efficiently check if a number is available/in-use.
// Similar to malloc.
// We can use a bitmap, augmented with a free-list to quickly assign.
// However, we want to avoid initializing the free-list with all maxNumbers.
// std::set would work.
// Essentially like the infinite set problem.
class PhoneDirectory {
 public:
  PhoneDirectory(int maxNumbers) : n(maxNumbers), next(0) {
    free.insert(next++);
  }

  int get() {
    if (free.empty()) {
      return -1;
    }

    int avail = *free.begin();
    free.erase(free.begin());

    if (free.empty() && next < n) {
      free.insert(next++);
    }
    return avail;
  }

  bool check(int number) { return free.contains(number) || next <= number; }

  void release(int number) {
    if (number < next) {
      free.insert(number);
    }
  }

 private:
  int n;
  int next;
  std::set<int> free;
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory* obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj->get();
 * bool param_2 = obj->check(number);
 * obj->release(number);
 */
