#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

class Solution {
 public:
  std::string shiftingLetters(std::string s,
                              std::vector<std::vector<int>>& shifts) {
    // shifts[i] = [start, end, direction]
    // shift the characters in s[start..end] inclusive, left (0) or right (1).
    // Mhm, some form of intervals. Brute-force updates will result in O(nq).
    // Probably need to accumulate the resultant shifts for each index i.
    // Line-sweep/sorting would be useful.
    constexpr int ALPHAS{26};

    // Assign -1 to Left, +1 to Right for Start events.
    // Negate for End events. We also want to +1 to the end idx, to denote
    // inclusive ends.
    //
    // shifts = [[0,1,0],[1,2,1],[0,2,1]]
    // events = [0, 1, 1, -2]
    std::vector<int> events(s.size() + 1, 0);
    for (const auto& shift : shifts) {
      int direction = shift[2] == 0 ? -1 : 1;
      events[shift[0]] += direction;
      events[shift[1] + 1] -= direction;
    }

    int rightShifts = 0;
    for (int i = 0; i < s.size(); ++i) {
      rightShifts += events[i];

      // Handle left shifts, i.e., negative modulos.
      s[i] = ((((s[i] - 'a' + rightShifts) % ALPHAS) + ALPHAS) % ALPHAS) + 'a';
    }
    return s;
  }
};
