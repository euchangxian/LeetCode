#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
/**
 * Each video is a string of digits, where the ith digit of the string represent
 * the content of the video at minute i.
 *
 * like and dislike videos.
 * Keep track of the views, likes and dislikes on each video.
 *
 * Upload/delete.
 * videoId increments by 1 starting from 0. Once deleted, the videoId can be
 * reused => this seems like the Infinite Set Design question, LC 2336, which
 * requires retrieving the smallest number in the set of integers, and also
 * support a similar operation like Delete. Uses Ordered Set. Technically, a
 * minHeap works, since we have no need to track the "bottom" of the heap to
 * determine if a videoId should be added back into the heap.
 */
class VideoSharingPlatform {
 private:
  // Keep track of the lowest available ID to be assigned.
  std::set<int> availableIds;

  std::array<std::string, 100001> videos{};

  // Keep track of the {likes, dislikes} of each video
  std::array<std::array<int, 2>, 100001> likesDislikes{};

  // Keep track of the views of the video
  std::array<int, 100001> views{};

 public:
  VideoSharingPlatform() : availableIds({0}) {}

  int upload(std::string video) {
    int assignedId = *availableIds.begin();
    availableIds.erase(assignedId);

    if (availableIds.empty()) {
      // This ID was not reinserted. Its newly seen.
      availableIds.insert(assignedId + 1);
    }

    // Initialize video stats in respective fields
    videos[assignedId] = std::move(video);
    likesDislikes[assignedId] = {0, 0};
    views[assignedId] = 0;

    return assignedId;
  }

  void remove(int videoId) {
    if (videos[videoId].empty()) {
      return;
    }

    videos[videoId] = "";          // use an empty string to indicate no-video
    availableIds.insert(videoId);  // add back the ID into the pool
  }

  std::string watch(int videoId, int startMinute, int endMinute) {
    if (videos[videoId].empty()) {
      return "-1";
    }

    ++views[videoId];

    std::string& video = videos[videoId];
    int requestedLength =
        std::min(endMinute - startMinute + 1,
                 static_cast<int>(video.size()) - startMinute);
    return video.substr(startMinute, requestedLength);
  }

  void like(int videoId) {
    if (videos[videoId].empty()) {
      return;
    }

    ++likesDislikes[videoId][0];
  }

  void dislike(int videoId) {
    if (videos[videoId].empty()) {
      return;
    }
    ++likesDislikes[videoId][1];
  }

  vector<int> getLikesAndDislikes(int videoId) {
    if (videos[videoId].empty()) {
      return {-1};
    }
    return std::vector(likesDislikes[videoId].begin(),
                       likesDislikes[videoId].end());
  }

  int getViews(int videoId) {
    if (videos[videoId].empty()) {
      return -1;
    }

    return views[videoId];
  }
};

/**
 * Your VideoSharingPlatform object will be instantiated and called as such:
 * VideoSharingPlatform* obj = new VideoSharingPlatform();
 * int param_1 = obj->upload(video);
 * obj->remove(videoId);
 * string param_3 = obj->watch(videoId,startMinute,endMinute);
 * obj->like(videoId);
 * obj->dislike(videoId);
 * vector<int> param_6 = obj->getLikesAndDislikes(videoId);
 * int param_7 = obj->getViews(videoId);
 */
