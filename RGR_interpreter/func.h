#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 100

// Простой стек для хранения адресов циклов
typedef struct {
    int data[MAX_DEPTH];
    int top;
} SimpleStack;

// Прототипы основных функций
int read_config(const char *config_file, char *out_input_file, int *out_debug_mode);
char* read_file(const char *bf_filename, int *out_size);
int check_data(const char *code);
void clear(char *tape, int size);
void save_to_file(const char *tape, int size);

// Функция логирования
void log_message(const char *level, const char *message);

// Интерпретатор (возвращает int для проверки в UNIT-тестах)
int run_interpreter(const char *code, int code_size, char *tape, int tape_size, int debug_mode);

#endif
