use std::slice::Iter;

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Language {
    Cpp,
    Go,
    Rust,
}

impl Language {
    pub fn iter() -> Iter<'static, Language> {
        static LANGUAGES: [Language; 3] = [Language::Cpp, Language::Go, Language::Rust];
        LANGUAGES.iter()
    }

    // Convert from extension string to Language enum
    pub fn from_extension(ext: &str) -> Option<Self> {
        match ext {
            "cpp" => Some(Language::Cpp),
            "go" => Some(Language::Go),
            "rs" => Some(Language::Rust),
            _ => None,
        }
    }

    pub fn to_path(&self, dir_name: &str) -> String {
        match self {
            Language::Cpp => format!("C++/{}/Solution.cpp", dir_name),
            Language::Go => format!("Go/{}/Solution.go", dir_name),
            Language::Rust => format!("Rust/{}/Solution.rs", dir_name),
        }
    }

    pub fn as_str(&self) -> &str {
        match self {
            Language::Cpp => "C++",
            Language::Go => "Go",
            Language::Rust => "Rust",
        }
    }
}
