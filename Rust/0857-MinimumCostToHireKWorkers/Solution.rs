pub struct Solution {}

// Looks like a variant of 0/1 knapsack at first glance.
// Upon taking a closer look at the question requirements, it seems like the approach should be to
// take workers with a small difference between their wage/quality ratios.
impl Solution {
    pub fn mincost_to_hire_workers(quality: Vec<i32>, wage: Vec<i32>, k: i32) -> f64 {
        let k = k as usize;
        let mut workers: Vec<(f64, i32)> = quality
            .iter()
            .zip(wage.iter())
            .map(|(&q, &w)| (w as f64 / q as f64, q))
            .collect();

        // Sort workers by their wage-quality ratio
        workers.sort_by(|a, b| a.0.partial_cmp(&b.0).unwrap());

        let mut quality_heap = std::collections::BinaryHeap::new();
        let mut quality_sum = 0;
        let mut min_cost = f64::MAX;

        for (ratio, quality) in workers.iter() {
            quality_heap.push(quality);
            quality_sum += quality;

            // If there are already k workers in the heap, remove the one with the highest quality
            if quality_heap.len() > k {
                if let Some(high_quality) = quality_heap.pop() {
                    quality_sum -= high_quality;
                }
            }

            // calculate the cost
            if quality_heap.len() == k {
                let cost = ratio * quality_sum as f64;
                if cost < min_cost {
                    min_cost = cost;
                }
            }
        }

        min_cost
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    // Helper function to allow for tolerance when comparing floats.
    fn are_close(a: f64, b: f64, tolerance: f64) -> bool {
        (a - b).abs() < tolerance
    }
    const TOLERANCE: f64 = 1e-5;

    #[test]
    fn test_mincost_to_hire_workers() {
        assert!(are_close(
            105.00000,
            Solution::mincost_to_hire_workers(vec![10, 20, 5], vec![70, 50, 30], 2),
            TOLERANCE
        ));
        assert!(are_close(
            30.66667,
            Solution::mincost_to_hire_workers(vec![3, 1, 10, 10, 1], vec![4, 8, 2, 2, 7], 3),
            TOLERANCE
        ));
    }
}
