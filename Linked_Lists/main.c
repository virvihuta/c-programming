#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* n = malloc(sizeof(Node));
    n->data = value;
    n->next = NULL;
    return n;
}

void append(Node** head, int value) {
    Node* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* cur = *head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new_node;
}

void prepend(Node** head, int value) {
    Node* new_node = create_node(value);
    new_node->next = *head;
    *head = new_node;
}

int insert_at(Node** head, int index, int value) {
    if (index < 0) return 0;
    if (index == 0) {
        prepend(head, value);
        return 1;
    }
    Node* cur = *head;
    for (int i = 0; i < index - 1 && cur != NULL; i++)
        cur = cur->next;
    if (cur == NULL) return 0;
    Node* new_node = create_node(value);
    new_node->next = cur->next;
    cur->next = new_node;
    return 1;
}

int delete_at(Node** head, int index) {
    if (*head == NULL || index < 0) return 0;
    Node* cur = *head;
    if (index == 0) {
        *head = cur->next;
        free(cur);
        return 1;
    }
    for (int i = 0; i < index - 1 && cur != NULL; i++)
        cur = cur->next;
    if (cur == NULL || cur->next == NULL) return 0;
    Node* temp = cur->next;
    cur->next = temp->next;
    free(temp);
    return 1;
}

int search(Node* head, int value) {
    int index = 0;
    Node* cur = head;
    while (cur != NULL) {
        if (cur->data == value) return index;
        cur = cur->next;
        index++;
    }
    return -1;
}

void print_list(Node* head) {
    Node* cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

void free_list(Node* head) {
    Node* cur;
    while (head != NULL) {
        cur = head;
        head = head->next;
        free(cur);
    }
}

int main() {
    Node* list = NULL;

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);

    prepend(&list, 5);

    insert_at(&list, 2, 99);

    print_list(list);

    printf("Search 20: %d\n", search(list, 20));

    delete_at(&list, 1);

    print_list(list);

    free_list(list);
    return 0;
}

