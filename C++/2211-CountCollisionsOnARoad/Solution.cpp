#include <ranges>
#include <string_view>

enum Direction {
  Left = 'L',
  Right = 'R',
  Stationary = 'S',
};

class Solution {
 public:
  int countCollisions(std::string_view directions) {
    // N cars on an inifinitely long road, labelled 0 to n-1.
    // directions[i] = L | R | S indicating going left, right or stationary.
    // All cars have the same speed if moving.
    // If two cars moving in oppposite directions collide, number of collisions
    // is 2.
    // If a moving car collide with a stationary car, number of collisions is 1.
    // After a collision, cars involve will remain at the point they collided.
    // Return total number of collisions.
    //
    // Monotonic Stack of Right and Stationary cars.
    // Iterating left to right, we want to maintain a stack of cars going
    // right or stationary.
    // If we encounter a stationary car: Increase collisions by 1 for the top
    // of the stack and pop the car off.
    // Then, for each remaining car in the stack, increase collisions by 1 and
    // pop them off.
    // At the end, we will have a stationary car at the top.
    // If we encounter a left-going car: increase collisions by 2. Then same
    // as stationary: pop remaining and increase by 1 each.
    // If we have a stationary car, and we encounter a right-going car, then
    // remove that stationary car.
    //
    // We can simplify to maintain a running count of either stationary or
    // right-going, where stationary = 0 | 1, rightGoing >= 0
    int collisions = 0;
    Direction top = Direction::Left;  // works as a sentinel value
    int stk = 0;
    for (Direction d : directions | std::ranges::views::transform(
                                        [](char c) { return Direction(c); })) {
      switch (d) {
        case Direction::Left:
          if (stk > 0) {
            collisions += top == Direction::Stationary ? 1 : stk + 1;

            // reset stack
            stk = 1;
            top = Direction::Stationary;
          }
          break;
        case Direction::Right:
          if (stk > 0 && top == Direction::Stationary) {
            stk = 1;
          } else {
            ++stk;
          }
          top = Direction::Right;
          break;
        case Direction::Stationary:
          if (stk > 0 && top == Direction::Right) {
            collisions += stk;
          }
          stk = 1;
          top = Direction::Stationary;
          break;
      }
    }
    return collisions;
  }
};
