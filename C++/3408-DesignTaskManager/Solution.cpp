#include <iterator>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

// Manage tasks with priorities.
// add: add tasks with specified taskId and priority to the given userId.
//      The task is guaranteed to not exist in the system.
// edit: update the priority of the given taskId.
//       The task is guaranteed to exist.
// rmv: remove the task with the given taskId.
//      The task is guaranteed to exist.
// execTop: execute the task with the higest priority across all users.
//          If multiple tasks have the same priority, execute the one with
//          the highest taskId.
//          Return the userId associated with the executed task.
//
// Hm. First thoughts: we don't have to granularly track the tasks associated
// with each user.
// This seems similar to a time-sliced shared host CPU.
// It feels like we can just store tuples: (priority, taskId, userId) into
// a priority queue.
// But that does not allow us to update the priority of existing tasks, nor
// remove (though, rmv can be done lazily by maintaining a "deleted" hashmap,
// which we check on execTop, updates can not be done in the same fashion
// naively, since we need to order by priority).
// Multiple hashmaps would work, along with an ordered Set/Map storing the
// tuples.
// ---
// Maintain std::set storing (priority, taskId, userId). This allows us to
// order by priority.
// Maintain std::unordered_map storing {taskId, (userId, priority)}. This allows
// us to edit the ordered Set, and to also remove tasks, since we can get
// the Key.
class TaskManager {
 public:
  TaskManager(std::vector<std::vector<int>>& tasks) {
    for (const auto& task : tasks) {
      auto userId = task[0];
      auto taskId = task[1];
      auto priority = task[2];
      add(userId, taskId, priority);
    }
  }

  void add(int userId, int taskId, int priority) {
    taskQueue.emplace(priority, taskId, userId);
    taskMetadata.emplace(std::piecewise_construct,
                         std::forward_as_tuple(taskId),
                         std::forward_as_tuple(userId, priority));
  }

  void edit(int taskId, int newPriority) {
    auto& [userId, priority] = taskMetadata[taskId];

    taskQueue.erase({priority, taskId, userId});

    priority = newPriority;
    taskQueue.insert({priority, taskId, userId});
  }

  void rmv(int taskId) {
    auto [userId, priority] = taskMetadata[taskId];
    taskQueue.erase({priority, taskId, userId});
    taskMetadata.erase(taskId);
  }

  int execTop() {
    if (taskQueue.empty()) {
      return -1;
    }
    auto [_, taskId, userId] = *taskQueue.rbegin();
    rmv(taskId);
    return userId;
  }

 private:
  using Task = std::tuple<int, int, int>;
  std::set<Task> taskQueue;

  using Metadata = std::pair<int, int>;
  std::unordered_map<int, Metadata> taskMetadata;
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */
