#include <algorithm>
#include <queue>
#include <vector>

constexpr int MAX_N = 1e4;
constexpr int MAX_DAY = 1e4;  // duration,lastDay <= 1e4

class Solution {
 public:
  int scheduleCourse(std::vector<std::vector<int>>& courses) {
    // Greedy?
    // First, sort by lastDay, since that is the largest restriction.
    // Take the current course.
    // Ah. we maintain the current time, and a PQ of taken courses, keyed by
    // duration.
    // When deciding, we can take a course trivially if time+duration<=lastDay.
    // Otherwise, remove the longest course and its duration from the PQ IF
    // this duration is shorter.
    std::ranges::sort(courses, {}, [](const auto& v) { return v[1]; });

    int day = 0;
    std::priority_queue<int> pq;  // {duration}
    for (const auto& course : courses) {
      int duration = course[0], lastDay = course[1];
      pq.emplace(duration);
      day += duration;
      if (day > lastDay) {
        day -= pq.top();
        pq.pop();
      }
      // if (day + duration <= lastDay) {
      //   pq.emplace(duration);
      //   day += duration;
      // } else if (!pq.empty() && pq.top() > duration) {
      //   day -= pq.top();
      //   pq.pop();
      //
      //   pq.emplace(duration);
      //   day += duration;
      // }
    }

    return pq.size();
  }

  int scheduleCourseDPTLE(std::vector<std::vector<int>>& courses) {
    // n different courses labelled 1 to n
    // courses[i] = [duration, lastDay] indicating the ith course must be taken
    // for duration consecutive day, and finish before or on the last day.
    // Start on day 1, only 1 course can be taken at any one time.
    // Return the maximum number of courses that can be taken.
    //
    // We want to finish courses that end earlier first, and courses that
    // have a shorter duration.
    // Is there a greedy choice?
    //
    // Consider:
    // courses = [[200,200],[1000,1200],[100,1250],[100,1300],[2000,2000]]
    // If we sort and naively take the earliest ending course, we will fail.
    // Hm. We can maintain the current day?
    //
    // NVM. Lets just try DP.
    // At each course, we can choose to take/skip
    // We can only take if duration+currDay <= lastDay.
    // Thus, we need the state (i, j) representing the course in consideration
    // and the currentDay respectively.
    //
    // WARNING: TLE. Sigh. O(NM) should theoretically pass though?
    std::ranges::sort(courses, {}, [](const auto& v) { return v[1]; });
    int maxLastDay = (*std::ranges::max_element(
        courses, {}, [](const auto& v) { return v[1]; }))[1];
    std::vector<std::vector<int>> memo(courses.size(),
                                       std::vector<int>(maxLastDay, -1));
    return dfs(courses, memo, 0, 0);
  }

 private:
  int dfs(std::vector<std::vector<int>>& courses,
          std::vector<std::vector<int>>& memo,
          int i,
          int j) {
    if (i >= courses.size()) {
      return 0;
    }

    if (j >= memo[0].size()) {
      return 0;
    }

    int& ans = memo[i][j];
    if (ans != -1) {
      return ans;
    }

    ans = dfs(courses, memo, i + 1, j);

    int duration = courses[i][0];
    int lastDay = courses[i][1];
    if (j + duration <= lastDay) {
      ans = std::max(ans, dfs(courses, memo, i + 1, j + duration) + 1);
    }
    return ans;
  }
};
