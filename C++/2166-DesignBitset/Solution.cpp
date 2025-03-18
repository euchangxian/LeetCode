#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

/**
 * 1 <= size <= 10^5
 * Use an array of 32/64 bit integers?
 * Using a boolean array kinda defeats the purpose. Flipping a boolean array
 * is not straightforward too.
 *
 * Array of uint64_t works.
 *
 * NOTE:
 * The blocks in the bitset array are stored from left to right.
 * i.e., bitset[0] contains bits 0 to 63, bitset[1] contains bits 64 to 127, and
 * so on.
 * However (this tripped me up a little), it must be noted that the Least
 * Significant Bit within each block, which intuitively corresponds to position
 * 0, is the "rightmost" bit of the integer, instead of index 0.
 * This understanding is necessary for calculating the bit masks.
 *
 *
 * WARNING:
 * BUT this does not mean that the integer's bits are stored from right to left.
 * It depends on the endianness of the machine architecture.
 * Recap on Endianness:
 * Take for example a 32-bit integer 0x12345678,
 * - Big Endian (LSB comes first in memory): 12 34 56 78
 * - Little Endian (LSB comes first in memory): 78 56 34 12
 *
 * INFO:
 * For modulos with power of 2s, e.g. x % 2^n, it can be optimized to a bitmask
 * operation x & (2^n - 1).
 * This is due to the nature of binary representations.
 * 2^n - 1 produces a bitmask that has its lower n bits all set to 1. Applying
 * the bitwise AND operation effectively extracts the lower n bits of x, which
 * gives the same result as x % 2^n.
 *
 * ...
 * There is no need to walk the bitset for each all(), one(), count() operation.
 * A count of '1's and '0's can be maintained
 */
class Bitset {
 public:
  Bitset(int size)
      : size(size),
        blockCount((size + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK),
        zeros(size),
        ones(0),
        bitset{{}} {
    const std::size_t lastBlockBits = size & (BITS_PER_BLOCK - 1);

    // Handle the case where the size is a multiple of 64, i.e., the mask should
    // be all '1's
    lastBlockMask =
        lastBlockBits == 0 ? UINT64_MAX : ~(UINT64_MAX << lastBlockBits);
  }

  void fix(int idx) {
    // Determine the 'block' that this bit belongs to
    const std::size_t blockIdx = idx / BITS_PER_BLOCK;

    // Determine which bit in that block.
    const int bitPos = idx & (BITS_PER_BLOCK - 1);

    const uint64_t mask = 1ULL << bitPos;

    // Minus if not already set
    zeros -= (bitset[blockIdx] & mask) == 0;

    // Plus if not already set.
    ones += (bitset[blockIdx] & mask) == 0;

    // OR the 1 bit in.
    bitset[blockIdx] |= mask;
  }

  void unfix(int idx) {
    // Determine the 'block' that this bit belongs to
    const std::size_t blockIdx = idx / BITS_PER_BLOCK;

    // Determine which bit in that block.
    const int bitPos = idx & (BITS_PER_BLOCK - 1);

    const uint64_t mask = 1ULL << bitPos;

    // Minus if not already unset.
    ones -= (bitset[blockIdx] & mask) > 0;

    // Plus if not already unset.
    zeros += (bitset[blockIdx] & mask) > 0;

    // AND the 1 bit!
    bitset[blockIdx] &= ~mask;
  }

  void flip() {
    // For flip, there is no need to finely handle the extra bits in the last
    // block if any. Bookkeeping is done in the necessary read methods.
    for (std::size_t i = 0; i < blockCount; ++i) {
      bitset[i] = ~bitset[i];
    }
    std::swap(zeros, ones);
  }

  bool all() {
    // All bits are '1's
    return ones == size;
  }

  bool one() {
    // At least one '1' bit.
    return ones > 0;
  }

  int count() {
    // Count '1' bits.
    return ones;
  }

  std::string toString() {
    std::string repr;
    repr.reserve(size);

    for (std::size_t i = 0; i < size; ++i) {
      const std::size_t blockIdx = i / BITS_PER_BLOCK;
      const int bitPos = i & (BITS_PER_BLOCK - 1);

      const uint64_t mask = 1ULL << bitPos;

      // Avoid to_string, since I am not sure if there are unnecessary
      // allocations/copy. std::string is tough.
      if (bitset[blockIdx] & mask) {
        repr.push_back('1');
      } else {
        repr.push_back('0');
      }
    }

    return repr;
  }

 private:
  static constexpr std::size_t MAX_BITS = 100000;
  static constexpr std::size_t BITS_PER_BLOCK = sizeof(uint64_t) * 8;

  // ceiling division. Determines the number of uint64_t integer required to
  // represent 10^5 bits
  static constexpr std::size_t MAX_BLOCKS =
      (MAX_BITS + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;

  const std::size_t size;
  const std::size_t blockCount;

  // Since the number of bits is not guaranteed to be a multiple of 64, the last
  // block may have unrelated bits. Precalculate the mask for the last block.
  uint64_t lastBlockMask;

  // Keep track of the counts of '1's and '0's bits.
  std::size_t zeros;
  std::size_t ones;
  std::array<uint64_t, MAX_BLOCKS> bitset;
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */
