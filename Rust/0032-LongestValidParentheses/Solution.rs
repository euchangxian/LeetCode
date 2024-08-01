pub struct Solution {}

impl Solution {
    pub fn longest_valid_parentheses(s: String) -> i32 {
        if s.len() < 2 {
            return 0;
        }

        let s = s.as_bytes();

        // dp[i] represents the length of the longest valid parentheses substrings ending at the
        // i-th index
        let mut dp = vec![0; s.len()];
        for i in 1..s.len() {
            let c = s[i];
            if c == b'(' {
                continue; // dp[i] = 0
            }

            // Check i - (dp[i-1] + 1) >= 0
            // Attempts to find the potential matching opening parentheses '(' index,
            // since dp[i-1] represents the length of the longest valid parentheses at (i-1)-th index,
            // subtract the length of the current longest valid parentheses, then subtract 1 to
            // get the potential opening parentheses. E.g. for "()(())" at i = 5(last parentheses),
            // dp[i-1] = 2. Thus, i - dp[i-1] = 3, which represents the index of the inner opening
            // parentheses. Subtract 1 to get the index of the outer opening parentheses.
            if let Some(idx) = i.checked_sub(dp[i - 1] + 1) {
                if s[idx] == b'(' {
                    dp[i] = dp[i - 1] + 2;

                    // Handle the case where theres a valid parentheses substring before the
                    // matching opening parentheses.
                    if idx > 0 {
                        dp[i] += dp[idx - 1];
                    }
                }
            }
        }
        let max = dp.iter().max();
        match max {
            Some(val) => *val as i32,
            None => panic!("Vector of at least length 1 should have a max"),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_longest_valid_parentheses() {
        assert_eq!(2, Solution::longest_valid_parentheses("(()".to_string()));
        assert_eq!(4, Solution::longest_valid_parentheses(")()())".to_string()));
        assert_eq!(0, Solution::longest_valid_parentheses("".to_string()));
        assert_eq!(2, Solution::longest_valid_parentheses("()".to_string()));
        assert_eq!(6, Solution::longest_valid_parentheses("()(())".to_string()));
    }
}
