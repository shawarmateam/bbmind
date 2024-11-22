#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(const char* filename) {
    FILE *file;
    char line[256];
    char *content = NULL;
    size_t total_length = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "\033[31mBBMIND001\033[0m: Unable to open file \"%s\".\n", filename);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        size_t line_length = strlen(line);

        char *new_content = realloc(content, total_length + line_length + 1);
        if (new_content == NULL) {
            perror("\033[31mBBMIND002\033[0m: Unable to allocate memory.");
            free(content);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        content = new_content;

        strcpy(content + total_length, line);
        total_length += line_length;
    }

    fclose(file);
    return content;
}

//void shiftRight(unsigned char* array, int size) {
//    for (int i = size - 1; i > 0; i--) array[i] = array[i - 1];array[0] = 0;
//}

void bbmind(char *string) {
    unsigned int stackmax = 100;
    unsigned int stacklen = 0;
    unsigned char stack[stacklen];
    unsigned char buff = 0;
    int i = 0;

    while (strlen(string)>i) {
        switch (string[i]) {
            case '+':
                buff++;
                printf("+ (%d)\n", buff);
                break;
            case '-':
                buff--;
                printf("- (%d)\n", buff);
                break;
            case '&':
                stacklen++;
                if (stacklen!=0) {
                    for (int j = stacklen - 1; j > 0; j--) stack[j] = stack[j - 1];
                }

                stack[0]=buff;
                buff=0;
                printf("& (%d)\n", stack[0]);
                break;
            case '^':
                stack[stacklen-1] = 0;
                stacklen--;
                printf("^\n");
                break;
            case '.':
                printf("(char):\n'%c'\n", (char)buff);
                break;
            case '~':
                buff = stack[buff];
                printf("~ (%d)\n", buff);
                printf("3~ (%d)\n", stacklen);
                //for (int j=0;j<stacklen;++j) printf("2~ (%s)\n", stack[j]);

                break;
            case '[':
                printf("[\n");
                break;
            case ']':
                printf("]\n");
                if (stack[0] == 0) break;
                while (string[i]!='[') i-=2;
                break;
        }i++;
    }
}

int main(int argv, char **argc) {
    if (argv <= 1) return 5;
    char *string = readFile(argc[1]);

    bbmind(string);
    return 0;
}
