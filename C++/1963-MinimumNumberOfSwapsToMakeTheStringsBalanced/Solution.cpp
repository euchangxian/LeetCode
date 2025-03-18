#include <string>

class Solution {
 public:
  int minSwaps(std::string s) {
    // Stack? can keep track of unmatched pairs? Does not work with the case:
    // "]]][[[", where the stack would result in 3, but the answer is 2 swaps.
    // The optimal way is this sequence of swaps:
    // "[]][[]" => Swap index 0 ']' with index 5 '['
    // "[][][]" => Swap index 2 ']' with index 3 '['
    // GREEDY... greedily swap the first closing bracket ']' with the last
    // opening bracket '['.
    //
    // How to prove that the greedy choice is optimal?
    // Two cases:
    // 1. The last opening bracket '[' is unpaired. By swapping the first
    // closing bracket ']' with the last opening bracket '[', we reduce the
    // number of unpaired brackets by AT LEAST 1. This is because either the
    // pattern "[]...[]" or "[...]" occurs.
    //
    // 2. The last opening bracket '[' is paired. By swapping, the number of
    // unpaired brackets will either stay the same or reduce by 1.
    // E.g. Initially, "]...[]". By swapping, we get either "[]...[]" or
    // "[...[]" (stay the same).
    //
    // Correction: The above is not really a proof. Just an enumeration of
    // cases.
    // More precisely, given two unmatched pairs, we can always swap parentheses
    // such that only one swap is needed to match both pairs.
    // The question is how to prove this? IDK.
    //
    // Given this proof, we can easily arrive at the fact that the minimum
    // number of swaps required is math.ceil(numUnmatched / 2).
    //
    // Proof below by Claude, proof-read by ME
    // Proof of optimality:
    // 1. Lemma: In any valid bracket string, the number of unmatched '['
    //    equals the number of unmatched ']'.
    //    Proof: Total '[' must equal total ']' for validity. Any mismatch
    //    in one direction is balanced by a mismatch in the other.
    // 2. Definition: Unmatched '[' is a "right mismatch",
    //    unmatched ']' is a "left mismatch".
    // 3. Theorem: Any two mismatches (one left, one right) can be resolved
    //    with a single swap.
    //    Proof:
    //    - Consider leftmost left mismatch ']' and rightmost right mismatch
    //    '['.
    //    - Swapping these reduces total mismatches by 2:
    //      - ']' now matches with some '[' to its left.
    //      - '[' now matches with some ']' to its right.
    //      - True regardless of what's between them (from Lemma 1).
    // 4. Corollary: Minimum swaps needed = ceil(numUnmatched / 2).
    //    Proof:
    //    - numUnmatched is even (equal left and right mismatches, Lemma 1).
    //    - We can resolve any two mismatches with one swap (Theorem 3).
    //    - Therefore, we need numUnmatched / 2 swaps.
    //    - ceil() handles the case where numUnmatched is 0.

    int numUnmatched = 0;
    int openingBrackets = 0;  // like a Stack
    for (const char c : s) {
      if (c == '[') {
        ++openingBrackets;
        continue;
      }

      // c == ']'
      if (openingBrackets > 0) {
        --openingBrackets;
      } else {
        ++numUnmatched;
      }
    }

    return (numUnmatched + 1) / 2;
  }
};
