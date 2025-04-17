use std::fs::File;
use std::io::{self, BufRead, BufWriter, Write};
use std::path::Path;

// The output is wrapped in a Result to allow matching on errors.
// Returns an Iterator to the Reader of the lines of the file.
pub fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

pub fn create_temp_file(readme_path: &str) -> Result<File, String> {
    File::create(format!("{}.tmp", readme_path))
        .map_err(|e| format!("Failed to create temp file: {}", e))
}

pub fn write_line<W: Write>(writer: &mut BufWriter<W>, line: &str) -> Result<(), String> {
    writeln!(writer, "{}", line).map_err(|e| format!("Failed to write to temp file: {}", e))
}

pub fn write_until_table_separator<R: BufRead, W: Write>(
    lines: &mut io::Lines<R>,
    writer: &mut BufWriter<W>,
) -> Result<(), String> {
    for line_result in lines.by_ref() {
        let line = line_result.map_err(|e| e.to_string())?;
        write_line(writer, &line)?;
        if line.starts_with("| :") {
            // stop at table separator
            break;
        }
    }
    Ok(())
}

pub fn finalize_readme_update<W: Write>(
    readme_path: &str,
    mut writer: BufWriter<W>,
) -> Result<(), String> {
    writer
        .flush()
        .map_err(|e| format!("Failed to flush writer: {}", e))?;
    std::fs::rename(format!("{}.tmp", readme_path), readme_path)
        .map_err(|e| format!("Failed to rename temp file: {}", e))
}
