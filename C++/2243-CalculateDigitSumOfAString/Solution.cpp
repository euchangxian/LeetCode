#include <cstddef>
#include <cstdlib>
#include <numeric>
#include <string>
#include <string_view>
#include <utility>

class Solution {
 public:
  std::string digitSum(std::string s, int k) {
    while (s.size() > k) {
      std::string grouped;
      grouped.reserve(s.size());

      std::string_view sv{s};
      for (std::size_t i = 0; i < s.size(); i += k) {
        int groupSum =
            std::reduce(sv.begin() + i, sv.begin() + std::min(i + k, s.size()),
                        0, [](int acc, char elem) { return acc + elem - '0'; });
        grouped.append(std::to_string(groupSum));
      }
      s = std::move(grouped);
    }

    return s;
  }
};
