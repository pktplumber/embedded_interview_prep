#include <stdio.h>

#define MAX_SIZE 10  // maximum elements in the queue

typedef struct {
    int data;
    int priority;
} Node;

typedef struct {
    Node queue[MAX_SIZE];
    int size;
} PriorityQueue;

// Initialize the queue
void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

// Insert an element into the priority queue
void push(PriorityQueue* pq, int data, int priority) {
    if (pq->size == MAX_SIZE) {
        printf("Queue full!\n");
        return;
    }

    int i = pq->size - 1;

    // Shift elements with lower priority to the right
    while (i >= 0 && pq->queue[i].priority > priority) {
        pq->queue[i + 1] = pq->queue[i];
        i--;
    }

    // Insert new element
    pq->queue[i + 1].data = data;
    pq->queue[i + 1].priority = priority;
    pq->size++;
}

// Remove the element with highest priority
Node pop(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Queue empty!\n");
        Node empty = {-1, -1};
        return empty;
    }

    // Highest priority element is at the front
    Node top = pq->queue[0];

    // Shift remaining elements left
    for (int i = 1; i < pq->size; i++) {
        pq->queue[i - 1] = pq->queue[i];
    }

    pq->size--;
    return top;
}

// Display the queue
void display(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Queue empty!\n");
        return;
    }

    printf("Priority Queue: ");
    for (int i = 0; i < pq->size; i++) {
        printf("(%d, %d) ", pq->queue[i].data, pq->queue[i].priority);
    }
    printf("\n");
}

int main() {
    PriorityQueue pq;
    initQueue(&pq);

    push(&pq, 10, 2);
    push(&pq, 20, 1);
    push(&pq, 30, 3);

    display(&pq);

    Node n = pop(&pq);
    printf("Popped: (%d, %d)\n", n.data, n.priority);

    display(&pq);

    return 0;
}