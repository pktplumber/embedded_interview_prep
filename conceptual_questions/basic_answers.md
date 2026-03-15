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
### What is the "stack"? What is it used for?
### What is the "heap"? What is it used for?
### In which memory section are static/global variables located in?

## Interrupts
### How do interrupts work?
### What are some common problems when dealing with interrupts?
### What should you never do in an interrupt?

## OS/Systems Programming
### What is the difference between a process and a thread?
A process is 

### What is a semaphore? What are the different types and their uses?
### What is a mutex? When would use a mutex instead of a semaphore and vice versa?
### Explain processor pipelines. What are the pros/cons of shorter and longer pipelines?
### What is a page fault?

### RTOSes
### What is priority inversion? Give an example.
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
