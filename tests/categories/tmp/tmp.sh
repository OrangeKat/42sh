#!/bin/bash

# Function to run a test case
run_test() {
	local test_script=$1
	local description=$2
	echo "Running test: $description"
	echo "Test script: $test_script"

	# Run the test on bash
	bash_out=$(bash -c "$test_script")
	bash_exit_code=$?

	# Run the test on 42sh
	_42sh_out=$(./../src/a.out -c "$test_script")
	_42sh_exit_code=$?

	# Compare outputs
	if [ "$bash_out" == "$_42sh_out" ]; then
		echo "PASS: Outputs are identical."
	else
		echo "FAIL: Outputs differ."
		echo "bash: $bash_out"
		echo "42sh: $_42sh_out"
	fi

	# Compare exit codes
	if [ $bash_exit_code -eq $_42sh_exit_code ]; then
		echo "PASS: Exit codes match."
	else
		echo "FAIL: Exit codes differ."
		echo "bash: $bash_exit_code"
		echo "42sh: $_42sh_exit_code"
	fi

	echo "-------------------------"
}

# Test cases with nesting and without variables

# Nested if within while loop
run_test "i=0; while [ \$i -lt 3 ]; do if [ \$((i % 2)) -eq 0 ]; then echo 'Even'; else echo 'Odd'; fi; i=\$((i+1)); done" "Nested if within while loop"

# Nested while within until loop
run_test "i=0; until [ \$i -eq 3 ]; do j=0; while [ \$j -lt \$i ]; do echo \$j; j=\$((j+1)); done; i=\$((i+1)); done" "Nested while within until loop"

# Nested if with true and false
run_test "if true; then if false; then echo 'Won't print'; else echo 'Will print'; fi; else echo 'Won't print'; fi" "Nested if with true and false"

# Nested if within seq and while loop
run_test "seq 1 5 | while read num; do if [ \$((num % 2)) -eq 0 ]; then if [ \$((num % 4)) -eq 0 ]; then echo 'Divisible by 4'; else echo 'Even but not by 4'; fi; else echo 'Odd'; fi; done" "Nested if within seq and while loop"

# End of script
echo "All tests completed."
