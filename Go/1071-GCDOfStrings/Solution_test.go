package lc1071

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestGCDOfStrings(t *testing.T) {
	testCases := map[string]struct {
		str1     string
		str2     string
		expected string
	}{
		"str2 is GCD": {
			str1:     "ABCABC",
			str2:     "ABC",
			expected: "ABC",
		},
		"Part of str2 is GCD": {
			str1:     "ABABAB",
			str2:     "ABAB",
			expected: "AB",
		},
		"No GCD": {
			str1:     "LEET",
			str2:     "CODE",
			expected: "",
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := GCDOfStrings(tc.str1, tc.str2)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
