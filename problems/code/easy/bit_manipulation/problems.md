# Bit-field problems

### Implement functions to toggle, set, and clear a bit.
`uint32_t toggle_bit(uint32_t num, uint8_t position); // example: toggle_bit(5, 1) => 7`

`uint32_t set_bit(uint32_t num, uint8_t position); // example: toggle_bit(5, 1) => 7`

`uint32_t clear_bit(uint32_t num, uint8_t position); // example: toggle_bit(7, 1) => 5`

`bool is_bit_set(uint32_t num, uint8_t position);`

`uint32_t set_multiple_bits(uint32_t num, uint32_t mask);`

`uint32_t clear_multiple_bits(uint32_t num, uint32_t mask);`

`uint32_t toggle_multiple_bits(uint32_t num, uint32_t mask);`

### Register writes
You are given this register:
```
31        16 15      8 7      0
+-----------+---------+--------+
| Reserved  | MODE    | ENABLE |
+-----------+---------+--------+
```
Write safe code to modify only MODE.
Why might C bitfields be dangerous here?
What happens if the register is write-one-to-clear?