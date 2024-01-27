#!/bin/sh

REF_OUT=".refstd.out"
TEST_OUT=".teststd.out"
REF="bash --posix"
TEST="./../src/42sh"

$REF -c "echo toto" >"$REF_OUT"
$TEST -c "echo toto" >"$TEST_OUT"
diff "$REF_OUT" "$TEST_OUT"

rm $REF_OUT
rm $TEST_OUT
