pub struct Solution {}

impl Solution {
    pub fn get_maximum_gold(grid: Vec<Vec<i32>>) -> i32 {
        let mut grid: Vec<Vec<i32>> = grid;
        let mut max_gold: i32 = 0;
        for i in 0..grid.len() {
            for j in 0..grid[0].len() {
                max_gold = max_gold.max(Solution::dfs(&mut grid, i, j));
            }
        }
        max_gold
    }

    fn dfs(grid: &mut Vec<Vec<i32>>, row: usize, col: usize) -> i32 {
        // check bounds. No need check negative, since usize does not allow negatives.
        if row >= grid.len() || col >= grid[0].len() || grid[row][col] == 0 {
            return 0;
        }

        let original_gold: i32 = grid[row][col];
        grid[row][col] = 0; // mark as visited

        let mut max_gold: i32 = 0;
        // Left, Right, Up, Down
        let directions: Vec<(i32, i32)> = vec![(0, -1), (0, 1), (-1, 0), (1, 0)];
        for direction in directions {
            let new_row = (row as i32) + direction.0;
            let new_col = (col as i32) + direction.1;
            if new_row < 0 || new_col < 0 {
                continue;
            }
            max_gold = max_gold.max(Solution::dfs(grid, new_row as usize, new_col as usize));
        }

        grid[row][col] = original_gold;
        max_gold + original_gold
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_maximum_gold() {
        assert_eq!(
            24,
            Solution::get_maximum_gold(vec![vec![0, 6, 0], vec![5, 8, 7], vec![0, 9, 0]])
        );
        assert_eq!(
            28,
            Solution::get_maximum_gold(vec![
                vec![1, 0, 7],
                vec![2, 0, 6],
                vec![3, 4, 5],
                vec![0, 3, 0],
                vec![9, 0, 20]
            ])
        );
    }
}
