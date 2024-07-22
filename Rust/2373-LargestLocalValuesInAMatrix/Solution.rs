pub struct Solution {}

impl Solution {
    pub fn largest_local(grid: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let n: usize = grid.len();
        let m: usize = n - 3 + 1;

        let mut max_local: Vec<Vec<i32>> = Vec::with_capacity(m);
        for _ in 0..m {
            max_local.push(vec![0; m])
        }

        for i in 1..n - 1 {
            for j in 1..n - 1 {
                max_local[i - 1][j - 1] = *grid[i - 1..=i + 1]
                    .iter()
                    .flat_map(|row| &row[j - 1..=j + 1])
                    .max()
                    .unwrap(); // safe to unwrap assuming grid has correct dimensions
            }
        }
        max_local
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_largest_local() {
        assert_eq!(
            vec![vec![9, 9], vec![8, 6]],
            Solution::largest_local(vec![
                vec![9, 9, 8, 1],
                vec![5, 6, 2, 6],
                vec![8, 2, 6, 4],
                vec![6, 2, 2, 2]
            ])
        );
        assert_eq!(
            vec![vec![2, 2, 2], vec![2, 2, 2], vec![2, 2, 2]],
            Solution::largest_local(vec![
                vec![1, 1, 1, 1, 1],
                vec![1, 1, 1, 1, 1],
                vec![1, 1, 2, 1, 1],
                vec![1, 1, 1, 1, 1],
                vec![1, 1, 1, 1, 1]
            ])
        );
    }
}
