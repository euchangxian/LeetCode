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
