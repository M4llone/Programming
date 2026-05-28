#include "func.h"
#include <string.h>

// Реализация логирования с уровнями
void log_message(const char *level, const char *message) {
    FILE *log_file = fopen("app.log", "a");
    if (log_file != NULL) {
        fprintf(log_file, "[%s] %s\n", level, message);
        fclose(log_file);
    }
}

// Надежный парсер конфигурационного файла KEY=VALUE
int read_config(const char *config_file, char *out_input_file, int *out_debug_mode) {
    FILE *f = fopen(config_file, "r");
    if (!f) {
        printf("Err: Конфигурационный файл <%s> не найден\n", config_file);
        log_message("ERROR", "Config file not found");
        return 0;
    }

    char line[256];
    int has_input = 0;
    int has_debug = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;
        
        if (line[i] == '\n' || line[i] == '\r' || line[i] == '\0' || line[i] == '#') continue;

        if (line[i] == 'i' && line[i+1] == 'n' && line[i+2] == 'p' && line[i+3] == 'u' && line[i+4] == 't') {
            i += 5;
            while (line[i] != '=' && line[i] != '\0') i++;
            if (line[i] == '=') {
                i++;
                while (line[i] == ' ' || line[i] == '\t') i++;
                int k = 0;
                while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r' && k < 127) {
                    out_input_file[k++] = line[i++];
                }
                out_input_file[k] = '\0';
                has_input = 1;
            }
        }
        else if (line[i] == 'd' && line[i+1] == 'e' && line[i+2] == 'b' && line[i+3] == 'u' && line[i+4] == 'g') {
            i += 5;
            while (line[i] != '=' && line[i] != '\0') i++;
            if (line[i] == '=') {
                i++;
                while (line[i] == ' ' || line[i] == '\t') i++;
                if (line[i] >= '0' && line[i] <= '9') {
                    *out_debug_mode = line[i] - '0';
                    has_debug = 1;
                }
            }
        }
    }
    fclose(f);

    if (!has_input || !has_debug) {
        log_message("ERROR", "Config file has invalid format or missing keys");
        return 0;
    }

    log_message("INFO", "Config file read successfully");
    return 1;
}

char* read_file(const char *bf_file, int *size_bf) {
    FILE *in = fopen(bf_file, "rb"); 
    if (in == NULL) {
        printf("Не удалось открыть файл с кодом '%s'\n", bf_file);
        log_message("ERROR", "Failed to open brainfuck source file");
        return NULL;
    }

    int size = 0;
    char ch;
    while ((ch = fgetc(in)) != EOF) size++;

    fclose(in);
    in = fopen(bf_file, "rb");

    char *code = (char*)malloc((size + 1) * sizeof(char));
    if (code == NULL) {
        log_message("ERROR", "Memory allocation failed for code buffer");
        fclose(in);
        return NULL;
    }
    
    for (int i = 0; i < size; i++) code[i] = fgetc(in);
    code[size] = '\0'; 
    fclose(in);

    log_message("INFO", "Brainfuck source file loaded successfully");
    *size_bf = size; 
    return code;
}

int check_data(const char *code) {
    int count = 0;
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '[') count++;
        if (code[i] == ']') count--;
        if (count < 0) {
            log_message("ERROR", "Syntax error: Unmatched closing bracket ']'");
            return 0;
        }
    }
    if (count != 0) {
        log_message("ERROR", "Syntax error: Unmatched opening bracket '['");
        return 0;
    }
    log_message("INFO", "Syntax validation passed");
    return 1;
}

void clear(char *type, int size) {
    for (int i = 0; i < size; i++) type[i] = 0;
}

void save_to_file(const char *type, int size) {
    FILE *dump = fopen("brain_view.txt", "w");
    if (dump != NULL) {
        for (int i = 0; i < size; i++) {
            fprintf(dump, "Cell [%d] = %d\n", i, type[i]);
        }
        fclose(dump);
        log_message("INFO", "type dump saved to type_dump.txt");
    }
}

// Изменено на int: возвращает 0 при успехе, -1 при ошибке
int run_interpreter(const char *code, int code_size, char *type, int type_size, int debug_mode) {
    int pc = 0;  
    int ptr = 0; 
    SimpleStack call_stack;
    call_stack.top = -1;

    log_message("INFO", "Interpreter execution started");

    while (code[pc] != '\0') {
        if (debug_mode && (code[pc] == '>' || code[pc] == '<' || code[pc] == '+' || 
                           code[pc] == '-' || code[pc] == '.' || code[pc] == ',' || 
                           code[pc] == '[' || code[pc] == ']')) {
            printf("[DEBUG] Шаг: %d | Команда: '%c' | Ячейка: %d | Значение: %d\n", pc, code[pc], ptr, type[ptr]);
            fflush(stdout);
            getchar();
        }

        switch (code[pc]) {
            case '>':
                ptr++;
                if (ptr >= type_size) {
                    printf("\nВыход за правую границу ленты\n");
                    log_message("ERROR", "type pointer out of bounds (right)");
                    return -1;
                }
                break;
            case '<':
                ptr--;
                if (ptr < 0) {
                    printf("\nВыход за левую границу ленты\n");
                    log_message("ERROR", "type pointer out of bounds (left)");
                    return -1;
                }
                break;
            case '+':
                type[ptr]++; break;
            case '-':
                type[ptr]--; break;
            case '.':
                putchar(type[ptr]); fflush(stdout); break;
            case ',':
                type[ptr] = getchar(); break;
            case '[':
                if (type[ptr] == 0) {
                    int open = 1;
                    while (open > 0) {
                        pc++;
                        if (code[pc] == '\0') {
                            log_message("ERROR", "Unexpected end of file inside loop");
                            return -1;
                        }
                        if (code[pc] == '[') open++;
                        if (code[pc] == ']') open--;
                    }
                } else {
                    call_stack.top++;
                    if (call_stack.top >= MAX_DEPTH) {
                        log_message("ERROR", "Stack overflow: loop depth exceeded");
                        return -1;
                    }
                    call_stack.data[call_stack.top] = pc;
                }
                break;
            case ']':
                if (call_stack.top < 0) {
                    log_message("ERROR", "Stack underflow: unmatched close bracket during runtime");
                    return -1;
                }
                if (type[ptr] != 0) {
                    pc = call_stack.data[call_stack.top];
                } else {
                    call_stack.top--;
                }
                break;
            default:
                break;
        }
        pc++;
    }
    log_message("INFO", "Interpreter execution finished successfully");
    return 0;
}
