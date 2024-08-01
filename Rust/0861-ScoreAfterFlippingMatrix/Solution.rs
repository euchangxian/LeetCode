pub struct Solution {}

// For rows, greedily set the most-significant bits/left-most bits to 1.
// For columns, toggle such that there are more 1 bits than 0.
// A toggle can be intepreted as a bitwise XOR(^) operation.
// i32::from_str_radix(str: String, base: i32)
impl Solution {
    pub fn matrix_score(grid: Vec<Vec<i32>>) -> i32 {
        let mut grid: Vec<Vec<i32>> = grid;
        let n: usize = grid[0].len();

        // count the number of occurences of 1s in each column.
        let mut frequencies: Vec<i32> = vec![0; n];

        // Toggle rows if the MSB is 0.
        for row in grid.iter_mut() {
            let flip = row[0] == 0;
            for (j, num) in row.iter_mut().enumerate() {
                *num = if flip { 1 - *num } else { *num };
                frequencies[j] += *num;
            }
        }
        // For each column, if the frequencies are LTE floor of m/2, then toggle it.
        let m: usize = grid.len();
        for (j, freq) in frequencies.iter().enumerate() {
            if *freq > (m as i32) / 2 {
                continue;
            }
            for row in grid.iter_mut() {
                row[j] = if row[j] == 1 { 0 } else { 1 };
            }
        }

        let mut sum: i32 = 0;

        for row in grid {
            let mut exp: u32 = n as u32;
            for num in row {
                sum += num * i32::pow(2, exp - 1);
                exp -= 1;
            }
        }

        sum
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_matrix_score() {
        assert_eq!(
            39,
            Solution::matrix_score(vec![vec![0, 0, 1, 1], vec![1, 0, 1, 0], vec![1, 1, 0, 0]])
        );
        assert_eq!(1, Solution::matrix_score(vec![vec![0]]));
    }
}
