#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
    char documentName[50];
    int numPages;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;

void initQueue(PrintQueue *q) {
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(PrintQueue *q) {
    return q->front == q->rear;
}

bool isFull(PrintQueue *q) {
    return (q->rear + 1) % SIZE == q->front;
}

bool enqueue(PrintQueue *q, char *documentName, int numPages) {
    if (numPages > 50) {
        printf("거부: 50장을 초과하는 문서입니다.\n");
        return false;
    }

    if (isFull(q)) {
        printf("대기열이 가득 찼습니다.\n");
        return false;
    }

    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;

    printf("작업 '%s' (%d 페이지) 추가됨\n", documentName, numPages);
    return true;
}

PrintJob dequeue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        PrintJob empty = {"", 0};
        return empty;
    }

    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

void cancelJob(PrintQueue *q, char *name) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    int i = q->front;
    int found = -1;

    while (i != q->rear) {
        if (strcmp(q->queue[i].documentName, name) == 0) {
            found = i;
            break;
        }
        i = (i + 1) % SIZE;
    }

    if (found == -1) {
        printf("해당 문서가 없습니다.\n");
        return;
    }

    while (found != q->rear) {
        int next = (found + 1) % SIZE;
        q->queue[found] = q->queue[next];
        found = next;
    }

    q->rear = (q->rear - 1 + SIZE) % SIZE;

    printf("인쇄 취소 완료\n");
}

void clearQueue(PrintQueue *q) {
    q->front = 0;
    q->rear = 0;
    printf("대기열 초기화\n");
}

void printQueue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    printf("현재 대기열:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("- %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (true) {
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 대기열 출력\n4. 인쇄 취소\n5. 전체 초기화\n0. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("문서 이름: ");
                scanf("%s", documentName);
                printf("페이지 수: ");
                scanf("%d", &numPages);
                enqueue(&q, documentName, numPages);
                break;

            case 2: {
                PrintJob job = dequeue(&q);
                if (strlen(job.documentName) > 0) {
                    printf("출력 중: %s (%d 페이지)\n", job.documentName, job.numPages);
                }
                break;
            }

            case 3:
                printQueue(&q);
                break;

            case 4:
                printf("취소할 문서 이름: ");
                scanf("%s", documentName);
                cancelJob(&q, documentName);
                break;

            case 5:
                clearQueue(&q);
                break;

            case 0:
                printf("종료\n");
                return 0;

            default:
                printf("잘못된 입력\n");
        }
    }
}
