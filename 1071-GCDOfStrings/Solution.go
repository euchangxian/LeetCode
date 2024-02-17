package lc1071

func GCDOfStrings(str1 string, str2 string) string {
	// Check if theres a divisor at all
	if str1+str2 != str2+str1 {
		return ""
	}

	gcd := euclidsGCD(len(str2), len(str1))

	return str1[0:gcd]
}

func euclidsGCD(m int, n int) int {
	if m == 0 {
		return n
	}
	return euclidsGCD(n%m, m)
}
