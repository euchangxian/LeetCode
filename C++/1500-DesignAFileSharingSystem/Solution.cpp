#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// FileSharing sytem to share a very large file consisting of m small chunks,
// id-ed from 1 to m.
// When a user joins the system, the system assigns a UID, and can be recycled.
// Users can request a certain chunk of the file, which should return a list of
// ids of all the users that own this chunk.
// If the list is non-empty, the chunk is received successfully.
// - join(ownedChunks): Assign the smallest positive available integer to the
//   joining user, who owns the ownedChunks. Return the UID.
// - leave(userId): file chunks cannot be taken from the leaving user.
// - request(userId, chunkId): userId requests chunkId. The returned list should
//   be sorted in ascending order.
//
// Hm.
// A std::set to assign and track UIDs.
// A std::unordered_map<ChunkID, SortedContainer> to track the list of users
// that own a chunk.
// For SortedContainer, there are two possible choices:
// - a std::set, allowing for logN addition and deletion, but O(N) time to copy
//   and return when a user requests a chunk.
// - std::vector, O(N) addition and deletion, O(N) time to copy too.
// Therefore, the choice seems clear for now, in terms of asymptotic analysis.
// We still need to maintain {uid, ownedChunks} so we can cleanup when a user
// leaves.
class FileSharing {
 public:
  FileSharing(int m) : nextUID(1), availableUIDs({nextUID}) {}

  int join(std::vector<int> ownedChunks) {
    auto uid = assignUID();
    for (auto chunkID : ownedChunks) {
      chunkOwners[chunkID].emplace(uid);
    }
    chunksOwned.emplace(uid,
                        std::set<int>{ownedChunks.begin(), ownedChunks.end()});
    return uid;
  }

  void leave(int userID) {
    auto handle = chunksOwned.extract(userID);
    if (!handle) {
      return;
    }
    const auto& ownedChunks = handle.mapped();
    for (auto chunkID : ownedChunks) {
      chunkOwners[chunkID].erase(userID);
    }
    releaseUID(userID);
  }

  std::vector<int> request(int userID, int chunkID) {
    auto it = chunkOwners.find(chunkID);
    if (it == chunkOwners.end() || it->second.empty()) {
      return {};
    }

    auto& owners = it->second;
    auto result = std::vector<int>{owners.begin(), owners.end()};

    owners.emplace(userID);
    chunksOwned[userID].emplace(chunkID);
    return result;
  }

 private:
  int assignUID() {
    auto uid = availableUIDs.extract(availableUIDs.begin()).value();
    if (availableUIDs.empty()) {
      availableUIDs.emplace(++nextUID);
    }
    return uid;
  }

  int nextUID;
  void releaseUID(int uid) { availableUIDs.emplace(uid); }

  std::set<int> availableUIDs;
  std::unordered_map<int, std::set<int>> chunksOwned;

  std::unordered_map<int, std::set<int>> chunkOwners;
};

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing* obj = new FileSharing(m);
 * int param_1 = obj->join(ownedChunks);
 * obj->leave(userID);
 * vector<int> param_3 = obj->request(userID,chunkID);
 */
