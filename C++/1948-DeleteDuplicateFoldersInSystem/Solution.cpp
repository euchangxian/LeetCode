#include <algorithm>
#include <array>
#include <format>
#include <memory>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

struct Node {
  std::string_view name{""};
  std::unordered_map<std::string_view, std::unique_ptr<Node>> children;
  std::string signature{""};
};

class Trie {
 public:
  Trie() : root(std::make_unique<Node>()) {}

  void insert(const std::vector<std::string>& path) {
    auto* it = root.get();
    for (std::string_view folder : path) {
      auto& childPtr = it->children[folder];
      if (!childPtr) {
        childPtr = std::make_unique<Node>();
        childPtr->name = folder;
      }
      it = childPtr.get();
    }
  }

  auto processSignatures() {
    std::unordered_map<std::string_view, int> signatureCount;
    auto postorder = [&](this auto&& postorder, Node* curr) {
      if (curr->children.empty()) {
        return;
      }

      std::vector<std::string> childSignatures;
      childSignatures.reserve(curr->children.size());
      for (const auto& [name, child] : curr->children) {
        postorder(child.get());
        childSignatures.emplace_back(
            std::format("{}({})", name, child->signature));
      }
      std::ranges::sort(childSignatures);

      for (const std::string& sig : childSignatures) {
        curr->signature += sig;
      }
      ++signatureCount[curr->signature];
    };

    postorder(root.get());
    return signatureCount;
  }

  auto deDuplicates() {
    auto signatureCount = processSignatures();
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> currPath;

    auto dfs = [&](this auto&& dfs, Node* curr) {
      if (!curr->children.empty() && signatureCount[curr->signature] >= 2) {
        return;
      }

      currPath.emplace_back(curr->name);
      result.emplace_back(currPath);
      for (const auto& [name, child] : curr->children) {
        dfs(child.get());
      }
      currPath.pop_back();
    };

    for (const auto& [name, child] : root->children) {
      dfs(child.get());
    }
    return result;
  }

 private:
  std::unique_ptr<Node> root;
};

class Solution {
 public:
  std::vector<std::vector<std::string>> deleteDuplicateFolder(
      std::vector<std::vector<std::string>>& paths) {
    // Given paths[i] representing an absolute path to the ith folder in the
    // system.
    // Two folders (not necessarily on the same level) are identical if they
    // contain the same non-empty set of identical subfolders, that have the
    // same underlying subfolder structure.
    //
    // Representing as a tree, a node A is equal to a node B if the respective
    // subtrees rooted at A is equal to that of B.
    // How to avoid the repeated traversal though.
    Trie trie{};
    for (const auto& path : paths) {
      trie.insert(path);
    }

    return trie.deDuplicates();
  }
};
