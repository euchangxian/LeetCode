#!/bin/bash

set -euo pipefail

REPO_ROOT=$(git rev-parse --show-toplevel)
HOOKS_DIR="$REPO_ROOT/.git/hooks"

CARGO_PROJECT_NAME="precommit_script"
CARGO_PROJECT_DIR="$REPO_ROOT/$CARGO_PROJECT_NAME"
BUILD_PATH="$CARGO_PROJECT_DIR/target/release/$CARGO_PROJECT_NAME"
EXECUTABLE="update_readme"

# Ensure the hooks directory exists
mkdir -p "$HOOKS_DIR"

# Create the pre-commit hook
cat >"$HOOKS_DIR/pre-commit" <<EOL
#!/bin/bash

# Run the Executable
"$REPO_ROOT/$EXECUTABLE"

# Check if README.md was modified
if git diff --exit-code README.md; then
    # No changes to README.md, exit normally
    exit 0
else
    # README.md was modified, add it to the staged changes
    git add README.md
fi

# Exit successfully
exit 0
EOL

# Make the pre-commit hook executable
chmod +x "$HOOKS_DIR/pre-commit"

echo "Building Cargo project (release build)..."
cargo build --release --manifest-path "$CARGO_PROJECT_DIR/Cargo.toml"
cp "$BUILD_PATH" "$EXECUTABLE"

# Make update_readme.sh executable
chmod +x "$EXECUTABLE"

echo "Git hooks have been set up successfully."
echo "The pre-commit hook will now run update_readme before each commit."
