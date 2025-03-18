class Solution {
 public:
  bool divisorGame(int n) {
    // initial number n, two players Alice and Bob, Alice starts first.
    // Each make a move every turn:
    // - choose any x such that 0 < x < n and n % x == 0, i.e., a factor of n.
    // - replace the number n with n-x.
    // If a player cannot make a move, they lose.
    // Return true iff Alice wins, assume optimal.
    //
    // Interesting that this appears as an easy, or am I dumb?
    // Note that 1 can always be picked as long as n > 1
    // if n = 1, then the player loses.
    // if n = 2, player wins.
    // if n = 3, only can pick 1, player loses.
    // if n = 4, only can pick 1, 2. Optimal to pick 1. player wins.
    // if n = 5, only pick 1, lose.
    // if n = 6, pick 1, win
    // ...
    // if n = 10, pick 1, win
    //
    // Inductively, it seems that even => wins, odd => lose.
    // How to prove?
    // If n is odd, any of its factors will be odd. Odd - odd = Even.
    // If N is even, we can always create an odd remainder by picking 1.
    // Thus, the other player will eventually end up with n = 1, losing.
    return n % 2 == 0;
  }
};
