#include "func.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <имя_файла.bf> [--debug]\n", argv[0]);
        return 1;
    }

    int debug_mode = 0;
    if (argc > 2 && strcmp(argv[2], "--debug") == 0) {
        debug_mode = 1;
    }

    int code_size = 0;
    char *code = read_file(argv[1], &code_size);
    if (code == NULL) {
        return 1;
    }

    
    if (check_data(code) == 0) {
        free(code);
        return 1;
    }

    int type_size = 30000;
    char *type = (char*)malloc(type_size * sizeof(char));
    if (type == NULL) {
        printf("Err: Ошибка выделения памяти под ленту\n");
        free(code);
        return 1;
    }
    
    clear(type, type_size);


    run_interpreter(code, code_size, type, type_size, debug_mode);


    save_to_file(type, 5);


    free(code);
    free(type);

    printf("\n");
    return 0;
}
