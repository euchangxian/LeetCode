pub struct Solution {}

impl Solution {
    pub fn length_of_last_word(s: String) -> i32 {
        return s
            .trim_end()
            .chars()
            .rev()
            .take_while(|c| c.is_alphabetic())
            .count() as i32;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_length_of_last_word() {
        assert_eq!(5, Solution::length_of_last_word("Hello World".to_string()));
        assert_eq!(
            4,
            Solution::length_of_last_word("   fly me   to   the moon  ".to_string())
        );
        assert_eq!(
            6,
            Solution::length_of_last_word("luffy is still joyboy".to_string())
        );
    }
}
