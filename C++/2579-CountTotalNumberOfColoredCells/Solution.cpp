class Solution {
 public:
  long long coloredCells(int n) {
    // just maffs.
    // 1, 5, 13, 25,
    //  +4 +8  +12  ...
    //
    // an^2 + bn + c
    // 1st term = a+b+c
    // 2nd term = 4a+2b+c
    // 3rd term = 9a+4b+c
    //
    // Therefore, we can derive:
    // 1) 2a = second difference = 4
    // 2) 3a+b = 2nd term - 1st term = 4
    // 3) a+b+c = 1st term = 1
    //
    // Solving:
    // a = 2
    // b = -2
    // c = 1
    return (2LL * n * n) - (2LL * n) + 1;
  }
};
