#include <assert.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 128

typedef struct {
    int32_t first;
    int32_t second;
} SolutionPair, *PSolutionPair;

SolutionPair get_solution(char *solution_data_file_name);
size_t solve1(const char *const data, const size_t size);
size_t solve2(const char *const data, const size_t size);

SolutionPair get_solution(char *solution_data_file_name) {
    SolutionPair result = {0};

    int solution_data_file = open(solution_data_file_name, O_RDONLY);
    struct stat stat;
    int err = fstat(solution_data_file, &stat);

    char *data = (char *)malloc(sizeof(char) * stat.st_size);
    read(solution_data_file, data, stat.st_size);

    char *endptr;

    result.first = strtoll(data, &endptr, 10);
    result.second = strtoll(endptr, &endptr, 10);

    free(data);
    return result;
}

// TODO
size_t solve1(const char *const data, const size_t size) { return 0; }

// TODO
size_t solve2(const char *const data, const size_t size) { return 0; }

int main(int argc, char **argv) {
    char input_data_file_name[BUFFER_SIZE] = "data.txt";
    char solution_data_file_name[BUFFER_SIZE] = "solution.txt";
    char buf[BUFFER_SIZE] = {0};
    if (argc == 1) {
        snprintf(buf, BUFFER_SIZE - 1, "%s%s", "./", input_data_file_name);
        strncpy(input_data_file_name, buf, BUFFER_SIZE - 1);
        snprintf(buf, BUFFER_SIZE - 1, "%s%s", "./", solution_data_file_name);
        strncpy(solution_data_file_name, buf, BUFFER_SIZE - 1);
    } else if (argc == 2) {
        char *execution_type = argv[1];
        if (!strncasecmp(execution_type, "test", 5)) {
            snprintf(buf, BUFFER_SIZE - 1, "%s%s", "./test_",
                     input_data_file_name);
            strncpy(input_data_file_name, buf, BUFFER_SIZE - 1);
            snprintf(buf, BUFFER_SIZE - 1, "%s%s", "./test_",
                     solution_data_file_name);
            strncpy(solution_data_file_name, buf, BUFFER_SIZE - 1);
        } else if (!strncasecmp(execution_type, "full", 5)) {
            snprintf(buf, BUFFER_SIZE - 1, "%s%s", "./", input_data_file_name);
            strncpy(input_data_file_name, buf, BUFFER_SIZE - 1);
            snprintf(buf, BUFFER_SIZE - 1, "%s%s", "./",
                     solution_data_file_name);
            strncpy(solution_data_file_name, buf, BUFFER_SIZE - 1);
        } else {
            printf("Usage: %s [test|full]\n", argv[0]);
            exit(1);
        }
    } else if (argc > 2) {
        printf("Usage: %s [test|full]\n", argv[0]);
        exit(1);
    }

    SolutionPair solutions = get_solution(solution_data_file_name);

    int input_data_file = open(input_data_file_name, O_RDONLY);
    struct stat stat;
    fstat(input_data_file, &stat);

    char *input_data =
        mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, input_data_file, 0);

    size_t result1 = solve1(input_data, stat.st_size);
    printf("%ld\n", result1);
    assert(result1 == solutions.first);

    size_t result2 = solve2(input_data, stat.st_size);
    printf("%ld\n", result2);
    assert(result2 == solutions.second);

    munmap(input_data, stat.st_size);
    return 0;
}
