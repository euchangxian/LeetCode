#include <string>
#include <string_view>
#include <unordered_map>

// The complexity here is checking that a parent path exists.
// Start with '/' initially.
class FileSystem {
 public:
  // sentinel
  FileSystem() {}

  bool createPath(std::string path, int value) {
    auto parent = getParent(path);
    auto ok = paths.contains(parent);

    // not root, and parent does not exist.
    if (!parent.empty() && !paths.contains(parent)) {
      return false;
    }

    // true if not exist.
    return paths.try_emplace(std::move(path), value).second;
  }

  int get(std::string path) {
    if (auto it = paths.find(path); it != paths.end()) {
      return it->second;
    }
    return -1;
  }

 private:
  std::string getParent(std::string_view path) {
    auto it = path.rfind('/');
    if (it == 0) {
      return "";
    }

    return std::string{path.substr(0, it)};
  }

  std::unordered_map<std::string, int> paths;
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */
