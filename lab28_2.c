#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Помилка виділення пам'яті!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Черга порожня!\n");
        exit(1);
    }
    Node* temp = q->front;
    int dequeuedValue = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return dequeuedValue;
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Черга порожня.\n");
        return;
    }
    
    printf("Вміст черги: ");
    Node* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void splitQueue(Queue* original, Queue* evenQueue, Queue* oddQueue) {
    int position = 1;
    while (!isEmpty(original)) {
        int value = dequeue(original);
        
        if (position % 2 == 0) {
            enqueue(evenQueue, value);
        } else {
            enqueue(oddQueue, value);
        }
        
        position++;
    }
}

int main() {
    system("chcp 65001");
    Queue originalQueue, evenQueue, oddQueue;
    initQueue(&originalQueue);
    initQueue(&evenQueue);
    initQueue(&oddQueue);
    
    int n, number;
    
    printf("Введіть кількість елементів у черзі: ");
    scanf("%d", &n);
    
    printf("Введіть %d чисел для черги:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &number);
        enqueue(&originalQueue, number);
    }
    
    printf("\nПочаткова черга:\n");
    printQueue(&originalQueue);

    splitQueue(&originalQueue, &evenQueue, &oddQueue);
    
    printf("\nЧерга з елементами на парних позиціях:\n");
    printQueue(&evenQueue);
    
    printf("\nЧерга з елементами на непарних позиціях:\n");
    printQueue(&oddQueue);

    while (!isEmpty(&evenQueue)) {
        dequeue(&evenQueue);
    }
    while (!isEmpty(&oddQueue)) {
        dequeue(&oddQueue);
    }
    
    return 0;
}