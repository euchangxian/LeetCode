#include <array>
#include <string>
#include <tuple>
#include <vector>

constexpr auto DIRECTION = std::array{
    "East",
    "North",
    "West",
    "South",
};

// width*height XY-plane: (0, 0) is bottom-left, (width-1,height-1) is
// top-right.
// Robot start at (0, 0), facing East
// step(num): attempt to move forward one cell in the direction it is facing.
// - If out of bounds, turn 90 degrees COUNTER-clockwise and retry the step
//
// Maintain Direction and Coordinates.
// Simulation is too slow.
// We need to observe that the Robot only moves on the boundaries of the Grid.
// Lol.
class Robot {
 public:
  Robot(int width, int height) {
    path.reserve(2 * (width + height - 4) + 4);

    // Bottom Edge: (0, 0) -> (width-1, 0) East
    for (int x = 0; x < width; ++x) {
      path.emplace_back(x, 0, 0);
    }

    // Right Edge: (width-1, 0) -> (width-1, height-1) North
    for (int y = 1; y < height; ++y) {
      path.emplace_back(width - 1, y, 1);
    }

    // Top Edge: (width-2, height-1) -> (0, height-1) West
    for (int x = width - 2; x >= 0; --x) {
      path.emplace_back(x, height - 1, 2);
    }

    // Left Edge: (0, height-2) -> (0, 0) South
    for (int y = height - 2; y > 0; --y) {
      path.emplace_back(0, y, 3);
    }

    // if the robot moves a full lap around the perimeter and ends back at
    // (0, 0), it will be facing South.
    std::get<2>(path[0]) = 3;
  }

  void step(int num) {
    moved = true;
    idx = (idx + num) % path.size();
  }

  std::vector<int> getPos() {
    auto [x, y, _] = path[idx];
    return {x, y};
  }

  std::string getDir() {
    if (!moved) {
      return "East";
    }

    return DIRECTION[std::get<2>(path[idx])];
  }

 private:
  bool moved{false};
  int idx{0};

  std::vector<std::tuple<int, int, int>> path;
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
