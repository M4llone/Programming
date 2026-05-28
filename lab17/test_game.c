#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "src/game.h"

static void test_field_init(void **state) {
    (void) state;
    
    field **units = (field**)malloc(4 * sizeof(field*));
    for(int i = 0; i < 4; i++) {
        units[i] = (field*)malloc(sizeof(field*));
    }
    
    field_init(units);
    
    int num = 0;
    int empty = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(strcmp(units[i][j].unit, "  \0") == 0) {
                empty++;
            } else if(atoi(units[i][j].unit) >= 1 && atoi(units[i][j].unit) <= 15) {
                num++;
            }
        }
    }
    assert_int_equal(empty, 1);
    assert_int_equal(num, 15);
    

    for(int i = 0; i < 4; i++) {
        free(units[i]);
    }
    free(units);
}

static void test_check_win_w(void **state) {
    (void) state;
    
    field **units = (field**)malloc(4 * sizeof(field*));
    for(int i = 0; i < 4; i++) {
        units[i] = (field*)malloc(sizeof(field*));
    }
    
    int num = 1;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(num <= 15) {
                sprintf(units[i][j].unit, "%d", num);
                num++;
            } else {
                strcpy(units[i][j].unit, "  \0");
            }
        }
    }
    
    int result = check_win(units);
    assert_int_equal(result, 1);
    

    for(int i = 0; i < 4; i++) {
        free(units[i]);
    }
    free(units);
}

static void test_check_win_l(void **state) {
    (void) state;
    
    field **units = (field**)malloc(4 * sizeof(field*));
    for(int i = 0; i < 4; i++) {
        units[i] = (field*)malloc(sizeof(field*));
    }
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            strcpy(units[i][j].unit, "  \0");
        }
    }
    
    strcpy(units[0][0].unit, "5\0");
    strcpy(units[0][1].unit, "1\0");
    
    int result = check_win(units);
    assert_int_equal(result, 0);

    for(int i = 0; i < 4; i++) {
        free(units[i]);
    }
    free(units);

}   


static void test_swap(void **state) {
    (void) state;
    
    field **units = (field**)malloc(4 * sizeof(field*));
    for(int i = 0; i < 4; i++) {
        units[i] = (field*)malloc(sizeof(field*));
    }
    
    int num = 1;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(num == 16) {
                strcpy(units[i][j].unit, "  \0");
            } else {
                sprintf(units[i][j].unit, "%d", num);
                num++;
            }
        }
    }
    
    
    assert_string_equal(units[3][3].unit, "  \0");
    

    for(int i = 0; i < 4; i++) {
        free(units[i]);
    }
    free(units);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_field_init),
        cmocka_unit_test(test_check_win_l),
        cmocka_unit_test(test_check_win_w),
        cmocka_unit_test(test_swap)
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}