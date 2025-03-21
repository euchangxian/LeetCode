#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  std::vector<std::string> findAllRecipes(
      std::vector<std::string>& recipes,
      std::vector<std::vector<std::string>>& ingredients,
      std::vector<std::string>& supplies) {
    // recipes[i] require all the ingredients in ingredients[i].
    // A recipe can also be an ingredient for other recipes.
    // Supplies contain ingredients, infinite quantity.
    //
    // Return all recipes that can be created.
    //
    // Topo-sort Recipes first?
    // We want to check those that do not contain other recipes as ingredients
    // first.
    // This requires collecting the recipe names and ingredient names into
    // a fast query data structure.
    // Then collect all supplies into a fast query structure.
    // Then iterate over recipes.
    const int n = recipes.size();
    std::unordered_map<std::string_view, int> recipeMap;
    recipeMap.reserve(n);
    for (int i = 0; i < n; ++i) {
      recipeMap.emplace(recipes[i], i);
    }

    std::vector<std::vector<int>> adj(n);
    std::vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
      bool hasAll = true;
      for (std::string_view ingredient : ingredients[i]) {
        if (recipeMap.contains(ingredient)) {
          ++indegree[i];
          adj[recipeMap[ingredient]].push_back(i);
        }
      }
    }

    std::unordered_set<std::string_view> available;
    available.reserve(supplies.size() + recipes.size());
    for (std::string_view s : supplies) {
      available.insert(s);
    }

    std::queue<int> frontier;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        frontier.push(i);
      }
    }

    std::vector<std::string> answer;
    answer.reserve(n);
    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop();

      bool canMake = true;
      for (std::string_view ingredient : ingredients[curr]) {
        if (!available.contains(ingredient)) {
          canMake = false;
          break;
        }
      }

      if (canMake) {
        available.insert(recipes[curr]);
        answer.emplace_back(recipes[curr]);
      }

      for (int next : adj[curr]) {
        if (--indegree[next] == 0) {
          frontier.push(next);
        }
      }
    }
    return answer;
  }
};
