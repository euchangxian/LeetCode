#include <utility>
#include <vector>

class SnapshotArray {
 public:
  SnapshotArray(int length) : snapID(0), snapshots(length) {
    for (int i = 0; i < length; ++i) {
      snapshots[i].emplace_back(snapID, 0);
    }
  }

  void set(int index, int val) {
    auto& changes = snapshots[index];
    auto& [lastID, old] = changes.back();
    if (lastID < snapID) {
      changes.emplace_back(snapID, val);
    } else {
      old = val;
    }
  }

  int snap() { return snapID++; }

  int get(int index, int snap_id) {
    auto& changes = snapshots[index];

    auto it = std::ranges::upper_bound(changes, snap_id, {},
                                       &std::pair<int, int>::first);

    --it;
    return it->second;
  }

 private:
  int snapID;

  // Not a 2D vector, where an entire copy is done per snap call.
  // Instead, only record the changes for each element that is updated
  // between invocations.
  std::vector<std::vector<std::pair<int, int>>> snapshots;
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
