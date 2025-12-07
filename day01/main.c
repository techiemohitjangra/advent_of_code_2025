#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 128

typedef struct {
    size_t first;
    size_t second;
} SolutionPair, *PSolutionPair;

SolutionPair get_solution(char *solution_data_file_name);
size_t solve1(const char *const data, const size_t size);
size_t solve2(const char *const data, const size_t size);

SolutionPair get_solution(char *solution_data_file_name) {
    SolutionPair result = {0};

    int solution_data_file = open(solution_data_file_name, O_RDONLY);
    struct stat stat;
    fstat(solution_data_file, &stat);

    char *data = (char *)malloc(sizeof(char) * stat.st_size);
    read(solution_data_file, data, stat.st_size);

    char *endptr;

    result.first = strtoll(data, &endptr, 10);
    result.second = strtoll(endptr, &endptr, 10);

    free(data);
    return result;
}

size_t solve1(const char *const data, const size_t size) {
    int32_t position = 50;
    size_t result = 0;
    register size_t i = 0;
    do {
        if (!isalnum(data[i])) {
            i += 1;
            continue;
        }
        char direction = data[i];
        i += 1;
        size_t tick_count = 0;
        while (isdigit(data[i])) {
            tick_count = (tick_count * 10) + (data[i] - '0');
            i += 1;
        }
        if (direction == 'L') {
            position -= tick_count;
        } else {
            position += tick_count;
        }
        position %= 100;
        if (position == 0) {
            result += 1;
        }
    } while (i < size);
    return result;
}

size_t solve2(const char *const data, const size_t size) {
    int32_t position = 50;
    size_t zero_count = 0;
    int32_t old_position = 0;
    register size_t i = 0;
    do {
        if (!isalnum(data[i])) {
            i += 1;
            continue;
        }
        char direction = data[i];
        i += 1;
        size_t tick_count = 0;
        while (isdigit(data[i])) {
            tick_count = (tick_count * 10) + (data[i] - '0');
            i += 1;
        }

        zero_count += tick_count / 100;
        tick_count %= 100;

        old_position = position;
        if (direction == 'L') {
            position -= tick_count;
        } else {
            position += tick_count;
        }

        if (old_position != 0 && (position >= 100 || position <= 0)) {
            zero_count += 1;
        }
        if (position >= 100) {
            position -= 100;
        }
        if (position < 0) {
            position += 100;
        }
    } while (i < size);
    return zero_count;
}

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
