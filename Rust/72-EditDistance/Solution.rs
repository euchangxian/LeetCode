pub struct Solution {}

// Similar to Longest Common Subsequence at first glance.
impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let m: usize = word1.len();
        let n: usize = word2.len();
        let word1 = word1.as_bytes();
        let word2 = word2.as_bytes();

        // dp[i][j] represents the minimum number of operations required to convert word1[0..i] to
        // word2[0..j].
        let mut dp: Vec<Vec<i32>> = Vec::with_capacity(m + 1);
        for _ in 0..m + 1 {
            dp.push(vec![0; n + 1])
        }

        // Init base cases: dp[i][0] = i, dp[0][j] = j
        // i.e. edges of the 'matrix'
        for (i, row) in dp.iter_mut().enumerate() {
            // different loop style since Clippy raises a warning.
            row[0] = i as i32;
        }
        for j in 0..n + 1 {
            dp[0][j] = j as i32;
        }

        for i in 1..m + 1 {
            for j in 1..n + 1 {
                // 1-indexed, minus 1 offset
                if word1[i - 1] == word2[j - 1] {
                    // No operations needed
                    dp[i][j] = dp[i - 1][j - 1];
                    continue;
                }
                // Compare insert (dp[i][j-1] + 1), replace (dp[i-1][j-1] + 1)
                // and delete (dp[i-1][j] + 1) operations
                dp[i][j] =
                    std::cmp::min(dp[i][j - 1], std::cmp::min(dp[i - 1][j - 1], dp[i - 1][j])) + 1;
            }
        }

        dp[m][n]
    }

    pub fn min_distance_1d(word1: String, word2: String) -> i32 {
        let m: usize = word1.len();
        let n: usize = word2.len();
        let word1 = word1.as_bytes();
        let word2 = word2.as_bytes();

        // dp[j] represents the minimum number of operations required to convert word1[0..i] to
        // word2[0..j] after the i-th iteration.
        // Base case: 0-th iteration, dp[j] = j
        let mut dp: Vec<i32> = (0..(n + 1) as i32).collect();

        for i in 1..m + 1 {
            let mut temp: Vec<i32> = dp.clone();
            temp[0] = i as i32;
            for j in 1..n + 1 {
                if word1[i - 1] == word2[j - 1] {
                    temp[j] = dp[j - 1];
                    continue;
                }
                temp[j] = std::cmp::min(temp[j - 1], std::cmp::min(dp[j - 1], dp[j])) + 1;
            }
            dp = temp;
        }
        dp[n]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_min_distance() {
        assert_eq!(
            3,
            Solution::min_distance("horse".to_string(), "ros".to_string())
        );
        assert_eq!(
            5,
            Solution::min_distance("intention".to_string(), "execution".to_string())
        );
        assert_eq!(
            3,
            Solution::min_distance_1d("horse".to_string(), "ros".to_string())
        );
        assert_eq!(
            5,
            Solution::min_distance_1d("intention".to_string(), "execution".to_string())
        );
    }
}
