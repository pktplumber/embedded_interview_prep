### Implement a fixed-size circular buffer in C.

Requirements:

Support the following operations:
- init(buffer, size)
- push(value)
- pop()
- is_empty()
- is_full()

The buffer must not overwrite existing data when full.

Assume the buffer will be used for UART RX data.

#### Follow up

Write it in C++
Make it interrupt-safe, thread-safe, and lock-free.
Allow overwrite mode when full.
