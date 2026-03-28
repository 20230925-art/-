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
    s->data = (int *)realloc(s->data, s->capacity * sizeof(int));
    if (s->data == NULL) exit(1);
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

int main() {
    Stack s;
    char str[101];
    
    initStack(&s, 10);

    printf("문자열을 입력하세요: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
    }

    for (int i = 0; str[i] != '\0'; i++) {
        push(&s, str[i]);
    }

    printf("거꾸로 출력된 문자열: ");
    while (!isEmpty(&s)) {
        printf("%c", (char)pop(&s));
    }
    printf("\n");

    freeStack(&s);
    return 0;
}
