#include <cstddef>
#include <cstdlib>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * Want to monitor metrics in granularities of minutes, hours or days.
 *
 * Most straightforward way is to define buckets for each tweet, and for each
 * partition. Results in x3 space usage, but allows for constant time retrieval
 * of metrics.
 *
 * I.e., store a map of buckets. Define a getBucket(int) function to determine
 * the bucket to place the new tweet in.
 * This won't really work though. the period queried is varying.
 * Feels like some sort of range queries. Can we optimize it?
 * What about storing the prefix sums? Still have to scan through to partition.
 *
 * Let's stick with the naive way.
 */
class TweetCounts {
 private:
  static constexpr int minuteSeconds = 60;
  static constexpr int hourSeconds = 3600;
  static constexpr int daySeconds = 86400;

  std::unordered_map<std::string, std::multiset<int>> tweets;

 public:
  TweetCounts() {}

  void recordTweet(std::string tweetName, int time) {
    tweets[tweetName].insert(time);
  }

  std::vector<int> getTweetCountsPerFrequency(std::string_view freq,
                                              std::string tweetName,
                                              int startTime,
                                              int endTime) {
    int interval = freq[0] == 'm'   ? minuteSeconds
                   : freq[0] == 'h' ? hourSeconds
                                    : daySeconds;

    auto iter = tweets.find(tweetName);
    if (iter == tweets.end()) {
      return {};
    }

    std::vector<int> buckets((endTime - startTime) / interval + 1, 0);

    const std::multiset<int>& records = iter->second;
    for (auto it = records.lower_bound(startTime);
         it != records.end() && *it <= endTime; ++it) {
      int bucketIdx = (*it - startTime) / interval;
      ++buckets[bucketIdx];
    }

    return buckets;
  }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 =
 * obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */
