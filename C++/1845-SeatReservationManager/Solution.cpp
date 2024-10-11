#include <cstddef>
#include <functional>
#include <queue>
#include <vector>

using namespace std;
class SeatManager {
 private:
  priority_queue<int, vector<int>, greater<>> availableSeats;

 public:
  SeatManager(int n) {
    for (int i = 1; i <= n; ++i) {
      availableSeats.push(i);
    }
  }

  // Fetch smallest unreserved seat, reserves it and returns the number
  int reserve() {
    int smallestSeat = availableSeats.top();
    availableSeats.pop();
    return smallestSeat;
  }

  // unreserves the seat with the given seatNumber
  void unreserve(int seatNumber) { availableSeats.push(seatNumber); }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
