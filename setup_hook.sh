#!/bin/bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HOOKS_DIR="$SCRIPT_DIR/.git/hooks"

# Ensure the hooks directory exists
mkdir -p "$HOOKS_DIR"

# Create the pre-commit hook
cat >"$HOOKS_DIR/pre-commit" <<EOL
#!/bin/bash

# Run the update_readme.sh script
"$SCRIPT_DIR/update_readme.sh"

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

# Make update_readme.sh executable
chmod +x "$SCRIPT_DIR/update_readme.sh"

echo "Git hooks have been set up successfully."
echo "The pre-commit hook will now run update_readme.sh before each commit."
