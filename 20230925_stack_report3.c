#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef int element;
typedef struct {
    element data[MAX];
    int top;
} StackType;

void init_stack(StackType *s) {
    s->top = -1;
}

int is_empty(StackType *s) {
    return (s->top == -1);
}

void push(StackType *s, element item) {
    if (s->top >= MAX - 1) return;
    s->data[++(s->top)] = item;
}

element pop(StackType *s) {
    if (is_empty(s)) return 0;
    return s->data[(s->top)--];
}

element peek(StackType *s) {
    if (is_empty(s)) return 0;
    return s->data[s->top];
}

int prec(char op) {
    switch (op) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

int evalPostfix(char *postfix) {
    StackType s;
    init_stack(&s);
    int op1, op2;
    int len = strlen(postfix);
    char ch;

    for (int i = 0; i < len; i++) {
        ch = postfix[i];
        if (isdigit(ch)) {
            push(&s, ch - '0');
        } else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
                case '+': push(&s, op1 + op2); break;
                case '-': push(&s, op1 - op2); break;
                case '*': push(&s, op1 * op2); break;
                case '/': push(&s, op1 / op2); break;
            }
        }
    }
    return pop(&s);
}

int infixToPostfix(char *infix, char *postfix) {
    StackType s;
    init_stack(&s);
    int k = 0;
    char ch, top_op;

    for (int i = 0; i < strlen(infix); i++) {
        ch = infix[i];
        if (isdigit(ch)) {
            postfix[k++] = ch;
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!is_empty(&s) && (top_op = pop(&s)) != '(') {
                postfix[k++] = top_op;
            }
        } else {
            while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
                postfix[k++] = pop(&s);
            }
            push(&s, ch);
        }
    }
    while (!is_empty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';

    return evalPostfix(postfix);
}

int main(void) {
    char infix[MAX];
    char postfix[MAX];
    int result;

    printf("중위표기식 입력 : ");
    scanf("%s", infix);

    result = infixToPostfix(infix, postfix);

    printf("후위표기식 : %s\n", postfix);
    printf("후위표기식 계산 결과 : %d\n", result);

    return 0;
}
