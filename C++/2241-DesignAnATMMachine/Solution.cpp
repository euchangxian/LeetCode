#include <algorithm>
#include <array>
#include <vector>

// Denominations of 20, 50, 100, 200, 500 dollars.
// Users can deposit or withdraw any amount of money.
// When withdrawing, machine prioritizes larger value banknotes.
// E.g., withdraw(300), and there are 2x$50, 1x$100 and 1x$200.
// The machine will use the $100 and $200 notes.
// However, withdraw(600) with 3x$200, 1x$500 notes, the request will be
// rejected as the machine first tries to use the $500, and cannot complete
// the remaining $100.
// Just use a greedy approach?
// A binary search on the maximum number of banknotes usable at each level
// can be done.
// Ah. What a choke. Just division. LOL.
enum Idx : std::size_t {
  Twenty,
  Fifty,
  Hundred,
  TwoHundred,
  FiveHundred,
  N,
};

constexpr std::array<int, Idx::N> values{{20, 50, 100, 200, 500}};

class ATM {
 public:
  ATM() {}

  void deposit(std::vector<int> banknotesCount) {
    for (int i = 0; i < Idx::N; ++i) {
      notes[i] += banknotesCount[i];
    }
  }

  std::vector<int> withdraw(int amount) {
    std::vector<int> usedNotes(Idx::N);
    for (int i = Idx::N - 1; i >= 0 && amount > 0; --i) {
      usedNotes[i] = std::min(notes[i], amount / values[i]);

      notes[i] -= usedNotes[i];
      amount -= usedNotes[i] * values[i];
    }

    if (amount > 0) {
      // backtrack the amount
      for (int i = 0; i < Idx::N; ++i) {
        notes[i] += usedNotes[i];
      }
      return {-1};
    }

    return usedNotes;
  }

 private:
  std::array<int, Idx::N> notes{};
};

/**
 * Your ATM object will be instantiated and called as such:
 * ATM* obj = new ATM();
 * obj->deposit(banknotesCount);
 * vector<int> param_2 = obj->withdraw(amount);
 */
