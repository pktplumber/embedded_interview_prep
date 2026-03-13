# Advanced Embedded Software Interview Questions

## DMA
### A peripheral writes data into memory using DMA, but sometimes the CPU reads old data.
#### Why does this happen?
The CPU and DMA see different versions of memory. Typical scenario:
1. The CPU writes data to a buffer.
2. That data sits in the CPU cache, not yet written back to RAM.
3. The DMA device reads the buffer from RAM.
4. RAM still contains the old data, so the DMA reads stale values.

The opposite can happen too:
1. DMA writes new data to RAM.
2. CPU reads the buffer, but its cache still contains old cached data.

#### What fixes are possible?
1. Flush cache before reading so the data reaches RAM.
2. Invalidate cache after DMA write
3. Use a memory barrier (fence) to enforce ordering constraints on memory operations

#### How do cache invalidation or memory barriers help?
Cache invalidation forces the CPU to discard the cached copy or memory, so the next read must be from main memory. Since DMA interacts directly with RAM and not the CPU cache, both the CPU and DMA driver will be reading the same memory.
Memory barriers will ensure that read/writes and other DMA operations happen in the correct order.

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
No. The following are possible issues:
1. Busy-wait race conditions
2. Compiler optimization assumptions
3. Interrupt timing edge cases
4. Non-atomic access (on some MCUs)
### What compiler optimizations could break it?
Loop invariant code motion, the compiler could move the read outside the loop to `if (!flag) while(1)`
Since flag is not atomic, there could be a read mid-write
Busy waiting is inefficient.
### What if the ISR fires before the loop begins?
If the flag is initialized to 0 after the interrupt is triggered, it will not be detected.
### How would you redesign this for robustness?
```
#include <stdatomic.h>

atomic_int flag = 0;

void ISR() {
    atomic_store(&flag, 1);
}

int main() {
    while (!atomic_load(&flag))
    {
        // sleep
    }
    process_data();
}
```

## A thread needs to sleep until an ISR is triggered. How can you signal a thread to wake up once an ISR executes?

You can use a binary_semaphore as a signal.

```
sem_t my_semaphore;

void thread_func(void)
{
    while (1)
    {
        semaphore_take(&my_semaphore, DELAY_MS);
    }
}

void ISR_handler(void)
{
    semaphore_give(&my_semaphore);
}
```

Note: this is OS-dependent. Only works on OSes/systems where ISRs can safely give a semaphore.

Can also use a message queue or event flag.

### Why is this code dangerous?
```
uint32_t *reg = (uint32_t*)0x40001000;
*reg |= (1 << 3);
```

#### Answer
This code is dangerous because of how it is compiled.
`*reg |= (1 << 3)` is compiled as:
1. Read register value
2. OR with (1 << 3)
3. Write result back
Some bits might be cleared when read and writing back the value could re-trigger hardware events which might be an unintended consequence.
Also, `*reg` is not declared volatile, so the compiler might compile it away.

The correct implementation might be:
```
uint32_t val = *reg;
val &= ~(MASK);
val |= (new_bits);
*reg = val;
```

