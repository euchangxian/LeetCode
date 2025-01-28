#include <cstddef>
#include <vector>

/**
 * Now that updates to existing values are supported, the prefix sum after
 * the updated idx must be updated, resulting in a worse case O(n) update, if
 * done naively.
 *
 * Binary-Indexed Trees (Fenwick Trees) solve this problem, allowing for O(logn)
 * updates.
 *
 * There are a few build-ups to arriving at a BIT.
 * 1. Naively, store the cumulative sum at each position in an array.
 *    This allows sumRange queries to be done in O(1) time, but updates will
 *    be O(n), as every cumulative sum after the updated idx have to be updated.
 *    too.
 *
 * 2. An alternative would be to store only the difference in cumulative sum.
 *    This allows updates to be done in O(1) time, but sumRange queries takes
 *    O(n) time, as the sum have to be recomputed each time.
 *
 * As such, there must be a way to represent the values differently, i.e., a
 * tree, such that we can precompute the cumulative sum in a way that allows
 * range queries to only require summing a small set of nodes and similarly,
 * allow updates to only affect a small set of nodes (both are paths to the
 * node, down (binary search)/up).
 *
 * Naive representation, using cumulative sums:
 * Cumulative Values: [ 5 ] [ 6 ] [21 ] [32 ] [84 ] [112] [112]
 * Bucket           :   1     2     3     4     5     6     7
 * Fast range sums, slow updates.
 *
 * Next naive Representation, using differences (between adjacent buckets):
 * [ +5] [ +1] [+15] [+11] [+52] [+28] [ +0]
 *   1     2     3     4     5     6     7
 * Fast updates, slow range sums.
 *
 * Tree representation storing cumulative sum (NOT YET BITs):
 *                  4
 *                [+32]
 *               /     \
 *            2           6
 *          [ +6]       [+80]
 *          /   \       /   \
 *         1     3     5     7
 *       [ +5] [+15] [+52] [ +0]
 *
 * To illustrate, suppose we have sumRange(1, 3) (for ease of illustration,
 * assume that this means the sum of nodes 2 to 3, where the start is
 * exclusive, unlike the actual problem where start is inclusive. The only
 * difference would be that every cumulative sum is shifted right).
 *
 * 1. Start at root (4). sum is 0.
 * 2. Go left to node (2). sum is 0.
 * 3. Go right to node (3). sum is 0 + 6 = 6.
 * 4. Find node (3). sum is 6 + 15 = 21.
 * 5. Start at root (4). sum is 21.
 * 6. Go left to node (2). sum is 21.
 * 8. Go left to node (1). sum is 21 - 5 = 16.
 *
 * For update(1, +5):
 * 1. Search for node (1) (either a binary search, or a lookup table).
 * 2. At node (1), increment its value by 5.
 * 3. Go to node (1)'s parent. Since node (1) is a left child of node (2),
 *    increment node (2)'s value by 5 too.
 * 4. Go to node (2)'s parent. Since node (2) is a left child of node (4),
 *    increment node (4)'s value by 5 too.
 *
 * Next, if we represent the bucket indices as binary values, we get:
 *                 100
 *                [+32]
 *               /     \
 *           010         110
 *          [ +6]       [+80]
 *          /   \       /   \
 *        001   011   101   111
 *       [ +5] [+15] [+52] [ +0]
 *
 * From this, we can make a nice observation! Notice that if find the rightmost
 * '1' bit in each number, and drop that bit, along with every bit that comes
 * after, we get:
 *                (empty)
 *                [+32]
 *               /     \
 *             0         1
 *          [ +6]       [+80]
 *          /   \       /   \
 *         00    01   10    11
 *       [ +5] [+15] [+52] [ +0]
 *
 * Notice that at each level, 0 means go left, and 1 means go right!
 * This also means that there is no need to consider whether a node is a left
 * child or a right child. The bits already encode the information. By
 * extracting and clearing the rightmost '1' bit at each level, we
 * automatically navigate the tree structure.
 *
 * This binary representation encodes the tree structure implicitly:
 * - Each index represents both a node and its path from the root.
 * - The rightmost '1' bit determines the "responsibility range" of each node.
 * - For example, 110 (6) is responsible for the sum of elements 5-6, while
 *   100 (4) is responsible for the sum of elements 1-4.
 *
 * When querying:
 * - We start from the target index and move up the tree.
 * - Clearing the rightmost '1' bit (n & (n-1)) moves us to the parent node.
 * - This process automatically accumulates the correct partial sums.
 *
 * When updating:
 * - We start from the target index and move up and to the right.
 * - Adding the rightmost '1' bit (n + (n & -n)) moves us to the next node
 *   that needs updating.
 * - This process automatically updates all affected partial sums.
 *
 * Suppose we want to find(7).
 * 1. n = 7 = 111
 * 2. Set sum to 0.
 * 3. Repeat while n > 0:
 *   a0. Add value at n = 7. sum =  0
 *   b0. Clear rightmost '1' bit at n (a mask). n = 6 = 110
 *   a1. Add value at n = 6. sum = 80
 *   b1. Clear rightmost '1' bit at n. n = 4 = 100
 *   a2. Add value at n = 4. sum = 80 + 32 = 112.
 *   b2. Clear rightmost '1' bit at n. n = 0. Stop.
 *
 * Therefore, cumulative sum at 7 = 112.
 *
 * Updates simply involve inverting the bits!
 * When updating, we move up and to the right in the tree:
 * 1. Start at the target index.
 * 2. Update the current node.
 * 3. Move to the next node by adding the rightmost '1' bit (n + (n & -n)).
 * 4. Repeat until we're out of the array bounds.
 *
 * This process ensures we update all nodes that include the target index
 * in their range, without explicitly tracking parent-child relationships.
 */
class NumArray {
 private:
  // Stores the current value of nums. For updating the cumulative differences
  // in the BIT.
  std::vector<int> nums_;

  // BIT stores the cumulative sum up to nums[i]
  std::vector<int> BIT_;

  // When updating a BIT, we propagate the change up the tree structure.
  // We move to all nodes responsible for the range including the updated index.
  //
  // The key operation is n += n & (-n). Let's break this down:
  //
  // Example: Updating index 1 in a BIT of size 8
  // Binary representation: 1 is 001 in 3-bit representation
  //
  // Step 1: n = 1 (001)
  //   n        = 001
  //   -n       = 111 (two's complement of 001)
  //   n & (-n) = 001 (isolates rightmost set bit)
  //   n += n & (-n) => 001 + 001 = 010 (2 in decimal)
  //
  // Step 2: n = 2 (010)
  //   n        = 010
  //   -n       = 110
  //   n & (-n) = 010
  //   n += n & (-n) => 010 + 010 = 100 (4 in decimal)
  //
  // Step 3: n = 4 (100)
  //   n        = 100
  //   -n       = 100
  //   n & (-n) = 100
  //   n += n & (-n) => 100 + 100 = 1000 (8 in decimal)
  //
  // The process stops here as 8 is the size of our BIT.
  //
  // This sequence (1 -> 2 -> 4 -> 8) represents the indices in the BIT
  // that need to be updated when we modify the value at index 1.
  //
  // Notice how this update affects all powers of 2 in the BIT (perfect binary
  // tree property!).
  // This is because index 1 contributes to all ranges in the tree.
  //
  // Contrast this with the query operation (n & (n-1)):
  // For find(1), we only need to access BIT[1], as n & (n-1) for 1 is 0.
  //
  // This demonstrates how update and query operations traverse the BIT
  // differently, both using efficient bit manipulation.
  void updateBIT(int n, int val) {
    while (n < BIT_.size()) {
      BIT_[n] += val;
      n += n & -n;
    }
  }

  // C++ represents negative numbers using 2's Complement, which inverts all
  // bits and add 1 to the result.
  // E.g., x = 12   // binary: 0000 1100
  // E.g., -x = -12 // binary: 1111 0100
  //
  // i.e., the shortcut to converting a number into its negative in 2's comp is:
  // From the back, see 0, keep 0. see 1. keep 1, invert all subsequent bits.
  //
  // This gives us a very efficient way of retrieving the rightmost '1' bit,
  // using x & -x
  int queryBIT(int n) {
    int sum = 0;
    while (n > 0) {
      sum += BIT_[n];
      n -= n & -n;
    }
    return sum;
  }

 public:
  NumArray(std::vector<int>& nums)
      : nums_(std::move(nums)), BIT_(nums_.size() + 1) {
    // O(nlogn), not optimal.
    // for (std::size_t i = 0; i < nums_.size(); ++i) {
    //   updateBIT(i + 1, nums_[i]);
    // }

    // Optimal O(n + m)
    // copy data to 1-indexed BIT first.
    for (std::size_t i = 0; i < nums_.size(); ++i) {
      BIT_[i + 1] = nums_[i];
    }

    for (int i = 1; i < BIT_.size(); ++i) {
      int parent = i + (i & -i);
      if (parent < BIT_.size()) {
        BIT_[parent] += BIT_[i];
      }
    }
  }

  void update(int index, int val) {
    // Check the difference using the original nums array. Update
    // correspondingly, traversing from the target node up to the parent.
    // inverted index.
    const int diff = val - nums_[index];  // Calculate the difference
    nums_[index] = val;  // Update the value in the original array

    updateBIT(index + 1, diff);
  }

  int sumRange(int left, int right) {
    // Get right cumsum and left cumsum
    return queryBIT(right + 1) - queryBIT(left);
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
