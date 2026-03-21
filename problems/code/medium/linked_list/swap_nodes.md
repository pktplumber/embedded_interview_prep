## Write a C function that swaps any two nodes by their index.

```
struct Node {
    int data;
    struct Node* next;
};

// x and y are the indices of the nodes to swap
void swapNodes(struct Node** head_ref, int x, int y);
```

### Write the swap function to swap the opposite nodes.
I.e. the nth node from the beginning and the nth from the end.

### Write a function to swap adjacent nodes in a singly-linked list
I.e. if input list is 
`1->2->3->4->5`
The output list would be
`2->1->4->3->5`