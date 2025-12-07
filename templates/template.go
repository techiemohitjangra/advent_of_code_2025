package main

import (
	"log"
	"os"
	"strconv"
	"strings"
)

// TODO
func solve1(data []byte) (int64, error) { return 0, nil }

// TODO
func solve2(data []byte) (int64, error) { return 0, nil }

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

	input_file, err := os.Open(solution_data_file_name)
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

	result2, err := solve2(input_buffer)
	if err != nil {
		log.Panicf("Failed to solve part 2 with error %s", err)
		os.Exit(1)
	}

	if result1 != solutions[0] {
		log.Panicf("assertion failure: %d == %d", result1, solutions[0])
		os.Exit(1)
	}
	if len(solutions) == 2 {
		if result2 != solutions[1] {
			log.Panicf("assertion failure: %d == %d", result2, solutions[1])
			os.Exit(1)
		}
	}
}
