#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    char name[30];
    char phone[20];
    struct Contact* next;
} Contact;

void addContact(Contact** head, char* name, char* phone) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;

    if (*head == NULL) {
        *head = newContact;
        return;
    }

    Contact* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newContact;
}

void searchContact(Contact* head, char* name) {
    Contact* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            printf("탐색 결과 - 이름: %s, 전화번호: %s\n", curr->name, curr->phone);
            return;
        }
        curr = curr->next;
    }
    printf("%s 님을 찾을 수 없습니다.\n", name);
}

void deleteContact(Contact** head, char* name) {
    Contact *curr = *head, *prev = NULL;

    if (curr != NULL && strcmp(curr->name, name) == 0) {
        *head = curr->next;
        free(curr);
        printf("%s 님의 연락처가 삭제되었습니다.\n", name);
        return;
    }

    while (curr != NULL && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("삭제 실패: %s 님을 찾을 수 없습니다.\n", name);
        return;
    }

    prev->next = curr->next;
    free(curr);
    printf("%s 님의 연락처가 삭제되었습니다.\n", name);
}

void displayAll(Contact* head) {
    Contact* curr = head;
    printf("\n=== 현재 전화번호부 목록 ===\n");
    while (curr != NULL) {
        printf("이름: %s | 번호: %s\n", curr->name, curr->phone);
        curr = curr->next;
    }
    printf("===========================\n");
}

void freeAll(Contact* head) {
    Contact* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Contact* head = NULL;

    addContact(&head, "Hong", "010-1234-5678");
    addContact(&head, "Kim", "010-9876-5432");
    addContact(&head, "Lee", "010-5555-4444");

    displayAll(head);

    searchContact(head, "Kim");

    deleteContact(&head, "Kim");
    displayAll(head);

    freeAll(head);

    return 0;
}
