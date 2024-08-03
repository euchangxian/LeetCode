#!/bin/bash

set -euo pipefail

# Function to get language icon
get_language_icon() {
  case $1 in
  cpp | cc) echo "![C++](assets/cpp.svg)" ;;
  go) echo "![Go](assets/go.svg)" ;;
  rs) echo "![Rust](assets/rust.svg)" ;;
  *) echo "![Unknown](assets/unknown.svg)" ;;
  esac
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
  echo "No changes to solution files detected. Exiting."
  exit 0
fi

# Function to insert or update a row in the table
update_table() {
  local number="$1"
  local problem_name="$2"
  local language_icon="$3"
  local temp_file=$(mktemp)

  awk -v num="$number" -v name="$problem_name" -v icon="$language_icon" '
  BEGIN { updated = 0; in_table = 0 }
  /^\| Code \| Problem Name \| Languages \|/ { in_table = 1; print; next }
  in_table && /^\| :--: \| :----------- \| :-------: \|/ { print; next }
  in_table && /^\|/ {
    split($0, a, "|")
    gsub(/^[ \t]+|[ \t]+$/, "", a[2])  # Trim whitespace
    if (a[2] == num) {
      printf("| %s | [%s](/%s-%s) | %s %s |\n", num, name, num, name, $NF, icon)
      updated = 1
    } else if (a[2] > num && !updated) {
      printf("| %s | [%s](/%s-%s) | %s |\n", num, name, num, name, icon)
      print $0
      updated = 1
    } else {
      print $0
    }
    next
  }
  in_table && /^$/ {
    if (!updated) {
      printf("| %s | [%s](/%s-%s) | %s |\n", num, name, num, name, icon)
    }
    in_table = 0
  }
  { print }
  END {
    if (in_table && !updated) {
      printf("| %s | [%s](/%s-%s) | %s |\n", num, name, num, name, icon)
    }
  }
  ' README.md >"$temp_file"

  mv "$temp_file" README.md
}

# Process changed files
echo "$CHANGED_SOLUTIONS" | while read -r file; do
  if [[ $file =~ /([0-9]{4})-([^/]+)/Solution\.(.+)$ ]]; then
    NUMBER=${BASH_REMATCH[1]}
    PROBLEM_NAME=${BASH_REMATCH[2]}
    EXTENSION=${BASH_REMATCH[3]}

    LANGUAGE_ICON=$(get_language_icon "$EXTENSION")

    update_table "$NUMBER" "$PROBLEM_NAME" "$LANGUAGE_ICON"
  fi
done

echo "README.md has been updated successfully."
