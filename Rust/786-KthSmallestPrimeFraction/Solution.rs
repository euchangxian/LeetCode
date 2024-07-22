pub struct Solution {}

// Given a strictly increasing array of 1 and prime numbers, it seems like a binary search
// problem intuitively.
// However, binary searching for the k-th smallest fraction given elements that could be
// numerators OR denominators is not straightforward.
//
// A naive approach would be to have two pointers, one at the left-most to take the
// smallest numerator, and one at the right-most to take the largest numerator, forming the
// smallest fraction. But this is wrong.
// E.g. arr = [1, 2, 5], k = 2. Naively taking 1/2 (0.5) as the second fraction will be
// wrong, since 2/5 (0.4) is a smaller fraction and is the second smallest fraction.
//
// Another naive (but correct) approach will simply be enumerating all possible fractions,
// then sorting and taking the k-th smallest fraction. This takes O(n^2) space-time.
impl Solution {
    pub fn kth_smallest_prime_fraction(arr: Vec<i32>, k: i32) -> Vec<i32> {
        let n: usize = arr.len();
        let mut fractions: Vec<Vec<i32>> = Vec::with_capacity(n * (n + 1) / 2);

        for i in 0..n {
            for j in i + 1..n {
                fractions.push(vec![arr[i], arr[j]]);
            }
        }

        fractions.sort_by(|frac1, frac2| {
            let num1 = frac1[0] as f64;
            let denom1 = frac1[1] as f64;
            let num2 = frac2[0] as f64;
            let denom2 = frac2[1] as f64;

            (num1 / denom1).total_cmp(&(num2 / denom2))
        });

        let kth_fraction = &fractions[(k - 1) as usize]; // borrow occurs here...
        vec![kth_fraction[0], kth_fraction[1]]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_kth_smallest_prime_fraction() {
        assert_eq!(
            vec![2, 5],
            Solution::kth_smallest_prime_fraction(vec![1, 2, 5], 2)
        );
        assert_eq!(
            vec![2, 5],
            Solution::kth_smallest_prime_fraction(vec![1, 2, 3, 5], 3)
        );
        assert_eq!(
            vec![1, 7],
            Solution::kth_smallest_prime_fraction(vec![1, 7], 1)
        );
    }
}
