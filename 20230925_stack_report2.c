#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

void initStack(Stack *s, int size) {
    s->data = (int *)malloc(size * sizeof(int));
    if (s->data == NULL) exit(1);
    s->top = -1;
    s->capacity = size;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void expandStack(Stack *s) {
    s->capacity += 10;
    int *newData = (int *)realloc(s->data, s->capacity * sizeof(int));
    if (newData == NULL) exit(1);
    s->data = newData;
}

void push(Stack *s, int value) {
    if (s->top == s->capacity - 1) expandStack(s);
    s->data[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) return -1;
    return s->data[(s->top)--];
}

void freeStack(Stack *s) {
    free(s->data);
}

int checkMatching(char *str) {
    Stack s;
    initStack(&s, 10);
    int valid = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&s)) {
                valid = 0;
                break;
            }
            char openCh = (char)pop(&s);
            if ((ch == ')' && openCh != '(') ||
                (ch == '}' && openCh != '{') ||
                (ch == ']' && openCh != '[')) {
                valid = 0;
                break;
            }
        }
    }

    if (!isEmpty(&s)) valid = 0;

    freeStack(&s);
    return valid;
}

int main() {
    char str[101];

    printf("문자열을 입력하세요: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
    }

    if (checkMatching(str)) {
        printf("유효한 괄호\n");
    } else {
        printf("유효하지 않은 괄호\n");
    }

    return 0;
}
