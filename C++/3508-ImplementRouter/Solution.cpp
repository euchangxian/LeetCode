#include <algorithm>
#include <deque>
#include <functional>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Manage Data packets. Each packet consists of:
// - source: UID for the machine that generated the packet
// - destination: UID for the destination machine
// - timestamp: Time at which the packet arrived at the router.
//
// The Router has a memoryLimit - maximum number of routers that can be stored
// at any time. Oldest packets are removed, i.e., FIFO
// - addPacket - add a packet to the router. A packet is duplicate if its
//   3-tuple (source, destination, timestamp) is the same as another.
//   Return true if the packet is newly seen. False otherwise.
// - forwardPacket: forwards the next packet in FIFO order.
//   - Remove the packet from storage
//   - Return the packet as an array [source, destination, timestamp]
//   - Return empty if there are no packets.
// - getCount - return the number of packets currently in the router that have
//   the specified destination, and have timestamps in the inclusive range
//   [start, end]
// Queries for addPacket are made in increasing order of timestamp. i.e., sorted
//
// Hmmmm.
// - We want a FIFO order.
// - We want to detect duplicate tuples.
// - We want to be able to do a range query by destination.
// Seems to be pointing to a sorted Map. Given that addPacket will not add
// duplicate packets (i.e., each packet must be forwarded at most once), we
// gain a little more flexibility here?
// Simplest way to check for duplicates is to store tuples in the map.
//
// The more maps we have, the more difficult it becomes to maintain consistency.
// Given that addPacket is done in increasing timestamp, we can possibly order
// by timestamp. But suppose we get two packets with the same timestamp, but
// different source/destination. It becomes not-possible to determine which
// arrived first.
// Will a std::queue of tuples work?
// Then a std::unordered_map<destination, std::multiset<timestamp>> to query.
// Upon forwarding, we can remove from the queue, and the multiset.
// Hm. C++ specifics, but does multiset::lower_bound return the FIRST, and
// multiset::upper_bound return the LAST? Regardless, std::distance still
// requires O(N) time.
// Can we do better? likely std::map<timestamp, frequency> and manually iterate.
// Ah. We can do even better. Timestamps are in increasing order. Hence,
// for two packets to the same destination, we do not need to care about
// their source, when dropped or forwarded, we can pop the earlier timestamp.
struct Packet {
  int source;
  int destination;
  int timestamp;

  auto operator<=>(const Packet&) const = default;
};
using Destination = decltype(Packet::destination);
using Timestamp = decltype(Packet::timestamp);

template <>
struct std::hash<Packet> {
  std::size_t operator()(const Packet& packet) const {
    auto [one, two, three] = packet;
    return (std::hash<int>{}(one)) ^ (std::hash<int>{}(two) << 1) ^
           (std::hash<int>{}(three) << 2);
  }
};

class Router {
 public:
  Router(int memoryLimit) : memoryLimit(memoryLimit) {}

  bool addPacket(int source, int destination, int timestamp) {
    auto packet = Packet{source, destination, timestamp};
    if (inRouter.contains(packet)) {
      return false;
    }

    packets.emplace(packet);
    inRouter.emplace(packet);
    rsq[destination].emplace_back(timestamp);
    if (packets.size() > memoryLimit) {
      popFront();
    }
    return true;
  }

  std::vector<int> forwardPacket() {
    if (packets.empty()) {
      return {};
    }

    auto [source, destination, timestamp] = popFront();
    return {source, destination, timestamp};
  }

  int getCount(int destination, int startTime, int endTime) {
    auto it = rsq.find(destination);
    if (it == rsq.end()) {
      return 0;
    }

    const auto& timestamps = it->second;

    const auto start = std::ranges::lower_bound(timestamps, startTime);
    const auto end = std::ranges::upper_bound(timestamps, endTime);
    return std::ranges::distance(start, end);
  }

 private:
  Packet popFront() {
    auto front = packets.front();
    packets.pop();

    inRouter.erase(front);

    auto& timestamps = rsq[front.destination];
    timestamps.pop_front();
    return front;
  }

  int memoryLimit;

  // we can use a fixed-size circular buffer since we have memoryLimit.
  std::queue<Packet> packets;
  std::unordered_set<Packet> inRouter;
  std::unordered_map<Destination, std::deque<Timestamp>> rsq;
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */
