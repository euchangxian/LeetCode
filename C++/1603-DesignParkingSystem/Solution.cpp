#include <array>
#include <cstddef>

using namespace std;
class ParkingSystem {
 private:
  const int big = 1;
  const int medium = 2;
  const int small = 3;

  std::array<int, 4> parkingLots;

 public:
  ParkingSystem(int big, int medium, int small) : parkingLots{{}} {
    parkingLots[this->big] = big;
    parkingLots[this->medium] = medium;
    parkingLots[this->small] = small;
  }

  bool addCar(int carType) {
    if (parkingLots[carType] == 0) {
      return false;
    }
    --parkingLots[carType];
    return true;
  }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
