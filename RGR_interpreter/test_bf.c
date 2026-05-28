#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "func.h"

// 1. Тест валидации корректных скобок
static void test_check_data_correct(void **state) {
    (void) state;
    const char *good_code = "+++++[>+++++++<-].";
    int result = check_data(good_code);
    assert_int_equal(result, 1); 
}

// 2. Тест валидации неверного баланса (лишняя закрывающая скобка)
static void test_check_data_unmatched_close(void **state) {
    (void) state;
    const char *bad_code = "+++++>-<-]";
    int result = check_data(bad_code);
    assert_int_equal(result, 0); 
}

// 3. Тест валидации неверного баланса (незакрытая открывающая скобка)
static void test_check_data_unmatched_open(void **state) {
    (void) state;
    const char *bad_code = "+++++[>++++<-";
    int result = check_data(bad_code);
    assert_int_equal(result, 0); 
}

// 4. Тест функции ручной очистки/обнуления ленты (clear)
static void test_clear_tape(void **state) {
    (void) state;
    int size = 10;
    char *tape = (char*)malloc(size * sizeof(char));
    
    for(int i = 0; i < size; i++) {
        tape[i] = 55; 
    }
    
    clear(tape, size);
    
    for(int i = 0; i < size; i++) {
        assert_int_equal(tape[i], 0);
    }
    
    free(tape);
}

// 5. Тест успешного выполнения базовых команд интерпретатора (+ и -)
static void test_interpreter_success_simple(void **state) {
    (void) state;
    int tape_size = 10;
    char *tape = (char*)calloc(tape_size, sizeof(char));
    
    const char *code = "+++>++-"; 
    int result = run_interpreter(code, strlen(code), tape, tape_size, 0);
    
    assert_int_equal(result, 0); 
    assert_int_equal(tape[0], 3); 
    assert_int_equal(tape[1], 1); 
    
    free(tape);
}

// 6. Тест критической ошибки: Выход за левую границу ленты (< на нулевой позиции)
static void test_interpreter_error_left_bound(void **state) {
    (void) state;
    int tape_size = 5;
    char *tape = (char*)calloc(tape_size, sizeof(char));
    
    const char *code = "<+"; 
    int result = run_interpreter(code, strlen(code), tape, tape_size, 0);
    
    assert_int_equal(result, -1); 
    
    free(tape);
}

// 7. Тест критической ошибки: Выход за правую границу ленты (>)
static void test_interpreter_error_right_bound(void **state) {
    (void) state;
    int tape_size = 2;
    char *tape = (char*)calloc(tape_size, sizeof(char));
    
    const char *code = ">>>+"; 
    int result = run_interpreter(code, strlen(code), tape, tape_size, 0);
    
    assert_int_equal(result, -1); 
    
    free(tape);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_check_data_correct),
        cmocka_unit_test(test_check_data_unmatched_close),
        cmocka_unit_test(test_check_data_unmatched_open),
        cmocka_unit_test(test_clear_tape),
        cmocka_unit_test(test_interpreter_success_simple),
        cmocka_unit_test(test_interpreter_error_left_bound),
        cmocka_unit_test(test_interpreter_error_right_bound)
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
