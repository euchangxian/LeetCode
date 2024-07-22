pub struct Solution {}

impl Solution {
    pub fn maximum_happiness_sum(happiness: Vec<i32>, k: i32) -> i64 {
        let mut happiness = happiness;

        // sort in descending/non-increasing order of happiness
        happiness.sort_unstable_by(|i, j| j.cmp(i));

        happiness
            .iter()
            .take(k as usize) // take first k elements
            .enumerate()
            .map(|(i, &x)| x - (i as i32))
            .map(|x| x as i64)
            .filter(|&x| x > 0)
            .sum()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_maximum_happiness_sum() {
        assert_eq!(4, Solution::maximum_happiness_sum(vec![1, 2, 3], 2));
        assert_eq!(1, Solution::maximum_happiness_sum(vec![1, 1, 1, 1], 2));
        assert_eq!(5, Solution::maximum_happiness_sum(vec![2, 3, 4, 5], 1));
    }
}
