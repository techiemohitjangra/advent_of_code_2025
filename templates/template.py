import sys
from typing import List


def read_data(file_name: str) -> str:
    data: str
    with open(file_name, "r") as file:
        data = file.read()
    return data


# TODO
def solve1(data):
    pass


# TODO
def solve2(data):
    pass


if __name__ == "__main__":
    data: str
    input_data: str = "data.txt"
    solution_data: str = "solution.txt"
    if len(sys.argv) == 1:
        input_data = "./"+input_data
        solution_data = "./"+solution_data
    elif len(sys.argv) == 2:
        execution_type = sys.argv[1]
        if execution_type.lower().strip() == "test":
            input_data = "./test_" + input_data
            solution_data = "./test_" + solution_data
        elif execution_type.lower().strip() == "full":
            input_data = "./"+input_data
            solution_data = "./"+solution_data
        else:
            print(f"Usage: python3 {sys.argv[0]} [test|full]", file=sys.stderr)
            exit(1)
    elif len(sys.argv) > 2:
        print(f"Usage: python3 {sys.argv[0]} [test|full]", file=sys.stderr)
        exit(1)

    data: str = read_data(input_data)
    solutions: (int, int)
    with open(solution_data) as file:
        solutions = tuple(int(sol) for sol in file.readline().strip().split())

    result1 = solve1(data)
    print(result1)
    assert result1 == solutions[0]
    if len(solutions) > 1:
        result2 = solve2(data)
        print(result2)
        assert result2 == solutions[1]
