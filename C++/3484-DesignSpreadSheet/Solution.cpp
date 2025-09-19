#include <array>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Spreadsheet is a grid of 26 columns labelled 'A' to 'Z', and a given
// number of rows.
// Each cell can hold a value between 0 and 1E5.
// Initialized to 0.
// Each cell is addressed by a string: #column#rowNumber, e.g., B10, 1-indexed
// row.
// setCell: set value in the specified cell.
// resetCell: set value in the specified cell to 0
// getValue: evaluate a formula of the form "=X+Y" where X and Y are either
// cell references, OR non-negative integers, and return the computed sum.
//
// There are some possible optimisations that can be made:
// 1. Lazy Initialization. Instead of zero-ing out the memory, we return 0
// only if its read without setting.
// This means that we avoid zero-ing out the allocated memory on construction
// of the Spreadsheet, and only do so when attempting to retrieve the value
// of a cell. Likely to be an insignificant performance gain, if any.
class Spreadsheet {
 public:
  Spreadsheet(int rows) : sheet(rows + 1, std::array<int, COLUMNS>{}) {}

  void setCell(std::string_view cell, int value) {
    auto [row, col] = getCellCoordinates(cell);
    sheet[row][col] = value;
  }

  void resetCell(std::string_view cell) { setCell(cell, 0); }

  int getValue(std::string_view formula) {
    // we want to ignore the first char '=', and the delimiter '+' to get
    // the operands.
    formula = formula.substr(1);
    auto plusPos = formula.find('+');

    auto op1 = formula.substr(0, plusPos);
    auto op2 = formula.substr(plusPos + 1);
    return getOperandValue(op1) + getOperandValue(op2);
  }

 private:
  constexpr static int COLUMNS = 26;

  constexpr static bool isCellReference(std::string_view operand) {
    return std::isalpha(operand[0]);
  }

  constexpr static std::pair<int, int> getCellCoordinates(
      std::string_view cell) {
    int col = cell[0] - 'A';
    int row = std::stoi(cell.substr(1).data());
    return {row, col};
  }

  int getOperandValue(std::string_view operand) {
    if (isCellReference(operand)) {
      auto [row, col] = getCellCoordinates(operand);
      return sheet[row][col];
    }

    return std::stoi(operand.data());
  }

  std::vector<std::array<int, COLUMNS>> sheet;
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */
