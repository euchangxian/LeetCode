package lc67

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestAddBinary(t *testing.T) {
	testCases := map[string]struct {
		a        string
		b        string
		expected string
	}{
		"Add 3 and 1 to make 4": {
			a:        "11",
			b:        "1",
			expected: "100",
		},
		"Add 10 and 11 to make 21": {
			a:        "1010",
			b:        "1011",
			expected: "10101",
		},
		"Add 4 and 50 to make 54": {
			a:        "100",
			b:        "110010",
			expected: "110110",
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			// t.Parallel()
			actual := addBinary(tc.a, tc.b)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
