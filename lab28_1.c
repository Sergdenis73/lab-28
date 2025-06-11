#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

bool isEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Помилка виділення пам'яті!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Стек порожній!\n");
        exit(1);
    }
    Node* temp = s->top;
    int poppedValue = temp->data;
    s->top = s->top->next;
    free(temp);
    return poppedValue;
}

void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Стек порожній.\n");
        return;
    }
    
    printf("Вміст стеку (зверху вниз): ");
    Node* current = s->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void removeUntilNegative(Stack* s) {
    Stack tempStack;
    initStack(&tempStack);

    while (!isEmpty(s)) {
        int value = pop(s);
        if (value < 0) {
            push(s, value); 
            break;
        }
        push(&tempStack, value);
    }

    while (!isEmpty(&tempStack)) {
        pop(&tempStack);
    }
}

int main() {
    system("chcp 65001");
    Stack s;
    initStack(&s);
    int number;
    
    printf("Введіть 14 чисел:\n");

    for (int i = 0; i < 14; i++) {
        scanf("%d", &number);
        push(&s, number);
    }
    
    printf("\nСтек до обробки:\n");
    printStack(&s);

    removeUntilNegative(&s);
    
    printf("\nСтек після видалення елементів до першого від'ємного:\n");
    printStack(&s);

    while (!isEmpty(&s)) {
        pop(&s);
    }
    
    return 0;
}