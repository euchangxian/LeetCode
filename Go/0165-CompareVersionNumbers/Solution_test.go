package lc165

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestCompareVersion(t *testing.T) {
	testCases := map[string]struct {
		version1 string
		version2 string
		expected int
	}{
		"Leading zeroes should be ignored. Equal versions": {
			version1: "1.01",
			version2: "1.001",
			expected: 0,
		},
		"Unspecified revisions should be ignored. Equal versions": {
			version1: "1.0",
			version2: "1.0.0",
			expected: 0,
		},
		"Revisions should be compared in left-to-right order": {
			version1: "0.1",
			version2: "1.0",
			expected: -1,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := compareVersion(tc.version1, tc.version2)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
