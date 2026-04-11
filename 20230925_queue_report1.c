#include <stdio.h>
#include <stdbool.h>

#define SIZE 30

typedef struct {
    int data[SIZE];
    int front;
    int rear;
} LinearQueue;

void initQueue(LinearQueue *q) {
    q->front = 0;
    q->rear = -1;
}

bool isEmpty(LinearQueue *q) {
    return q->front > q->rear;
}

bool isFull(LinearQueue *q) {
    return q->rear == SIZE - 1;
}

bool enqueue(LinearQueue *q, int value) {
    if (isFull(q)) {
        printf("[오류] 큐가 가득 찼습니다.\n");
        return false;
    }
    q->data[++(q->rear)] = value;
    return true;
}

int dequeue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("[오류] 큐가 비어 있습니다.\n");
        return -1;
    }
    int value = q->data[q->front++];
    if (isEmpty(q)) {
        initQueue(q);
    }
    return value;
}

void printQueue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }
    printf("큐 데이터: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() {
    LinearQueue q;
    initQueue(&q);
    int choice, value;

    while (1) {
        printf("\n1.삽입 2.삭제 3.출력 4.종료: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            printf("데이터 입력: ");
            scanf("%d", &value);
            enqueue(&q, value);
        } else if (choice == 2) {
            value = dequeue(&q);
            if (value != -1) printf("삭제된 값: %d\n", value);
        } else if (choice == 3) {
            printQueue(&q);
        } else if (choice == 4) {
            break;
        } else {
            printf("잘못된 입력입니다.\n");
        }
    }
    return 0;
}
