#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Staff
{
    char text[256];
    char name[128];
    int id;
    char level[14];
} Staff;

long get_size(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) return -1;
    fseek(f, 0L, SEEK_END);
    long sz = ftell(f);
    fclose(f);
    return sz;
}

void search_ID(){
    Staff user;
    int num;
    int flag = 1;  

    FILE *file = fopen("database.dat", "rb");
    if (file == NULL) {
        printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        return;
    }
    
    if (scanf("%d", &num) != 1) {
        printf("Ошибка ввода\n");
        fclose(file);
        return;
    }

    while (fread(&user, sizeof(Staff), 1, file)) {
        if (user.id == num){
            printf("%s %d %s\n", user.name, user.id, user.level);
            flag = 0;
            break;
        }
    }

    if (flag){
        printf("ERROR ID NOT FOUND\n");
    }

    fclose(file);
}

void compress() {
    FILE *file = fopen("database.dat", "rb");
    FILE *file_comp = fopen("database.rle", "wb");
    if (!file || !file_comp) {
        if (file) fclose(file);
        if (file_comp) fclose(file_comp);
        return;
    }

    unsigned char curr, prev;
    unsigned char count = 0;

    if (fread(&prev, 1, 1, file)) {
        count = 1;
        while (fread(&curr, 1, 1, file)) {
            if (curr == prev && count < 255) {
                count++;
            } else {
                fwrite(&count, 1, 1, file_comp);
                fwrite(&prev, 1, 1, file_comp);
                prev = curr;
                count = 1;
            }
        }
        fwrite(&count, 1, 1, file_comp);
        fwrite(&prev, 1, 1, file_comp);
    }
    fclose(file);
    fclose(file_comp);

    long sz_before = get_size("database.dat");
    long sz_after = get_size("database.rle");
    if (sz_before > 0) {
        double proc = (1.0 - (double)sz_after / sz_before) * 100.0;
        printf("Размер до: %ld байт, Размер после: %ld байт. Сжатие: %.2f%%\n", 
                sz_before, sz_after, proc);
    }
}

void decompress() {
    unsigned char count, val;
    FILE *in = fopen("database.rle", "rb");
    FILE *out = fopen("database1.dat", "wb");
    if (!in || !out) {
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    while (fread(&count, 1, 1, in)) {
        if (fread(&val, 1, 1, in)) {
            for (int i = 0; i < count; i++) {
                fwrite(&val, 1, 1, out);
            }
        }
    }
    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s staff.csv\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("In %s:%d Error opening file %s\n", __FILE__, __LINE__, argv[1]);
        exit(1);
    }

    FILE *file_w = fopen("database.dat", "wb");
    if (file_w == NULL) {
        fclose(file);
        exit(1);
    }

    Staff user;
    
    while (fgets(user.text, sizeof(user.text), file)) { 
        if (sscanf(user.text, "%[^;];%d;%s", user.name, &user.id, user.level) == 3) {
            printf("%s %d %s\n", user.name, user.id, user.level);
            fwrite(&user, sizeof(Staff), 1, file_w);
        }
    }

    fclose(file);
    fclose(file_w);

    search_ID();
    compress();
    decompress();

    return 0;
}
