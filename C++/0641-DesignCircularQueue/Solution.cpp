#include <vector>
class MyCircularDeque {
private:
  const std::size_t mCapacity;

  std::size_t mSize;

  // Indicates where insertFront will place the element. Grows rightwards.
  std::size_t mFront;

  // Indicates where insertLast will place the element. Grows leftwards
  std::size_t mLast;

  // Circular buffer
  std::vector<int32_t> mBuf;

public:
  MyCircularDeque(int k)
      : mCapacity(k), mSize(0), mFront(0), mLast(k - 1), mBuf(k) {}

  inline bool insertFront(int value) {
    if (isFull()) {
      return false;
    }

    mBuf[mFront] = value;

    // Front pointer grows rightwards. Handle wrap-around
    mFront = (mFront + 1) % mCapacity;

    ++mSize;
    return true;
  }

  inline bool insertLast(int value) {
    if (isFull()) {
      return false;
    }

    mBuf[mLast] = value;

    // Back pointer grows leftwards. Handle wrap-around from 0.
    mLast = (mLast - 1 + mCapacity) % mCapacity;

    ++mSize;
    return true;
  }

  inline bool deleteFront() {
    if (isEmpty()) {
      return false;
    }

    // Move back the front pointer.
    mFront = (mFront - 1 + mCapacity) % mCapacity;
    --mSize;
    return true;
  }

  inline bool deleteLast() {
    if (isEmpty()) {
      return false;
    }

    mLast = (mLast + 1) % mCapacity;
    --mSize;
    return true;
  }

  inline int getFront() {
    if (isEmpty()) {
      return -1;
    }
    return mBuf[(mFront - 1 + mCapacity) % mCapacity];
  }

  inline int getRear() {
    if (isEmpty()) {
      return -1;
    }
    return mBuf[(mLast + 1) % mCapacity];
  }

  inline bool isEmpty() { return mSize == 0; }

  inline bool isFull() { return mSize == mCapacity; }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
