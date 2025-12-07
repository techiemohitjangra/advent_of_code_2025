#!/usr/bin/env bash

RED="\033[0;31m"
LIGHT_RED="\033[1;31m"
GREEN="\033[0;32m"
LIGHT_GREEN="\033[1;32m"
PURPLE="\033[0;35m"
LIGHT_PURPLE="\033[1;35m"
NO_COLOR="\033[0m"


SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
SCRIPT_NAME=$(basename "${BASH_SOURCE[0]}")


if [ $# -eq 0 ] || [ $# -gt 1 ] || [ $1 == "help" ] || [ $1 == "--help" ] || [ $1 == "-h" ]; then
    echo "Usage: $SCRIPT_NAME <directory_name>"
    exit 1
fi

if [[ ! -d "$SCRIPT_DIR/$1" ]]; then
    echo -e "${LIGHT_RED}ERROR${NO_COLOR}: $SCRIPT_DIR/$1 not found!" >&2
    exit 1
fi

for file in "$SCRIPT_DIR/templates/*"; do
    # [[ -f "$file" ]] || continue
    echo $file
    cp
done
