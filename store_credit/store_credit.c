#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRICES 2000

struct Case {
    int credit;
    int number_of_items;
    int prices[MAX_PRICES];
};

int readFile(char *filename, struct Case **cases_pointer) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to find the file.\n");
        return 0;
    }

    long unsigned int line_length = 0;
    char *line = NULL;
    int bytes_read;

    bytes_read = getline(&line, &line_length, fp);
    if (bytes_read == -1) {
        printf("Reading file failed.\n");
        return 0;
    }

    int N_cases  = strtol(line, NULL, 10);
    struct Case *cases = malloc(N_cases * sizeof(struct Case));
    int i, credit, number_of_items;

    for(i=0; i < N_cases; i++) {
        bytes_read = getline(&line, &line_length, fp);
        if (bytes_read == -1) {
            printf("Reading file failed.\n");
            return 0;
        }
        credit  = strtol(line, NULL, 10);
        cases[i].credit = credit;

        bytes_read = getline(&line, &line_length, fp);
        if (bytes_read == -1) {
            printf("Reading file failed.\n");
            return 0;
        }
        number_of_items  = strtol(line, NULL, 10);
        cases[i].number_of_items = number_of_items;

        bytes_read = getline(&line, &line_length, fp);
        char *tail = line;
        int j = 0;
        int price;
        for (j = 0; j < number_of_items; j++) {
            price  = strtol(tail, &tail, 10);
            cases[i].prices[j] = price;
        }
    }

    fclose(fp);
    free(line);
    *cases_pointer = cases;
    return N_cases;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("No file specified!");
        return 1;
    }

    struct Case *cases = NULL;
    int number_of_cases = readFile(argv[1], &cases);
    if (cases == NULL) {
        return 1;
    }
    int i, j, k, compare;
    for (i = 0; i < number_of_cases; i++) {
        bool done = false;
        for (j = 0; j < cases[i].number_of_items; j++) {
            if (done) {break;}
            compare = cases[i].prices[j];
            for (k = j + 1; k < cases[i].number_of_items; k++) {
                if (compare + cases[i].prices[k] == cases[i].credit) {
                    printf("Case #%i: %i %i\n", i + 1, j + 1, k + 1);
                    done = true;
                    break;
                }
            }
        }
    }
    free(cases);
    return 0;
}
