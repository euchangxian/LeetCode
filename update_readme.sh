#!/bin/sh
set -e

# Function to get language icon with link
get_language_icon_with_link() {
  extension=$1
  path=$2
  case $extension in
  cpp)
    icon="C++"
    asset="c++.svg"
    ;;
  go)
    icon="Go"
    asset="go.svg"
    ;;
  rs)
    icon="Rust"
    asset="rust.svg"
    ;;
  *)
    icon="Unknown"
    asset="unknown.svg"
    ;;
  esac
  echo "[![$icon](assets/$asset)]($path)"
}

# Check if README.md exists
if [ ! -f README.md ]; then
  echo "Error: README.md not found in the current directory."
  exit 1
fi

# Get the list of staged files
STAGED_FILES=$(git diff --cached --name-only)

# Filter for Solution.* files
CHANGED_SOLUTIONS=$(echo "$STAGED_FILES" | grep -E 'Solution\.[^/]+$' || true)

# If no solution files have changed, exit early
if [ -z "$CHANGED_SOLUTIONS" ]; then
  exit 0
fi

# Create a temporary file to store new table rows
temp_rows_file=$(mktemp)

# Process changed files and accumulate new rows
echo "$CHANGED_SOLUTIONS" | while read -r file; do
  if echo "$file" | grep -qE '([^/]+)/([0-9]{4})-([^/]+)/Solution\.(.+)$'; then
    NUMBER=$(echo "$file" | sed -E 's/[^/]+\/([0-9]{4})-([^/]+)\/Solution\.(.+)$/\1/')
    PROBLEM_NAME=$(echo "$file" | sed -E 's/[^/]+\/([0-9]{4})-([^/]+)\/Solution\.(.+)$/\2/')
    EXTENSION=$(echo "$file" | sed -E 's/[^/]+\/([0-9]{4})-([^/]+)\/Solution\.(.+)$/\3/')
    LANGUAGE_ICON=$(get_language_icon_with_link "$EXTENSION" "$file")
    echo "| $NUMBER | $PROBLEM_NAME | $LANGUAGE_ICON |" >>"$temp_rows_file"
  fi
done

# Function to batch update the README table
batch_update_table() {
  awk -v new_rows="$(cat "$temp_rows_file")" '
  BEGIN {
    split(new_rows, updates, "\n")
    in_table = 0
  }
  /^\| *Code *\| *Problem Name *\| *Languages *\|/ { in_table = 1; print; next }
  in_table && /^\| *:?-+:? *\| *:?-+:? *\| *:?-+:? *\|/ { print; next }
  in_table && /^\|/ {
    code_num = $2
    gsub(/^[ \t]+|[ \t]+$/, "", code_num)
    if (length(code_num) > 0) {
      for (i in updates) {
        split(updates[i], fields, "|")
        num = fields[2]
        gsub(/^[ \t]+|[ \t]+$/, "", num)
        if (num == code_num) {
          print updates[i]
          delete updates[i]
          found = 1
          break
        }
      }
      if (!found) print $0
    } else {
      print $0
    }
    next
  }
  in_table && /^$/ {
    for (i in updates) if (updates[i] !~ /^[ \t]*$/) print updates[i]
    in_table = 0
  }
  { print }
  END {
    if (in_table) {
      for (i in updates) if (updates[i] !~ /^[ \t]*$/) print updates[i]
    }
  }
  ' README.md >README.tmp && mv README.tmp README.md
}

# Update README in batch
batch_update_table

# Clean up temporary rows file
rm -f "$temp_rows_file"

# Run prettier to format README
npx prettier --write README.md
