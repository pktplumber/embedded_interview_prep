# Basic Embedded Interview Question Answers

## Coding
### What does the "volatile" keyword do and when would you use it?

"volatile" tells the compiler that whenever you access this variable, its value has to be loaded from memory, and that the compiler shouldn't assume anything about the value from previous stores/loads. 
Used for hardware registers, variables used in signal/interrupt handlers, occasionally multi-threaded code.

### What does the "const" keyword do and when would you use it?

"const" indicates that a variable/object cannot change after initialization. In C++, it can be used for methods to indicate the object will be unchanged after the function call.

Used for constant values/configurations, C++ getters, hardware/address locations, function arguments that do not change, etc.

### What does the "inline" keyword mean?

"inline" indicates that a function's contents should be "copied" directly into the call location instead of calling as a function.

Is a suggestion to the compiler.

Can reduce overhead of calling function, but rarely used since compiler will usually determine if a function can be inlined or not.

### What does the "static" keyword do in C?

The "static" keyword is a storage specifier indicating that a variable/function should only be accessible by the translation unit it is defined in.

### What does the "static" keyword do in C++?

Same as above, but can also indicate that a variable is the same for all instances of a class. I.e.:

class C
{
    public:
        void set_v(int v) { _v = v; }

        static int get_v() { return _v; }

    private:
        static int _v;  // Same for all instances of "C", since its declared static
}

Can specify a class method.

### What is a pointer in C and C++?

A pointer is a variable that points to another variables memory address

### What is a reference in C++?

A reference is similar to a pointer, except it references a variable directly and cannot point to NULL.

### What is the difference between using an inline function and a macro?

Inline indicates that a function can be copied to the call location. It is better for type safety, since it explicitly defines the return and argument types.

A macro simply copies text into the call/referenced location. It does not do any type checking.

### What are the 4 main properties of an object-oriented programming language? Explain each one.

1. **Encapsulation**: Data/variables are bundled into single components/classes while restricting direct access to details/logic involving that data. In C++, this is achieved via the `public`, `private`, and `protected` keywords.
2. **Inheritance**: The ability for classes to share common properties and behavior of other classes (the base class). This enables code reuse and the ability to extend functionality. 
3. **Polymorphism**: "many forms". It allows the same function name/operator/interface to perform different actions depending on the context or object that uses it. Mention `virtual` methods, the base class implements a common interface for different types of behavior. 
4. **Abstraction**: The concept of hiding implementation details and showing only the essential features/interface to the user. Focuses on what an object does, not how it does it.

### What is the difference between static and dynamic polymorphism. Give an example of each.

**Static polymorphism** is when a function call is resolved at compile time. It is achieved via *function overloading* and *operator overloading*. It can also be achieved via the CRTP pattern.
```
class Example
{
    public:
        int add(const int a, const int b) { return a + b; }
        double add(const double a, const double b) { return a + b; }
};
```

**Dynamic polymorphism** is when a function call is resolved at runtime. It is achieved via *function overriding* and *virtual methods*. 
```
class Base
{
    public:
        // Virtual
        virtual int foo() { return 1; }

        // pure virtual
        virtual int bar() = 0;
};

class Derived
{
    public:
        int foo() override { return 10; }

        // pure virtual
        int bar() override { return 99; };
};
```

### What is an atomic operation? Why are atomic operations useful?

An atomic operation is a single, indivisible unit of work, uninterruptible by other threads/processes. They are useful for multi-threaded applications, since one thread can modify a variable completely before another thread can read/modify it.

### What is memory fragmentation? How do you avoid it?

Memory fragmentation is 

### What are templates in C++? Why are they useful?

Templates enable a type of static/compile-time polymorphism where the template type is used within the object instance itself. This allows programmers to reuse the same class with different underlying types.

For example, `std::vector<T>` is a container class that can store many different types of classes/types such as `std::vector<uint8_t>`, `std::vector<int>`, `std::vector<CustomClass>`, etc.

### What is the difference between C and C++? When would you use C over C++ and vice versa?

C is purely procedural and C++ is object-oriented (could also be procedural). C has limited abstraction features while C++ has strong abstraction features such as classes, encapsulation, access modifiers (`public` and `private`), etc.. The C standard library is smaller/simpler and required manual memory management. The C++ standard library offers many more features and can support manual + some safer memory management options like smart pointers.

C is better suited for code that requires maximum control of memory management and minimal abstraction. Linux kernel drivers cannot be written in C++, so C is oftern the best choice for kernal drivers.

C++ is better suited for large, complex systems and when you want to benefit from code re-use and abstraction.

### What is the difference between python and C/C++?
Python is an interpreted language and C/C++ are both compiled languages. Python is a program build with C. Python syntax and type checking is done at runtime. C/C++ syntax and type checking are done at compile time.

## Compiling
### Explain the stages of compiling c/c++ code. What are the different stages?
1. Preprocessor: Processes all lines beginning with `#`. `#define` performs a text substitution of all references to the macro. `#include` inserts the contents of the referenced header file. Comments are removed.
2. Compiling: Checks syntax and converts preprocessed code into object code. This includes: syntax checking, type checking, conversion of text code to object/machine code, and sometimes optimization.
3. Linking: Combines object files to form one executable.

## Drivers/Protocols
### Summarize SPI, UART, and I2C busses. How are they different?
- SPI - 4 signals with master/slave protocol: CLK, DATA, MOSI, MISO. Useful for high data rate and short distance communication 
- UART - 2 signals: data out and data in. Configurable clock speed, stop/start bits, parity, and data length. Limited data rates
- I2C - Communication by addressing. 2 signals: clock and data. Each peripheral has a unique address. Master indicates the address in the data signal 
### Explain how the SPI protocol works in detail.
### Explain how the UART protocol works in detail.
### Explain how the I2C protocol works in detail.
### Explain how the CAN protocol works in detail.

## Memory Management
### What is a memory leak? How do you avoid it? Provide general techniques, C techniques, and C++ techniques.
A memory leak occurs when memory is dynamically allocated but not returned after use. This can occur in memory pools or with malloc/new.

Use statically allocated buffers, user memory profilers, etc.

In C, always call "free" at the end of the function where the data is used if possible.

In C++, use smart pointers. 

### What is the CPU cache. Explain cache coherency and the different types?
The CPU cache is a memory unit that allows quicker access than standard CPU memory. There are L1, L2, and L3 cache levels each with larger sizes. Data that is frequently accessed is more likely to exist in the cache.

Temporal coherency: data that is accessed frequently is more likely to exist in the cache.

Spacial coherency: data that is nearby (i.e. contiguous memory) is more likely to be in the cache.

### In general, how do you design cache-friendly code?
### What is "RAM"? What is it used for?
### Why is it faster to read and write to/from a uint32_t (or uint64_t depending on the architecture) than a uint8_t or a uint16_t?
Many CPU addresses/registers are 32 or 64 bits in size, so they can be accessed directly. Data types that do not align with the register size require extra instructions to access.

### What does the linker script do?
The linker script:
- Defines memory regions like .text for code, .data for initialized vars, .bss for uninitialized data, etc.
- Defines the different types of memory sizes and start address like the stack, RAM, and head
- Sets the program entry point
- It can also create custom symbols

### What is the "stack"? What is it used for?
The stack is a data structure used to store information related to the flow of the program such as the function calls/addresses, stack-based variables, function arguments, etc.. The stack is used to maintain the code's/programs order of execution. It uses the stack-pointer to do this

### What is the "heap"? What is it used for?
The heap is a block of memory that can be allocated and used at run-time.

### In which memory section are static/global variables located in?
In the .data segment

### In which memory are const variables/data located in?
In the .rom (read-only memory) section

## Interrupts
### How do interrupts work?
Interrupts pause the current flow of execution to run different code, effectively "interrupting" the program. There can be hardware or software-based interrupts. Hardware interrupts are triggered by an external signal, software interrupts are triggered by instructions/the OS.

- Interrupts are organized in a vector table that defines their handlers, priority etc.
- The processor maps the interrupt signals to a specific function call
- When the processor detects an interrupt signal, it saves the current program context (program counter, registers) then looks up and calls the interrupt handler function
- If multiple interrupts occur at the same time, the processor will determine which one has the highest priority and call that one first.

### What are some common problems when dealing with interrupts?
- Priority handling/nested interrupts: Lower priority interrupts can get delayed
- Race conditions: without proper synchronization, shared resources could lead to data corruption if accessed by multiple interrupts
- Timing/latency: Delay between interrupt signal and triggering the handler can be an issue
- Interrupting important processes: An interrupt triggering while a task with a hard-realtime deadline is executing, the task could be interrupted for too long, delaying the task execution

### What should you never do in an interrupt?
- Loop/remain in the interrupt for too long. Interupt handlers should be simple. This might include:
  - Using floating point operations
  - Looping for too long
  - Allocating dynamic memory
  - Infinite loops
- Accessing mutex/locks should be avoided
  - If a task has locked a mutex, and an ISR attempts to unlock, it will block forever if not configured correctly
- Blocking OS calls

### What are some techniques for accessing shared data in an interrupt?
1. Disable interrupts at the start of the handler, re-enable at end
2. Use atomic operations
3. Use lock-free data structures (ring-buffer)
4. Defer work outside of the ISR
5. Can use semaphore, but only call the `give` method
6. Some RTOSes support syncronization calls (i.e. FreeRTOS's xQueueSendFromISR func)

## OS/Systems Programming
### What is the difference between a process and a thread?
A process is a unit of execution that has its own memory/address space called "virtual memory". Processes can be spawned with the `fork` call on linux.

Threads are execution units that exist in the same address space. 

### What is a semaphore? What are the different types and their uses?
A semphore is an OS synchronization primitive used to control access to shared resources or coordinate execution between threads. It can also be used as a thread-safe signal between threads. There is the:
- Binary semaphore: Used for signalling between contexts.
- Counting semaphore: Access to and counting of limited resources such as memory buffers

### What is a mutex? When would use a mutex instead of a semaphore and vice versa?
A mutex is effectively a "lock" for a resource shared between threads. When a thread accesses a shared resource, it will lock the mutex until it is done, then unlock it. If the mutex is already locked, it will block until the resource is free or until a timeout.

You would typically use a mutex to lock access to a shared resource and use a semaphore to signal or count resources.

### Explain processor pipelines. What are the pros/cons of shorter and longer pipelines?
### What is a page fault?
Interrupt raised by the memory management unit to indicate an invalid memory access error.

In systems with virtual memory, memory is divided into chunks called "pages" that get loaded into RAM.
1. A program tries to access a memory address that is not loaded into RAM or is invalid. Some common causes include:
 - Dereferencing a NULL pointer
 - Stack overflow into an unmapped region
 - Writing to read-only memory
2. The MMU triggers a Page Fault Exception interrupt
3. The OS will attempt to resolve the error

### How do embedded systems without an MMU handle memory errors?
Many processors have a memory protection unit (MPU) that allows the operating system to define memory regions. Access violations trigger a harward fault handler. Also, compilers can insert known values ("canaries") on the stack before function return addressess. Before returning, the code checks if the canary has been modified.

Hardware exceptions (hard fault, bus fault, memory fault) are triggered by:
- Invalid memory access 
- Misaligned access
- Access to protected regions 

### RTOSes
### What is priority inversion? Give an example.
Priority inversion is a scenario where a lower priority task claimed a resource (with a mutex) which a higher priority task needs to access, so the higher priority task is blocked by the lower priority task effectively inverting their priorities.
1. 3 Tasks. A = highest, B = medium, C = lowest
2. A and C need to access a shared resource which is locked with a mutex.
3. C is running, locks the mutex, then gets interrupted by B.
4. Task C is preempted by Task B.
5. Task A cannot run until Task B and C are complete, effectively lowering A's priority

### How do you prevent priority inversion?


### List some common scheduling algorithms. What are the differences between them?

### What is a memory leak?
### When and why would you use the keyword "static"?
### What is "re-entrant" code. How do you ensure code is reentrant?

## Electronics
### What are pull-up and pull-down resistors? What is the difference between them and when might you use them?
### What is "Ohms Law"?

## Safety
### What are some safe programming techniques you use?
### What are some common software design techniques/features to ensure safety?
### What is "RAMS". How do you design a system to maximize it? What are some common features?
