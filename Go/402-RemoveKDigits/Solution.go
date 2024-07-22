package lc402

import (
	"strconv"
	"strings"
)

func removeKDigits(num string, k int) string {
	if len(num) <= k {
		return "0"
	}

	// Monotonically non-decreasing stack. Represents the final number after removing k digits.
	nums := make([]int, 0, len(num))

	for _, r := range num {
		// Unicode: Characters '0', '1', ..., '9' are encoded consecutively in the Unicode
		// table. That is, '0': 48, '1': 49, ..., '9': 57.
		// Suppose the rune r represents a digit. Then, taking the unicode difference
		// between r and '0' returns the actual integer representation of the digit.
		digit := int(r - '0')

		// Since the digits are iterated in decreasing significance,
		// while there are still digits to be removed (k > 0)
		for k > 0 && len(nums) > 0 {
			previousDigit := nums[len(nums)-1]

			if previousDigit <= digit {
				break // simply add digit to the stack
			}

			// Pop previousDigit and decrement k to maintain monotonicity of stack.
			nums = nums[:len(nums)-1]
			k--
		}

		// Numbers do not start with a 0, i.e. discard leading zeros
		if len(nums) == 0 && digit == 0 {
			continue
		}
		nums = append(nums, digit)
	}

	// Case where digits in num are non-decreasing, resulting in no digits removed earlier
	if k > 0 {
		nums = nums[:len(nums)-min(len(nums), k)] // remove top k digits
	}

	// No remaining digits that are non-zero
	if len(nums) == 0 {
		return "0"
	}

	var result strings.Builder
	for _, digit := range nums {
		result.WriteString(strconv.Itoa(digit))
	}

	return result.String()
}
