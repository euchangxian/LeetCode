use crate::asset::Asset;
use crate::language::Language;
use std::path::Path;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Solution {
    pub id: u32, // technically, u16 is sufficient already. There are only 3k+ LC problems,
    pub name: String,
    pub languages: Vec<Language>,
}

impl Solution {
    pub fn from_filepath(file: &str) -> Result<Solution, String> {
        let path = Path::new(file);

        // Get the parent directory name (e.g., "0001-TwoSum")
        let dir_name = path
            .parent()
            .and_then(|p| p.file_name())
            .and_then(|oss| oss.to_str())
            .ok_or_else(|| format!("Invalid path structure: {}", file))?;

        let parts: Vec<&str> = dir_name.split('-').collect();
        if parts.len() < 2 {
            return Err(format!(
                "Unexpected directory name. Expected ID-Name, Got: {}",
                dir_name
            ));
        }

        let id = parts[0]
            .trim_start_matches('0')
            .parse::<u32>()
            .map_err(|_| format!("failed to parse problem ID from: {}", parts[0]))?;
        let name = parts[1].to_string();
        let lang = path
            .extension()
            .and_then(|ext| ext.to_str())
            .and_then(Language::from_extension)
            .ok_or_else(|| format!("Unsupported or missing file extension: {}", file))?;

        Ok(Solution {
            id,
            name,
            languages: vec![lang],
        })
    }

    pub fn from_table_row(row: &str) -> Result<Solution, String> {
        let parts: Vec<&str> = row
            .split('|')
            .map(|s| s.trim())
            .filter(|s| !s.is_empty())
            .collect();

        if parts.len() < 3 {
            return Err(format!("Failed to parse row: {}", row));
        }

        let id = parts[0]
            .parse::<u32>()
            .map_err(|e| format!("Failed to parse Problem ID: {}", e))?;
        let name = parts[1].to_string();
        let lang_part = parts[2];
        let languages: Vec<Language> = Language::iter()
            .filter(|lang| lang_part.contains(&format!("[![{}]", lang.as_str())))
            .cloned()
            .collect();

        Ok(Solution {
            id,
            name,
            languages,
        })
    }

    pub fn to_table_row(&self) -> String {
        let lang_icons = self
            .languages
            .iter()
            .map(|lang| {
                let asset_path = Asset::from_language(lang);
                let dir_name = format!("{:04}-{}", self.id, self.name);
                let file_path = lang.to_path(&dir_name);
                format!(
                    "[![{}]({})]({})", // [![Language](asset_path)](file_path)
                    lang.as_str(),
                    asset_path.display(),
                    file_path
                )
            })
            .collect::<Vec<_>>()
            .join(" ");

        format!("| {} | {} | {} |", self.id, self.name, lang_icons)
    }

    pub fn merge(&mut self, other: &Solution) {
        let mut languages: Vec<Language> = vec![];
        Language::iter()
            .filter(|lang| self.languages.contains(lang) || other.languages.contains(lang))
            .for_each(|lang| languages.push(lang.clone()));
        self.languages = languages;
    }
}
