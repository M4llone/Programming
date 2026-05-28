#include "func.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // Проверяем, передал ли пользователь файл с кодом
    if (argc < 2) {
        printf("Использование: %s <имя_файла.bf> [--debug]\n", argv[0]);
        return 1;
    }

    // Режим отладки включается, если вторым аргументом передан флаг --debug
    int debug_mode = 0;
    if (argc > 2 && strcmp(argv[2], "--debug") == 0) {
        debug_mode = 1;
    }

    int code_size = 0;
    // 1. Считываем код напрямую из файла (например, text.bf)
    char *code = read_file(argv[1], &code_size);
    if (code == NULL) {
        return 1;
    }

    // 2. Проверяем баланс скобок
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

    // 4. Запуск интерпретатора
    run_interpreter(code, code_size, type, type_size, debug_mode);

    // 5. Сохранение первых 20 ячеек ленты
    save_to_file(type, 5);

    // Освобождаем ресурсы
    free(code);
    free(type);

    printf("\n");
    return 0;
}
