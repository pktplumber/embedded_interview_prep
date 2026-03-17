# Basic
You are working on firmware for a microcontroller that reads analog sensor data using an ADC. The sensor is noisy, so you must implement a moving average filter to smooth the readings.

The ADC is 12-bits and is sampled once every millisecond.

Your task is to implement a moving average filter over the last 16 samples. The filtered value should update every time a new sample arrives.

Implement the function `uint16_t moving_average_update(uint16_t new_sample);` that:
- Inserts the new sample into the filter window.
- Removes the oldest sample.
- Returns the current average of the last 16 samples.
- Runs in O(1) time per update.
- Uses constant memory

# Advanced
Now, say the ADC runs continuously using DMA into a circular buffer and hardware fills the buffer automatically.

You must compute the moving average without copying data.

System:
- ADC sampling: 20 kHz
- DMA buffer size: 128 samples
- 12-bit ADC
- Called in a timer every 1 ms

Hardware exposes a pointer: `uint16_t dma_get_write_index(void);`

**Compute the average of the last 32 samples.**

Constraints:
- Cannot copy the DMA buffer
- Must handle wrap-around
- Must run in <10 µs
- DMA may update the buffer while you're reading it
