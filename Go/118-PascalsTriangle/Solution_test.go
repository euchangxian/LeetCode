package lc118

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestGenerate(t *testing.T) {
	testCases := map[string]struct {
		numRows  int
		expected [][]int
	}{
		"Base case": {
			numRows: 1,
			expected: [][]int{
				{1},
			},
		},
		"Five rows": {
			numRows: 5,
			expected: [][]int{
				{1},
				{1, 1},
				{1, 2, 1},
				{1, 3, 3, 1},
				{1, 4, 6, 4, 1},
			},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := generate(tc.numRows)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
