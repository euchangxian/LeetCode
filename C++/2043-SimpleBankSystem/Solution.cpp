#include <utility>
#include <vector>

// (i+1)th account has balance[i] in account. (1-indexed account)
// A transaction is valid if:
// - given account number is between 1 and n.
// - amount withdrawn or transferred from is LTE the balance.
using i64 = long long;
class Bank {
 public:
  Bank(std::vector<i64>& balance) : balance_(std::move(balance)) {}

  // transfer from account1 to account2
  bool transfer(int account1, int account2, i64 money) {
    if (!valid(account1) || !valid(account2) || !withdraw(account1, money)) {
      return false;
    }
    return deposit(account2, money);
  }

  bool deposit(int account, i64 money) {
    if (!valid(account)) {
      return false;
    }
    balance_[account - 1] += money;
    return true;
  }

  bool withdraw(int account, i64 money) {
    if (!valid(account) || money > balance_[account - 1]) {
      return false;
    }
    balance_[account - 1] -= money;
    return true;
  }

 private:
  bool valid(int account) { return account >= 1 && account <= balance_.size(); }

  std::vector<i64> balance_;
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
