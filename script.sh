#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <test_file>"
    exit 1
fi

TEST_FILE="$1"
LOG_FILE="valgrind_results.log"
DATE=$(date '+%Y-%m-%d %H:%M:%S')

# Clean previous log
echo "=== Valgrind Test Results - $DATE ===" > "$LOG_FILE"
echo "Test file: $TEST_FILE" >> "$LOG_FILE"
echo "----------------------------------------" >> "$LOG_FILE"

# Rebuild project
make re >> /dev/null 2>&1

# Process each line
while IFS= read -r cmd || [ -n "$cmd" ]; do
    [ -z "$cmd" ] && continue

    echo "Testing command: $cmd" >> "$LOG_FILE"
    echo "----------------------------------------" >> "$LOG_FILE"

    # Capture initial FD state
    echo "Initial FDs:" >> "$LOG_FILE"
    echo "$cmd" | ./minislay & 
    PID=$!
    sleep 0.1
    lsof -p $PID 2>/dev/null | grep -v "cwd\|txt\|mem\|rtd" >> "$LOG_FILE"

    # Kill the process
    kill $PID 2>/dev/null

    # Run valgrind tests
    echo "$cmd" | valgrind --leak-check=full \
                          --show-leak-kinds=all \
                          --track-fds=all \
						  --trace-children=yes \
                          --suppressions=toolbox_and_notes/readline.supp \
                          ./minislay 2>&1 | \
    grep -E "^==.*==.*(definitely|indirectly|possibly|still reachable|ERROR SUMMARY|Invalid|uninitialised|Process terminating|FILE DESCRIPTORS|Open file descriptor|Segmentation fault      (core dumped))" >> "$LOG_FILE"

    echo "----------------------------------------" >> "$LOG_FILE"
    echo "" >> "$LOG_FILE"
done < "$TEST_FILE"

echo "Tests completed. Results saved in $LOG_FILE"

# Enhanced grep for both memory leaks and FD leaks
echo "=== Memory Leaks ===" 
grep -n "lost: [^0]" "$LOG_FILE"
echo "=== FD Leaks ===" 
grep -n "Open file descriptor [^012]" "$LOG_FILE"
