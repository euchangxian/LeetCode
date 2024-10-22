#include <cstddef>
#include <string>
#include <unordered_map>

using namespace std;
class Logger {
 private:
  // {string, nextTimestamp}
  unordered_map<string, int> nextTime;

 public:
  Logger() {}

  bool shouldPrintMessage(int timestamp, string message) {
    auto iter = nextTime.find(message);

    // Check if not rate-limited: first occurence, or t + 10 has already passed.
    if (iter == nextTime.end() || timestamp >= iter->second) {
      nextTime[message] = timestamp + 10;
      return true;
    }

    return false;
  }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
