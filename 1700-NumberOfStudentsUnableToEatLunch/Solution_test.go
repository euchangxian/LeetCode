package lc1700

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestCountStudents(t *testing.T) {
	testCases := map[string]struct {
		students   []int
		sandwiches []int
		expected   int
	}{
		"All students are able to eat": {
			students:   []int{1, 1, 0, 0},
			sandwiches: []int{0, 1, 0, 1},
			expected:   0,
		},
		"3 students are unable to eat": {
			students:   []int{1, 1, 1, 0, 0, 1}, // remaining students: {1, 1, 1}
			sandwiches: []int{1, 0, 0, 0, 1, 1}, // remaining sandwiches: {0, 1, 1}
			expected:   3,
		},
		"1 student unable to eat. Order of Sandwiches matter": {
			students:   []int{1, 1, 1, 0, 0, 1}, // remaining students: {1}
			sandwiches: []int{1, 0, 0, 1, 1, 0}, // remaining sandwiches: {0}
			expected:   1,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := countStudents(tc.students, tc.sandwiches)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
