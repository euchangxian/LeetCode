mod asset;
mod git;
mod language;
mod readme;
mod solution;

use std::cmp;

use solution::Solution;

const README: &str = "README.md";

fn main() -> Result<(), String> {
    let staged_files = git::get_staged_files()?;
    let Some(solution_path) = git::validate_staged_files(&staged_files)? else {
        return Ok(());
    };

    let solution = Solution::from_filepath(solution_path)?;
    let mut lines = readme::read_lines(README).map_err(|e| e.to_string())?;

    // Use a temp file to ensure atomic Changes
    let temp_file = readme::create_temp_file(README)?;
    let mut writer = std::io::BufWriter::new(temp_file);

    readme::write_until_table_separator(&mut lines, &mut writer)?;

    // At this point, should be at problem 1.
    let mut found: bool = false;
    for line in lines {
        let line = line.map_err(|e| e.to_string())?;
        if found {
            readme::write_line(&mut writer, &line)?;
            continue;
        }

        match Solution::from_table_row(&line) {
            Ok(mut curr) => {
                match curr.id.cmp(&solution.id) {
                    cmp::Ordering::Less => {
                        readme::write_line(&mut writer, &line)?;
                    }
                    cmp::Ordering::Equal => {
                        curr.merge(&solution);
                        readme::write_line(&mut writer, &curr.to_table_row())?;
                        found = true;
                    }
                    cmp::Ordering::Greater => {
                        readme::write_line(&mut writer, &solution.to_table_row())?;
                        readme::write_line(&mut writer, &curr.to_table_row())?;
                        found = true;
                    }
                };
            }
            Err(_) => {
                readme::write_line(&mut writer, &line)?;
            }
        }
    }

    readme::finalize_readme_update(README, writer)?;

    let out = git::format_readme()?;
    println!("{out}");
    Ok(())
}
