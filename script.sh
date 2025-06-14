#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <test_file>"
    exit 1
fi

TEST_FILE="$1"
LOG_FILE="valgrind_results.log"
COMMAND_FILE="command_results.txt"
DATE=$(date '+%Y-%m-%d %H:%M:%S')

# Clean previous logs
echo "=== Valgrind Test Results - $DATE ===" > "$LOG_FILE"
echo "=== Commands with Memory Issues - $DATE ===" > "$COMMAND_FILE"
echo "Test file: $TEST_FILE" >> "$LOG_FILE"
echo "----------------------------------------" >> "$LOG_FILE"

# Counter for command number
command_number=0

# Rebuild project
make re >> /dev/null 2>&1

# Process each line
while IFS= read -r cmd || [ -n "$cmd" ]; do
    [ -z "$cmd" ] && continue
    ((command_number++))

    echo "[$command_number] Testing: $cmd" >> "$COMMAND_FILE"
    echo "Testing command: $cmd" >> "$LOG_FILE"
    echo "----------------------------------------" >> "$LOG_FILE"

    # Run valgrind and store results
    echo "$cmd" | valgrind --leak-check=full \
                          --show-leak-kinds=all \
                          --track-fds=all \
                          --trace-children=yes \
                          --suppressions=toolbox_and_notes/readline.supp \
                          ./minislay 2>&1 | \
    grep -E "==.*==.*((definitely|indirectly|possibly) lost: [1-9][0-9]* bytes|Invalid (read|write|free)|reachable: [1-9][0-9]*)" >> "$LOG_FILE"

    echo "----------------------------------------" >> "$LOG_FILE"
    echo "" >> "$LOG_FILE"
done < "$TEST_FILE"

echo "=== Memory Issues Summary ==="

# Extract and categorize errors
echo -e "\nInvalid memory operations:"
grep -n "Invalid" "$LOG_FILE" | while read -r line; do
    line_num=${line%%:*}
    cmd=$(head -n "$line_num" "$LOG_FILE" | grep "Testing command:" | tail -n1)
    if [ ! -z "$cmd" ]; then
        echo "  $cmd"
    fi
done | sort -u

echo -e "\nMemory leaks:"
grep -n "lost:" "$LOG_FILE" | while read -r line; do
    line_num=${line%%:*}
    cmd=$(head -n "$line_num" "$LOG_FILE" | grep "Testing command:" | tail -n1)
    if [ ! -z "$cmd" ]; then
        echo "  $cmd"
    fi
done | sort -u

echo -e "\nDetailed results saved in $LOG_FILE"
