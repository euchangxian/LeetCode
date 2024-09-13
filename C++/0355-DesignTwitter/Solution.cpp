#include <algorithm>
#include <array>
#include <climits>
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
// 1 <= userID, followerID, followeeID <= 500. i.e., number of users <= 500
constexpr uint16_t USERS = 500;

// 1 <= tweetID <= 10^4. i.e., number of tweets <= 10e4
constexpr uint16_t TWEETS = 10000;

class Twitter {
private:
  // counts the number of times postTweet was invoked. This is so we can
  // order the tweets created from most recent to least recent
  // Also acts as a pointer to the tweets array
  uint16_t time;

  // userID and the list of Users that they are following
  array<bitset<USERS>, USERS> following;

  // {tweetID, userID}
  array<pair<uint16_t, uint16_t>, TWEETS> tweets;

public:
  Twitter() : time(0), following({}), tweets({}) {
    for (int i = 0; i < USERS; ++i) {
      following[i].set(i);
    }
  }

  // Compose a new tweet with tweetID by the user userID. TweetID will be unique
  void postTweet(int userId, int tweetId) {
    tweets[time] = {tweetId, userId};
    ++time;
  }

  // Retrieves the 10 most recent tweetIDs in the user's feed. Each item in
  // the news feed must be posted by users who the user followed, or the user
  // themself.
  // Ordered from most recent to least recent
  // Will need to check if the user is currently following the tweet-poster.
  vector<int> getNewsFeed(int userId) {
    vector<int> topFeed;
    topFeed.reserve(10);

    // time must be casted to signed int to prevent wrap-around
    for (int16_t i = static_cast<int16_t>(time) - 1;
         i >= 0 && topFeed.size() < 10; --i) {

      auto const &[tweetId, posterId] = tweets[i];
      if (following[userId].test(posterId)) {
        topFeed.push_back(tweetId);
      }
    }

    return topFeed;
  }

  // The user with ID followerID started following the user with ID followeeID.
  void follow(int followerId, int followeeId) {
    following[followerId].set(followeeId);
  }

  // The user with ID followerID unfollowed the user with ID followeeID.
  void unfollow(int followerId, int followeeId) {
    if (followeeId != followerId) {
      // Prevent user from unfollowing themself
      following[followerId].reset(followeeId);
    }
  }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
