package lc2000

func reversePrefix(word string, ch byte) string {
	if len(word) < 2 {
		return word
	}

	indexOf := 0 // Stores index of the first occurence of ch in word
	for i, c := range []byte(word) {
		if c == ch {
			indexOf = i
			break
		}
	}

	reversed := make([]byte, 0, len(word))
	for i := indexOf; i >= 0; i-- {
		reversed = append(reversed, word[i])
	}
	for i := indexOf + 1; i < len(word); i++ {
		reversed = append(reversed, word[i])
	}
	return string(reversed)
}
