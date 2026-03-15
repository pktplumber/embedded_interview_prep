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

## OS/RTOS
### What is a deadlock? How do you prevent them?
A deadlock is a state where two or more threads or processes are waiting for the same resource being held by the other effectively stalling the threads from executing permanently.

Example: 
1. Thread 1 locks mutex A for reading sensor data.
2. Thread 2 locks mutex B to receive a UART message that controls the sensor.
3. Thread 1 tries to unlock mutex B so it can send the sensor data over UART.
4. Thread 2 tries tries to unlock mutex A so it can configure the sensor.

Since Thread 1 doesn't unlock mutex A until it can lock mutex B, and thread 2 doesn't unlock mutex B until it can lock mutex A, both threads are at a standstill.

It can also happen if a process tries to lock a mutex twice if the OS doesn't provide recursive mutexes.

#### Fixes
- Always lock mutexes in the same order. E.g. both threads will always attempt to lock A then B
- Use timeouts on the mutex lock calls.
- Unlock as soon as you're done with the resource. This might mean you need to copy the resource's data instead of referencing it

### What is a segmentation fault and what are some common causes? What happens in the OS during a segmentation fault?
A segmentation fault is a runtime error that occurs when a program tries to access memory that it is not allowed to access.

For example:
- Dereferencing a null pointer
- Reading/writing to memory allocated to another process (linux).
- Use after free
- Stack overflow, i.e. when a process overruns its own allocated program stack.
- Writing to read-only memory. E.g. modifying a string literal

#### What happens in the OS during a seg fault (advanced)
Details are typically OS-dependent, but on CPUs with a MMU (memory management unit), the CPU is checks each address being accessed against the page table.

If the page is not mapped, is read-only/protected, or outside the processes allowed range, it will raise a page fault (hardware trap). The OS will inspect the fault and raise a seg fault signal which kills the process.

### Name some common linux commands and their purposes.
### What is an OS signal? Can you name some linux OS signals and their purposes?
