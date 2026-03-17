#include <stdint.h>

#define DMA_BUF_SIZE 128
#define AVG_WINDOW   32

extern volatile uint16_t adc_dma_buffer[DMA_BUF_SIZE];
extern uint16_t dma_get_write_index(void);  // Provided by hardware driver library

// Looking for:
// 1. 
uint16_t compute_adc_average(void)
{
    uint32_t sum = 0;

    uint16_t write_idx = dma_get_write_index();

    /* newest sample index */
    int32_t idx = write_idx - 1;

    if (idx < 0)
        idx += DMA_BUF_SIZE;

    for (uint32_t i = 0; i < AVG_WINDOW; i++)
    {
        sum += adc_dma_buffer[idx];

        idx--;
        if (idx < 0)
            idx = DMA_BUF_SIZE - 1;
    }

    return (uint16_t)(sum / AVG_WINDOW);
}