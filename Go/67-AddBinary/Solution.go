package lc67

import (
	"strconv"
	"strings"
)

func addBinary(a string, b string) string {
	if len(a) < len(b) {
		a, b = b, a
	}
	carry := 0
	result := make([]string, 0, len(a))
	i, j := len(a)-1, len(b)-1
	for i >= 0 || j >= 0 || carry > 0 {
		sum := carry

		if i >= 0 {
			sum += int(a[i] - '0')
			i--
		}

		if j >= 0 {
			sum += int(b[j] - '0')
			j--
		}

		// sum is at most 3 here.
		result = append(result, strconv.Itoa(sum%2))
		carry = sum / 2
	}

	var sb strings.Builder
	for k := len(result) - 1; k >= 0; k-- {
		sb.WriteString(result[k])
	}
	return sb.String()
}

// Given the constraints 1 <= a.length, b.length <= 10^4, it is clear that this problem is meant to be solved
// by manually adding bits.
func addBinaryDecimalConversion(a string, b string) string {
	aDecimal, _ := strconv.ParseInt(a, 2, 64)
	bDecimal, _ := strconv.ParseInt(b, 2, 64)

	return strconv.FormatInt(aDecimal+bDecimal, 2)
}
