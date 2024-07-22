use std::{cmp::Ordering, collections::BinaryHeap};

pub struct Solution {}

#[derive(PartialEq, Eq)]
pub struct Cell {
    cost: usize,
    position: (usize, usize),
}

impl Ord for Cell {
    fn cmp(&self, other: &Self) -> Ordering {
        // highest cost to be popped first
        self.cost.cmp(&other.cost)
    }
}

impl PartialOrd for Cell {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Solution {
    pub fn maximum_safeness_factor(grid: Vec<Vec<i32>>) -> i32 {
        let n: usize = grid.len();
        if grid[0][0] == 1 || grid[n - 1][n - 1] == 1 {
            return 0; // Will always go through a thief
        }
        println!("grid: {:?}", grid);

        let thiefs: Vec<(usize, usize)> = grid
            .iter()
            .enumerate()
            .flat_map(|(i, row)| {
                row.iter()
                    .enumerate()
                    .filter(|(_, &elem)| elem == 1)
                    .map(move |(j, _)| (i, j)) // Not too sure why move is needed.
            })
            .collect();

        println!("thiefs: {:?}", thiefs);

        // Assign a cost to each cell: the minimum MD of the cell to any thief.
        let mut costs: Vec<Vec<usize>> = Vec::with_capacity(n);
        for i in 0..n {
            costs.push(vec![0; n]);
            for j in 0..n {
                if grid[i][j] == 1 {
                    continue;
                }
                costs[i][j] = thiefs
                    .iter()
                    .map(|(tr, tc)| tr.abs_diff(i) + tc.abs_diff(j))
                    .min()
                    .unwrap(); // safe to just unwrap given problem constraints
            }
        }
        println!("costs: {:?}", costs);

        let mut heap: BinaryHeap<Cell> = BinaryHeap::new();
        let mut visited: Vec<Vec<bool>> = Vec::with_capacity(n);
        for _ in 0..n {
            visited.push(vec![false; n]);
        }

        let start: Cell = Cell {
            position: (0, 0),
            cost: costs[0][0],
        };
        heap.push(start);
        let directions: Vec<(i32, i32)> = vec![(0, 1), (1, 0), (0, -1), (-1, 0)];
        let mut min_cost: usize = usize::MAX;
        while let Some(current) = heap.pop() {
            if current.position.0 == n - 1 && current.position.1 == n - 1 {
                return min_cost.min(current.cost) as i32;
            }
            visited[current.position.0][current.position.1] = true;

            min_cost = min_cost.min(current.cost);
            let n: i32 = n as i32;
            for direction in &directions {
                let i_adj: i32 = (current.position.0 as i32) + direction.0;
                let j_adj: i32 = (current.position.1 as i32) + direction.1;

                if i_adj < 0 || j_adj < 0 || i_adj >= n || j_adj >= n {
                    continue;
                }

                let i_adj: usize = i_adj as usize;
                let j_adj: usize = j_adj as usize;
                if visited[i_adj][j_adj] {
                    continue;
                }

                heap.push(Cell {
                    position: (i_adj, j_adj),
                    cost: costs[i_adj][j_adj],
                })
            }
        }

        min_cost as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_maximum_safeness_factor() {
        assert_eq!(
            0,
            Solution::maximum_safeness_factor(vec![vec![1, 0, 0], vec![0, 0, 0], vec![0, 0, 1]])
        );
        assert_eq!(
            2,
            Solution::maximum_safeness_factor(vec![vec![0, 0, 1], vec![0, 0, 0], vec![0, 0, 0]])
        );
        assert_eq!(
            2,
            Solution::maximum_safeness_factor(vec![
                vec![0, 0, 0, 1],
                vec![0, 0, 0, 0],
                vec![0, 0, 0, 0],
                vec![1, 0, 0, 0]
            ])
        );
    }
}
