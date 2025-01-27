#include <cstddef>
#include <cstdlib>
#include <vector>

// Stream of n videos, labelled from [1..n].
// Determine the length of the longest uploaded prefix at various points.
// i is an uploaded prefix if all videos in the range [1..i] has been
// uploaded.
// Hm. We want Range Maximum Query, but we also want the prefix frequency.
// Very precisely, we can use Segment Trees for RMQ, PURQ Fenwick Trees for
// prefix frequency/presence array.
// Lol. Don't jump to complicated solutions...
// Think of it as a TCP buffer.
class LUPrefix {
 public:
  LUPrefix(int n) : uploaded(n + 1) {}

  void upload(int video) { uploaded[video] = true; }

  int longest() {
    while (i < uploaded.size() && uploaded[i]) {
      ++i;
    }
    return i - 1;
  }

 private:
  int i{1};
  std::vector<bool> uploaded;
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
