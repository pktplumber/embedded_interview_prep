#include <stdint.h>
#include <stddef.h>

#define WINDOW_SIZE         16
#define WINDOW_SIZE_POW     4

static uint16_t Readings[WINDOW_SIZE];

static size_t OldestReading;
static size_t NumSamples;
static uint32_t CurrSum;

// Added init function incase moving average needs to be reset.
void init(void)
{
    CurrSum = 0;
    NumSamples = 0;
    OldestReading = 0;
}

// Looking for the following:
//  1. Correct solution
//  2. Use sum instead of looping over samples each time
//  3. Correct use of counter/tail index. The tail index should
//     loop back to the start of the array when full
//  4. Bit tricks to avoid division and modulo. Only works if window
//     size is a power of 2
//  5. Prevent overflows
uint16_t moving_average_update(uint16_t new_sample)
{
    uint16_t ret = 0;
    if (NumSamples < WINDOW_SIZE)
    {
        // We don't have enough samples for the full window width yet.
        // Update the readings array
        Readings[NumSamples] = new_sample & 0xFFF; // Use mask just in case
        NumSamples = (NumSamples + 1); 
        CurrSum += new_sample;
        // Need to use actual division, since the readings might not be a power of 2
        ret = (uint16_t)(CurrSum/NumSamples);
    }
    else
    {
        // We have a full window's worth of samples
        // Remove oldest reading
        CurrSum -= Readings[OldestReading];
        // Add newest reading to sum
        CurrSum += new_sample & 0xFFF; // Mask 12 bits just in case
        // Update oldest reading to the latest value
        Readings[OldestReading] = new_sample & 0xFFF;
        // Now increment the oldest reading index, so the latest isn't overwritten
        OldestReading = (OldestReading + 1) & (WINDOW_SIZE - 1); // Modulo is expensive, '&' with
                                                            // window size instead since it is a
                                                            // power of 2
        // Calc average. Since the window size is a power of 2, we can use the bit-shift to divide
        ret = (uint16_t)(CurrSum >> WINDOW_SIZE_POW);
    }

    return ret;
}


// Follow up questions:
// - How would you modify this if WINDOW_SIZE is not a power of two?
// - How would you make this thread-safe if accessed from both ISR and main loop?
// - How could you make the window size configurable at runtime?
// - How would you implement the same thing without storing all samples?




// Follow up questions answered:
// - You could not use the bit-shift/masking. You would have to do the actual modulo
// - If called from main loop, disable interrupt before calling, re-enable after return
// - 
