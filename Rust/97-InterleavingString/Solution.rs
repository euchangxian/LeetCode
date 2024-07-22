pub struct Solution {}

impl Solution {
    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        let n: usize = s1.len();
        let m: usize = s2.len();

        if n + m != s3.len() {
            return false;
        }

        let s1 = s1.as_bytes();
        let s2 = s2.as_bytes();
        let s3 = s3.as_bytes();

        // After the i-th iteration, dp[j] represents whether s3[0..i+j] can be obtained
        // from interleaving s1[0..i] and s2[0..j]
        let mut dp: Vec<bool> = vec![false; m + 1];
        dp[0] = true;
        for j in 1..m + 1 {
            dp[j] = dp[j - 1] && s2[j - 1] == s3[j - 1];
        }

        for i in 1..n + 1 {
            dp[0] = dp[0] && s3[i - 1] == s1[i - 1];
            for j in 1..m + 1 {
                dp[j] = (dp[j] && s3[i + j - 1] == s1[i - 1])
                    || (dp[j - 1] && s3[i + j - 1] == s2[j - 1]);
            }
        }

        dp[m]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_interleave() {
        assert!(Solution::is_interleave(
            "aabcc".to_string(),
            "dbbca".to_string(),
            "aadbbcbcac".to_string()
        ));
        assert!(!Solution::is_interleave(
            "aabcc".to_string(),
            "dbbca".to_string(),
            "aadbbbaccc".to_string()
        ));
        assert!(Solution::is_interleave(
            "".to_string(),
            "".to_string(),
            "".to_string()
        ));
        assert!(!Solution::is_interleave(
            "".to_string(),
            "".to_string(),
            "a".to_string()
        ));
    }
}
