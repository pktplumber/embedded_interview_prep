# Basic Embedded Interview Question Answers

## Coding
#### What does the "volatile" keyword do and when would you use it?

"volatile" tells the compiler that whenever you access this variable, its value has to be loaded from memory, and that the compiler shouldn't assume anything about the value from previous stores/loads. 
Used for hardware registers, variables used in signal/interrupt handlers, occasionally multi-threaded code.

#### What does the "const" keyword do and when would you use it?

"const" indicates that a variable/object cannot change after initialization. In C++, it can be used for methods to indicate the object will be unchanged after the function call.

Used for constant values/configurations, C++ getters, hardware/address locations, function arguments that do not change, etc.

#### What does the "inline" keyword mean?

"inline" indicates that a function's contents should be "copied" directly into the call location instead of calling as a function.

Is a suggestion to the compiler.

Can reduce overhead of calling function, but rarely used since compiler will usually determine if a function can be inlined or not.

#### What does the "static" keyword do in C?

The "static" keyword is a storage specifier indicating that a variable/function should only be accessible by the translation unit it is defined in.

#### What does the "static" keyword do in C++?

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

#### What is a pointer in C and C++?

A pointer is a variable that points to another variables memory address

#### What is a reference in C++?

A reference is similar to a pointer, except it references a variable directly and cannot point to NULL.

#### What is the difference between using an inline function and a macro?

Inline indicates that a function can be copied to the call location. It is better for type safety, since it explicitly defines the return and argument types.

A macro simply copies text into the call/referenced location. It does not do any type checking.

#### What are the properties of an object-oriented programming language?

1. 
2. 
3. 
4. 

#### What is an atomic operation? Why are atomic operations useful?

An atomic operation is a single, indivisible unit of work, uninterruptible by other threads/processes. They are useful for multi-threaded applications, since one thread can modify a variable completely before another thread can read/modify it.

#### What is memory fragmentation? How do you avoid it?

Memory fragmentation is 

#### What are templates in C++? Why are they useful?

## Compiling
#### Explain the stages of compiling c/c++ code. What are the different stages?
#### What is the "preprocessor" and what does it do?

## Drivers/Protocols
#### Summarize SPI, UART, and I2C busses. How are they different?
#### Explain how the SPI protocol works in detail.
#### Explain how the UART protocol works in detail.
#### Explain how the I2C protocol works in detail.
#### Explain how the CAN protocol works in detail.

## Memory Management
#### What is a memory leak? How do you avoid it? Provide general techniques, C techniques, and C++ techniques.
#### Explain cache coherency and the different types?
#### In general, how do you design cache-friendly code?
#### What is "RAM"? What is it used for?
#### Why is it faster to read and write to/from a uint32_t (or uint64_t depending on the architecture) than a uint8_t or a uint16_t?
#### What does the linker script do?
#### What is the "stack"? What is it used for?
#### What is the "heap"? What is it used for?
#### In which memory section are static/global variables located in?

## Interrupts
#### How do interrupts work?
#### What are some common problems when dealing with interrupts?
#### What should you never do in an interrupt?

## OS/Systems Programming
#### What is the difference between a process and a thread?
#### What is a semaphore? What are the different types and their uses?
#### What is a mutex? When would use a mutex instead of a semaphore and vice versa?
#### Explain processor pipelines. What are the pros/cons of shorter and longer pipelines?

### RTOSes
#### What is priority inversion? Give an example.
#### How do you prevent priority inversion?
#### List some common scheduling algorithms. What are the differences between them?

### Networking/Communications
#### What is the difference between UDP and TCP? When would you use one over the other?

#### What is a memory leak?
#### When and why would you use the keyword "static"?
#### What is "re-entrancy" code. How do you ensure code is reentrant?

## Electronics
#### What are pull-up and pull-down resistors? What is the difference between them and when might you use them?
#### What is "Ohms Law"?

## Safety
#### What are some safe programming techniques you use?
#### What are some common software design techniques/features to ensure safety?
#### What is "RAMS". How do you design a system to maximize it? What are some common features?
