use crate::language::Language;
use std::path::PathBuf;

#[non_exhaustive]
pub struct Asset;
impl Asset {
    pub const CPP: &str = "assets/c++.svg";
    pub const GO: &str = "assets/go.svg";
    pub const RUST: &str = "assets/rust.svg";

    pub fn from_language(lang: &Language) -> PathBuf {
        match lang {
            Language::Cpp => PathBuf::from(Asset::CPP),
            Language::Go => PathBuf::from(Asset::GO),
            Language::Rust => PathBuf::from(Asset::RUST),
        }
    }
}
