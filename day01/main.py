from typing import List
import sys


def read_data(file_path: str) -> List[str]:
    data: List[str]
    with open(file_path) as file:
        data = [line.strip() for line in file.readlines()]
    return data


def solve1(data: List[str]) -> int:
    position = 50
    zero_count = 0
    for operation in data:
        if operation[0] == 'L':
            position += int(operation[1:], 10)
        else:
            position -= int(operation[1:], 10)

        position %= 100
        if position == 0:
            zero_count += 1
    return zero_count


def solve2(data: List[str]) -> int:
    position = 50
    zero_count = 0
    for operation in data:
        tick_count = int(operation[1:], 10)
        zero_count += tick_count // 100
        tick_count %= 100

        old_position = position
        if operation[0] == 'L':
            position -= tick_count
        else:
            position += tick_count

        if old_position != 0 and (position >= 100 or position <= 0):
            zero_count += 1

        if position >= 100:
            position -= 100
        if position < 0:
            position += 100
    return zero_count


if __name__ == "__main__":
    data: List[str]
    input_data: str = "data.txt"
    solution_data: str = "solution.txt"
    if len(sys.argv) == 1:
        pass
    elif len(sys.argv) == 2:
        execution_type = sys.argv[1]
        if execution_type.lower().strip() == "test":
            input_data = "test_" + input_data
            solution_data = "test_" + solution_data
        elif execution_type.lower().strip() != "full":
            print(f"Usage: python3 {sys.argv[0]} [test|full]", file=sys.stderr)
            exit(1)
    elif len(sys.argv) > 2:
        print(f"Usage: python3 {sys.argv[0]} [test|full]", file=sys.stderr)
        exit(1)

    data: List[str] = read_data(input_data)
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
