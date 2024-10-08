#include <vector>

class MyCircularQueue {
 private:
  const size_t mCapacity;
  size_t mSize;

  size_t mBack;
  std::vector<int32_t> mBuf;

 public:
  MyCircularQueue(int k) : mCapacity(k), mSize(0), mBack(0), mBuf(k) {}

  bool enQueue(int value) {
    if (isFull()) {
      return false;
    }

    mBuf[mBack] = value;
    mBack = (mBack + 1) % mCapacity;
    ++mSize;
    return true;
  }

  bool deQueue() {
    if (isEmpty()) {
      return false;
    }

    --mSize;
    return true;
  }

  int Front() {
    if (isEmpty()) {
      return -1;
    }
    // No need to convert 1-indexed mSize to 0-indexed. This is because mBack
    // is always pointing to the NEXT index where the value should be inserted.
    return mBuf[(mBack - mSize + mCapacity) % mCapacity];
  }

  int Rear() {
    if (isEmpty()) {
      return -1;
    }
    return mBuf[(mBack - 1 + mCapacity) % mCapacity];
  }

  bool isEmpty() { return mSize == 0; }

  bool isFull() { return mSize == mCapacity; }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
