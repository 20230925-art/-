#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void append(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int searchValue1(Node* head, int val) {
    Node* curr = head;
    int index = 1;

    while (curr != NULL) {
        if (curr->data == val) {
            return index;
        }
        curr = curr->next;
        index++;
    }
    return -1;
}

void searchValue2(Node* head, int val) {
    Node* curr = head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (curr->data == val) {
            printf("%d 탐색 성공!\n", val);
            
            if (prev != NULL) printf("앞 노드의 값: %d\n", prev->data);
            else printf("앞 노드가 없습니다.\n");

            if (curr->next != NULL) printf("뒤 노드의 값: %d\n", curr->next->data);
            else printf("뒤 노드가 없습니다.\n");
            
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("%d을(를) 찾을 수 없습니다.\n", val);
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);

    int val = 30;
    int pos = searchValue1(head, val);
    printf("%d의 위치는 %d번째\n", val, pos);

    printf("---------------------------\n");

    searchValue2(head, val);

    printf("---------------------------\n");

    freeList(head);

    return 0;
}
