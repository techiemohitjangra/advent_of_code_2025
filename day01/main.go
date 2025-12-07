package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Instruction = struct {
	Direction rune
	TickCount int64
}

func parse_data(data []byte) []Instruction {
	lines := strings.Split(strings.Trim(string(data), "\n\t\r "), "\n")
	var instructions []Instruction = make([]Instruction, len(lines))
	for _, value := range lines {
		var direction rune
		if value[0] == 'R' {
			direction = 'R'
		} else {
			direction = 'L'
		}
		ticks, err := strconv.ParseInt(value[1:], 10, 32)
		if err != nil {
			log.Panicf("Failed to parse rotation count for instruction %s with error %s", value, err)
			os.Exit(1)
		}
		instructions = append(instructions, Instruction{
			direction,
			ticks,
		})
	}
	return instructions
}

func solve1(data []byte) (int64, error) {
	var instructions []Instruction = parse_data(data)
	var result int64 = 0
	var position int64 = 50
	for _, instruction := range instructions {
		if instruction.Direction == 'R' {
			position += instruction.TickCount
		} else {
			position -= instruction.TickCount
		}
		position %= 100
		if position == 0 {
			result += 1
		}
	}
	return result, nil
}

func solve2(data []byte) (int64, error) {
	var instructions []Instruction = parse_data(data)
	var result int64 = 0
	var position int64 = 50

	for _, instruction := range instructions {
		var old_position int64 = position
		result += instruction.TickCount / 100
		instruction.TickCount = instruction.TickCount % 100
		if instruction.Direction == 'R' {
			position += instruction.TickCount
		} else {
			position -= instruction.TickCount
		}
		if old_position != 0 && (position >= 100 || position <= 0) {
			result += 1
		}
		if position >= 100 {
			position -= 100
		}
		if position < 0 {
			position += 100
		}
	}
	return result, nil
}

func main() {
	argv := os.Args
	argc := len(argv)

	input_data_file_name := "data.txt"
	solution_data_file_name := "solution.txt"
	if argc == 1 {
		input_data_file_name = "./" + input_data_file_name
		solution_data_file_name = "./" + solution_data_file_name
	} else if argc == 2 {
		if strings.Compare(strings.ToLower(argv[1]), "test") == 0 {
			input_data_file_name = "./test_" + input_data_file_name
			solution_data_file_name = "./test_" + solution_data_file_name
		} else if strings.Compare(strings.ToLower(argv[1]), "full") == 0 {
			input_data_file_name = "./" + input_data_file_name
			solution_data_file_name = "./" + solution_data_file_name
		} else {
			log.Printf("Usage: %s [full|test]", argv[0])
			os.Exit(1)
		}
	} else {
		log.Printf("Usage: %s [full|test]", argv[0])
		os.Exit(1)
	}

	solution_file, err := os.Open(solution_data_file_name)
	if err != nil {
		log.Panicf("Failed to open solutions file with error %s", err)
		os.Exit(1)
	}

	solutions_stats, err := solution_file.Stat()
	if err != nil {
		log.Panicf("Failed to get the size of solutions file with error %s", err)
		os.Exit(1)
	}

	var solution_buffer []byte = make([]byte, solutions_stats.Size())
	solution_file.Read(solution_buffer)
	solutions_string := strings.Split(string(solution_buffer), " ")
	solutions := make([]int64, len(solutions_string))
	for index, value_string := range solutions_string {
		value, err := strconv.ParseInt(strings.Trim(value_string, "\n\t\r "), 10, 64)
		if err != nil {
			log.Panicf("Failed to parse solution: %s with error message %s", value_string, err)
			os.Exit(1)
		}
		solutions[index] = value
	}

	input_file, err := os.Open(input_data_file_name)
	if err != nil {
		log.Panicf("Failed to open solutions file with error %s", err)
		os.Exit(1)
	}

	input_stats, err := input_file.Stat()
	if err != nil {
		log.Panicf("Failed to get the size of solutions file with error %s", err)
		os.Exit(1)
	}

	var input_buffer []byte = make([]byte, input_stats.Size())
	input_file.Read(input_buffer)

	result1, err := solve1(input_buffer)
	if err != nil {
		log.Panicf("Failed to solve part 1 with error %s", err)
		os.Exit(1)
	}
	if result1 != solutions[0] {
		log.Panicf("assertion failure: %d == %d", result1, solutions[0])
		os.Exit(1)
	} else {
		fmt.Println(result1)
	}

	if len(solutions) == 2 {
		result2, err := solve2(input_buffer)
		if err != nil {
			log.Panicf("Failed to solve part 2 with error %s", err)
			os.Exit(1)
		}
		if result2 != solutions[1] {
			log.Panicf("assertion failure: %d == %d", result2, solutions[1])
			os.Exit(1)
		} else {
			fmt.Println(result2)
		}
	}
}
