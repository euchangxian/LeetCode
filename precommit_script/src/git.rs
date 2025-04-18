use std::path::Path;
use std::process::Command;

// Execute `git diff --name-only --cached`
//
// Could fail if:
// - git executable is not found, or insufficient permissions.
// - Otherwise, not in a git repo, etc
pub fn get_staged_files() -> Result<Vec<String>, String> {
    let output = Command::new("git")
        .args(["diff", "--name-only", "--cached"])
        .output()
        .map_err(|e| format!("Failed to execute git command: {}", e))?;

    let stdout = String::from_utf8_lossy(&output.stdout);

    // Check process exit code
    if !output.status.success() {
        return Err(format!("Git command failed: {}", stdout));
    }
    let files: Vec<String> = stdout.lines().map(|line| line.to_string()).collect();
    Ok(files)
}

// Check that at most one Solution is staged per commit.
pub fn validate_staged_files(staged_files: &[String]) -> Result<Option<&String>, String> {
    let solutions: Vec<&String> = staged_files
        .iter()
        .filter(|file| {
            let filename = Path::new(file)
                .file_name()
                .and_then(|os_str| os_str.to_str());

            match filename {
                Some(name) => name.starts_with("Solution."),
                None => false,
            }
        })
        .collect();

    match solutions.len() {
        0 => Ok(None),
        1 => Ok(Some(solutions[0])),
        _ => Err(format!("Multiple Solution files staged: {:?}", solutions)),
    }
}

pub fn format_readme() -> Result<String, String> {
    let output = Command::new("dprint")
        .args(["fmt"])
        .output()
        .map_err(|e| format!("Failed to execute dprint fmt: {}", e))?;

    let stdout = String::from_utf8_lossy(&output.stdout);
    // Check process exit code
    if !output.status.success() {
        return Err(format!("dprint failed: {}", stdout));
    }
    Ok(stdout.to_string())
}
