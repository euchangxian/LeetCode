#include <algorithm>
#include <queue>
#include <ranges>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

class SCC {
 public:
  SCC(int vertices) : computed(false), V(vertices), numSCCs(0), time(0) {
    adj.resize(V);
    componentOf.assign(V, -1);
  }

  void addEdge(int v, int w) { adj[v].push_back(w); }

  void tarjanSCC() {
    if (computed) {
      return;  // avoid recomputing
    }

    time = 0;
    numSCCs = 0;
    componentOf.assign(V, -1);

    std::vector<int> discovery(V, -1);
    std::vector<int> lowest(V, -1);
    std::stack<int> st;

    // Process all vertices
    for (int i = 0; i < V; i++) {
      if (discovery[i] == -1) {
        tarjanSCC(i, discovery, lowest, st);
      }
    }

    computed = true;
  }

  int getNumSCCs() {
    if (!computed) {
      tarjanSCC();
    }
    return numSCCs;
  }

  const std::vector<int>& getComponentMap() {
    if (!computed) {
      tarjanSCC();
    }
    return componentOf;
  }

  // Get all vertices in a specific component
  std::vector<int> getComponent(int compId) {
    if (!computed) {
      tarjanSCC();
    }

    std::vector<int> result;
    for (int i = 0; i < V; i++) {
      if (componentOf[i] == compId) {
        result.push_back(i);
      }
    }
    return result;
  }

  // Get all SCCs as lists of vertices
  std::vector<std::vector<int>> getAllSCCs() {
    if (!computed) {
      tarjanSCC();
    }

    std::vector<std::vector<int>> result(numSCCs);
    for (int i = 0; i < V; i++) {
      result[componentOf[i]].push_back(i);
    }
    return result;
  }

  const std::vector<std::vector<int>> getAdjList() { return adj; }

 private:
  bool computed;
  int V;     // Number of vertices
  int time;  // For Tarjan's algorithm
  int numSCCs;

  std::vector<std::vector<int>> adj;  // Adjacency list
  std::vector<int> componentOf;       // Maps each vertex to its component ID

  int tarjanSCC(int u,
                std::vector<int>& discovery,
                std::vector<int>& lowest,
                std::stack<int>& st) {
    discovery[u] = lowest[u] = ++time;
    st.push(u);

    for (int v : adj[u]) {
      // Only consider vertices not yet assigned to a component
      if (componentOf[v] == -1) {
        // If not discovered, recursively visit
        if (discovery[v] == -1) {
          tarjanSCC(v, discovery, lowest, st);
          lowest[u] = std::min(lowest[u], lowest[v]);
        }
        // Back edge to a vertex in current SCC
        else {
          lowest[u] = std::min(lowest[u], discovery[v]);
        }
      }
    }

    // If u is root of an SCC
    if (lowest[u] == discovery[u]) {
      // Process all vertices in the current SCC
      int v;
      do {
        v = st.top();
        st.pop();
        componentOf[v] = numSCCs;
      } while (v != u);

      numSCCs++;
    }

    return lowest[u];
  }
};

class Solution {
 public:
  int minRunesToAdd(int n,
                    std::vector<int>& crystals,
                    std::vector<int>& flowFrom,
                    std::vector<int>& flowTo) {
    // TLDR: Find the MINIMUM number of edges to add (apart from those already
    // represented in {from[i], to[i]}) such that every node from [0..n-1] is
    // either:
    // - a crystal, i.e., has magic
    // - connected to another magic component.
    //
    // Seems like a simple UFDS?
    // Not really.
    // First, is the minimum edge requirement.
    // Second, is the directed edges (UFDS is undirected).
    //
    // Feels like Strongly Connected Components.
    //
    // DFS? Starting from Crystal nodes.
    // The issue is the directed-ness of the edges for non-connected components.
    // Traversing them in a different order may cause wrong number of edges to
    // be added.
    // i.e., 1->0, but we look at 0 first and determine that an edge needs to
    // be added to 0, then 1, where we could have just added to 1.
    //
    // Hm. Seems topological sort-like? We want to start from the parent.
    // Seems about right.
    // For cycles, an edge can be added to any arbitrary node in the cycle.
    //
    // Not easy to implement correctly/efficiently.
    // Notice that we want to treat every cycle as a single node.
    // This is essentially condensing SCCs to a single node, simplifying the
    // problem greatly (except SCCs are not easy to implement...
    // Tarjans/Kosaraju).
    SCC scc(n);
    for (const auto [u, v] : std::ranges::views::zip(flowFrom, flowTo)) {
      scc.addEdge(u, v);
    }

    // Assigns each node to a component.
    scc.tarjanSCC();
    int numSCCs = scc.getNumSCCs();
    const std::vector<int>& SCC = scc.getComponentMap();

    // At this point, we can additionally do a Union Find. Union every node
    // in the same SCC together. Then, union every crystal node to a CRYSTAL
    // sentinel.
    // Then, the remaining number of components are the number of edges that
    // we need to add.
    // Ahhh. Not really. 3 -> 4 is 2 separate SCCs, even though 3 may be
    // a crystal node.
    // Need another approach to counting.
    // DFS starting from crystal nodes? Mark each SCC as reachable/unreachable.
    // Then, count number of unreachable SCCs.
    // Ah... Does not account for minimum edges to add. i.e.,
    // 1->2->3, where 0 is a crystal. Then, simply adding an edge from 0 to 1
    // will be sufficient.
    // Hmmmm. Need to actually create the condensed graph. Then, DFS starting
    // from the components with a crystal.
    // Given that Tarjan's side-effect is a reverse topological sort of each
    // SCC, are we able to utilize it? Nope. In our case, the source SCCs should
    // be SCCs with crystals, which is not known yet.
    // Thus, need to topo-sort and explore starting from the source SCCs.
    std::vector<std::unordered_set<int>> sccAdj(numSCCs);
    std::vector<int> indegree(numSCCs);
    for (const auto [u, v] : std::ranges::views::zip(flowFrom, flowTo)) {
      if (SCC[u] != SCC[v]) {
        bool newEdge = sccAdj[SCC[u]].insert(SCC[v]).second;

        if (newEdge) {
          ++indegree[SCC[v]];  // may be incremented multiple time.
        }
      }
    }

    // guaranteed to not have Cycles in the condensed graph.
    // First figure out which components are unreachable. Then, do a partial
    // topological sort; figure out the unreachable SCCs with a zero-indegree.
    std::queue<int> frontier;
    std::vector<bool> reachable(numSCCs, false);
    for (int u : crystals) {
      if (!reachable[SCC[u]]) {
        reachable[SCC[u]] = true;
        frontier.push(SCC[u]);
      }
    }

    // Modified Kahn's. Cant really call it Topological Sort already.
    // Since we simply push all neighbours and decrement indegree.
    while (!frontier.empty()) {
      auto curr = frontier.front();
      frontier.pop();
      for (int next : sccAdj[curr]) {
        if (!reachable[next]) {
          reachable[next] = true;
          --indegree[next];
          frontier.push(next);
        }
      }
    }

    int edges = 0;
    for (int i = 0; i < numSCCs; ++i) {
      if (!reachable[i] && indegree[i] == 0) {
        ++edges;
      }
    }
    return edges;
  }
};
