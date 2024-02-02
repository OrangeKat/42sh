#! /bin/sh

flm_test() {
	local test_script=$1
	local description=$2
	echo "#!/bin/sh

    REF_OUT=\".refstd.out\"
    TEST_OUT=\".teststd.out\"
    REF_ERR=\".refstd.err\"
    TEST_ERR=\".teststd.err\"
    REF=\"bash --posix\"
    TEST=\"./../src/42sh\"

    COMMAND='$test_script'
    echo \$COMMAND >in

    cat in | \$REF >\"\$REF_OUT\" 2>\"\$REF_ERR\"
    REF_CODE= \$?
    cat in | \$TEST >\"\$TEST_OUT\" 2>\"\$TEST_ERR\"
    TEST_CODE= \$?
    diff \"\$REF_OUT\" \"\$TEST_OUT\"
    DIFF_CODE=\$?

    if [ \$REF_CODE -ne \$TEST_CODE ]; then
        echo \"wrong return code\"
    fi

    if [ \$DIFF_CODE -ne 0 ]; then
        echo \"wrong stdout\"
    fi

    diff \"\$REF_ERR\" \"\$TEST_ERR\"
    ERR_CODE=\$?

    if [ \$ERR_CODE -ne 0 ]; then
        echo \"wrong stderr\"
    fi

    rm \$REF_OUT
    rm \$TEST_OUT
    rm \$REF_ERR
    rm \$TEST_ERR
    rm in

    exit \$DIFF_CODE && \$ERR_CODE && [ \$REF_CODE -eq \$TEST_CODE]" >./categories/mass_produce/${description}.sh
<<<<<<< Updated upstream
	chmod +x "./categories/mass_produce/${description}.sh"
	echo "./categories/mass_produce/${description}.sh \\" >>Makefile.am
=======
    chmod +x "./categories/mass_produce/${description}.sh"
    #echo "./categories/mass_produce/${description}.sh \\" >> Makefile.am
>>>>>>> Stashed changes
}

flm_test "echo hello | tr e a | grep hal" "double_pipe"

flm_test "echo hello | grep hel" "single_pipe"

flm_test "cd ..; pwd" "simple_cd"

flm_test "cd ..; cd ./src; pwd; cd; pwd" "complex_cd"

flm_test "exit 255" "simple_exit"

flm_test "if exit 255; then echo qlqch; fi" "exit_if"

flm_test "echo hello > redir.txt" "simple_redir"

flm_test "while false; do echo hello; done" "simple_while"

flm_test "until true; do echo true; done" "simple_until"

flm_test "echo hello >> redir.txt" "simple_reredir"

flm_test "cat < Makefile.am" "simple_reverse_redir"

flm_test "echo hello >& redir.txt" "simple_and_redir"

flm_test "echo hello <> redir.txt" "simple_xor_redir"

flm_test "cat &< Makefile.am" "simple_reverse_and_redir"
