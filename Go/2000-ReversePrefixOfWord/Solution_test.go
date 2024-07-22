package lc2000

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestReversePrefix(t *testing.T) {
	testCases := map[string]struct {
		word     string
		ch       byte
		expected string
	}{
		"Multiple occurence of character": {
			word:     "abcdefd",
			ch:       'd',
			expected: "dcbaefd",
		},
		"Reverse first 4 characters": {
			word:     "xyxzxe",
			ch:       'z',
			expected: "zxyxxe",
		},
		"Character does not exist": {
			word:     "abcd",
			ch:       'z',
			expected: "abcd",
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := reversePrefix(tc.word, tc.ch)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
