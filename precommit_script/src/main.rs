mod asset;
mod git;
mod language;
mod readme;
mod solution;
use std::time::Instant;

use std::cmp;

use solution::Solution;

const README: &str = "README.md";

// Times the execution of a function and prints the duration with a label.
#[cfg(debug_assertions)]
fn time_operation<F, T>(label: &str, operation: F) -> T
where
    F: FnOnce() -> T,
{
    let start = Instant::now();
    let result = operation();
    let duration = start.elapsed();
    println!("{} took: {:?}", label, duration);
    result
}

#[cfg(not(debug_assertions))]
fn time_operation<F, T>(_label: &str, operation: F) -> T
where
    F: FnOnce() -> T,
{
    operation()
}

fn main() -> Result<(), String> {
    let staged_files = time_operation("git diff", git::get_staged_files)?;
    let Some(solution_path) = time_operation("validate_staged_files", || {
        git::validate_staged_files(&staged_files)
    })?
    else {
        return Ok(());
    };

    let solution = time_operation("parsing solution struct", || {
        Solution::from_filepath(solution_path)
    })?;
    let mut lines = time_operation("opening README", || {
        readme::read_lines(README).map_err(|e| e.to_string())
    })?;

    // Use a temp file to ensure atomic Changes
    let temp_file = time_operation("creating temporary file", || {
        readme::create_temp_file(README)
    })?;
    let mut writer = std::io::BufWriter::new(temp_file);

    time_operation("writing until table separator", || {
        readme::write_until_table_separator(&mut lines, &mut writer)
    })?;

    time_operation("processing table", || -> Result<(), String> {
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

        if !found {
            readme::write_line(&mut writer, &solution.to_table_row())?;
        }

        Ok(())
    })?;

    time_operation(
        "finalizing readme update (flush writer, rename temp file)",
        || readme::finalize_readme_update(README, writer),
    )?;

    let out = time_operation("run formatter", git::format_readme)?;
    println!("{out}");
    Ok(())
}
