package lc402

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestRemoveKDigits(t *testing.T) {
	testCases := map[string]struct {
		num      string
		k        int
		expected string
	}{
		"No zeroes in num": {
			num:      "1432219",
			k:        3,
			expected: "1219",
		},
		"Some zeroes in num": {
			num:      "10200",
			k:        1,
			expected: "200",
		},
		"k is equal to digits in num": {
			num:      "10",
			k:        2,
			expected: "0",
		},
		"Removing 1 digit results in 0": {
			num:      "100000",
			k:        1,
			expected: "0",
		},
		"num is monotonically non-decreasing": {
			num:      "123456789",
			k:        3,
			expected: "123456",
		},
		"More zeroes than non-zeros": {
			num:      "100001",
			k:        4,
			expected: "0",
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := removeKDigits(tc.num, tc.k)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
