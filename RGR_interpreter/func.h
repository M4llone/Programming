#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 100

typedef struct {
    int data[MAX_DEPTH];
    int top;
} SimpleStack;


int read_config(const char *config_file, char *out_input_file, int *out_debug_mode);
char* read_file(const char *bf_filename, int *out_size);
int check_data(const char *code);
void clear(char *tape, int size);
void save_to_file(const char *tape, int size);
void log_message(const char *level, const char *message);
int run_interpreter(const char *code, int code_size, char *tape, int tape_size, int debug_mode);

#endif
