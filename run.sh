#!/usr/bin/env bash

C_SOURCE_FILES="main.c"
RUST_SOURCE_FILES="main.rs"
PYTHON_SOURCE_FILES="main.py"
GO_SOURCE_FILES="main.go"
ZIG_SOURCE_FILES="main.zig"


RED="\033[0;31m"
LIGHT_RED="\033[1;31m"
GREEN="\033[0;32m"
LIGHT_GREEN="\033[1;32m"
PURPLE="\033[0;35m"
LIGHT_PURPLE="\033[1;35m"
NO_COLOR="\033[0m"


# arg1: lang[string]
# arg2: part[int]
# arg3: expected[int]
# arg4: found[int]
function check_solution(){
    lang=$1
    part=$2
    expected=$3
    found=$4

    if [ "$expected" -ne "$found" ]; then
        echo -e "${LIGHT_RED}[ERROR]${NO_COLOR}: ${lang} part${part} mismatched"
        echo -e "\t${PURPLE}Expected${NO_COLOR}: ${expected}"
        echo -e "\t${PURPLE}Found${NO_COLOR}: ${found}"
        return 1
    else
        echo -e "${LIGHT_GREEN}[SUCCESS]${NO_COLOR}: ${lang} part${part}"
        return 0
    fi
}

function validate_solutions(){
    mode=$1
    part1_solution=$2
    part2_solution=$3

    # cleanup
    mkdir -p build
    rm -r build/*

    # compile
    go_sol=( $(go run ${GO_SOURCE_FILES} $mode 2>&1) )
    c_sol=( $(clang -Wall -Wextra -Wdeprecated ${C_SOURCE_FILES} -o build/c_main && ./build/c_main $mode 2>&1) )
    python_sol=( $(python3 ${PYTHON_SOURCE_FILES} $mode 2>&1) )
    rust_sol=( $(rustc ${RUST_SOURCE_FILES} -o build/rust_main && ./build/rust_main $mode 2>&1) )
    zig_sol=( $(zig build-exe main.zig -femit-bin=build/zig_main && ./build/zig_main $mode 2>&1) )

    check_solution "go" 1 $part1_solution ${go_sol[0]}
    check_solution "go" 2 $part2_solution ${go_sol[1]}

    check_solution "rust" 1 $part1_solution ${rust_sol[0]}
    check_solution "rust" 2 $part2_solution ${rust_sol[1]}

    check_solution "zig" 1 $part1_solution ${zig_sol[0]}
    check_solution "zig" 2 $part2_solution ${zig_sol[1]}

    check_solution "python" 1 $part1_solution ${python_sol[0]}
    check_solution "python" 2 $part2_solution ${python_sol[1]}

    check_solution "c" 1 $part1_solution ${c_sol[0]}
    check_solution "c" 2 $part2_solution ${c_sol[1]}
}

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
SCRIPT_NAME=$(basename "${BASH_SOURCE[0]}")

if [ $# -eq 0 ] || [ $# -gt 2 ]; then
    echo "Usage: $SCRIPT_NAME <full|test> <day_directory>"
    exit 1
fi

DAY_DIR="$SCRIPT_DIR/$2"

if [ $1 == "full" ]; then
    DAY_FILE="$DAY_DIR/solution.txt"
elif [ $1 == "test" ];then
    DAY_FILE="$DAY_DIR/test_solution.txt"
else
    echo "Usage: $SCRIPT_NAME <full|test> <day_directory>"
    exit 1
fi

if [[ ! -d "$DAY_DIR" ]]; then
    echo -e "${LIGHT_RED}ERROR${NO_COLOR}: $DAY_DIR not found!" >&2
    exit 1
fi

if [[ ! -f "$DAY_FILE" ]]; then
    echo -e "${LIGHT_RED}ERROR${NO_COLOR}: $DAY_FILE not found!" >&2
    exit 1
fi
MODE=$1
validate_solutions $MODE $(cat $DAY_FILE)
