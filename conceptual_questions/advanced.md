# Advanced Embedded Software Interview Questions

## DMA
### A peripheral writes data into memory using DMA, but sometimes the CPU reads old data.
#### Why does this happen?
#### What fixes are possible?
#### How do cache invalidation or memory barriers help?

## Review the code below:
```
volatile int flag = 0;

void ISR() {
    flag = 1;
}

int main() {
    while (!flag);
    process_data();
}
```

### Is this implementation always safe?
### What compiler optimizations could break it?
### What if the ISR fires before the loop begins?
### How would you redesign this for robustness?

## A thread needs to sleep until an ISR is triggered. How can you signal a thread to wake up once an ISR executes?

### Why is this code dangerous?
```
uint32_t *reg = (uint32_t*)0x40001000;
*reg |= (1 << 3);
```

## OS/RTOS
### What is a deadlock? How do you prevent them?
### What is a segmentation fault and what are some common causes? What happens in the OS during a segmentation fault?
### Name some common linux commands and their purposes.
### What is an OS signal? Can you name some linux OS signals and their purposes?
