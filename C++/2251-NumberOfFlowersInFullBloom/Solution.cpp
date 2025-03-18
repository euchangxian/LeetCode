#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class PURQ {
 public:
  PURQ(int n) : N(n), tree(N + 1, 0) {}

  int query(int l, int r) const { return prefix(r) - prefix(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += i & -i) {
      tree[i] += diff;
    }
  }

  int prefix(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }

 private:
  int N;
  std::vector<int> tree;
};

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), purq(n) {}

  int query(int i) const { return purq.prefix(i); }

  void update(int l, int r, int diff) {
    purq.update(l, diff);
    purq.update(r + 1, -diff);
  }

 private:
  int N;
  PURQ purq;
};

class Solution {
 public:
  std::vector<int> fullBloomFlowers(std::vector<std::vector<int>>& flowers,
                                    std::vector<int>& people) {
    // Given flowers[i] = [start, end] indicating the flower in full bloom from
    // start to end inclusive.
    // Also given people[i] indicating the time that the ith person sees the
    // flowers.
    // Return answers[i] indicating the number of flowers in full bloom when
    // the ith person arrives.
    // Trivial with RUPQ Fenwick Trees, i.e., number of ranges that overlap.
    // Though, start,end <= 10^9 requires discretization.
    const int n = flowers.size();
    std::vector<int> points;
    points.reserve(3 * n);
    for (const auto& flower : flowers) {
      points.push_back(flower[0]);
      points.push_back(flower[1]);
    }
    for (int time : people) {
      points.push_back(time);
    }
    std::sort(points.begin(), points.end());

    int k = 1;
    std::unordered_map<int, int> rank;
    rank.reserve(points.size());
    rank[points[0]] = k;
    for (int i = 1; i < points.size(); ++i) {
      if (points[i] != points[i - 1]) {
        rank[points[i]] = ++k;
      }
    }

    FenwickTree ft(rank.size());
    for (const auto& range : flowers) {
      ft.update(rank[range[0]], rank[range[1]], 1);
    }

    std::vector<int> answer;
    answer.reserve(people.size());
    for (int time : people) {
      answer.push_back(ft.query(rank[time]));
    }
    return answer;
  }
};
