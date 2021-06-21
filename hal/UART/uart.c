#include <stdint.h>
#include "sam3x8a.h"
#if 0
#include "dma.h"
#endif
#include "uart.h"
#include "buffers.h"
#include "pmc.h"
#include "reactor.h"


const uart_pindata_t pin_cfgs[] = {{GPIOA,  9,  8, GPIO_AF1_MODE},
                                   {GPIOA, 11, 10, GPIO_AF1_MODE},
                                   {GPIOA, 13, 12, GPIO_AF1_MODE},
                                   {GPIOB, 20, 21, GPIO_AF1_MODE},
                                   {GPIOD,  4,  5, GPIO_AF2_MODE}};

uart_t SD1;
uart_t SD2;
uart_t SD3;
uart_t SD4;
uart_t SD5;

void uart_init() {
    SD1.dev = UART;
    SD1.pins = pin_cfgs[0];
    SD1.last_error_code = 0;
    SD1.rx_threshold = 0;
    SD1.rx_complete_cb = 0;
    SD1.tx_complete_cb = 0;
    SD1.error_cb = 0;

    SD2.dev = USART0;
    SD2.pins = pin_cfgs[1];
    SD2.last_error_code = 0;
    SD2.rx_threshold = 0;
    SD2.rx_complete_cb = 0;
    SD2.tx_complete_cb = 0;
    SD2.error_cb = 0;

    SD3.dev = USART1;
    SD3.pins = pin_cfgs[2];
    SD3.last_error_code = 0;
    SD3.rx_threshold = 0;
    SD3.rx_complete_cb = 0;
    SD3.tx_complete_cb = 0;
    SD3.error_cb = 0;

    SD4.dev = USART2;
    SD4.pins = pin_cfgs[3];
    SD4.last_error_code = 0;
    SD4.rx_threshold = 0;
    SD4.rx_complete_cb = 0;
    SD4.tx_complete_cb = 0;
    SD4.error_cb = 0;

    SD5.dev = USART3;
    SD5.pins = pin_cfgs[4];
    SD5.last_error_code = 0;
    SD5.rx_threshold = 0;
    SD5.rx_complete_cb = 0;
    SD5.tx_complete_cb = 0;
    SD5.error_cb = 0;

#if UART_USE_DMA == 1
    SD1.dma_rx_channel = DMA_UART_RX_CHANNEL;
    SD1.dma_tx_channel = DMA_UART_TX_CHANNEL;

    SD2.dma_rx_channel = DMA_USART0_RX_CHANNEL;
    SD2.dma_tx_channel = DMA_USART0_TX_CHANNEL;

    SD3.dma_rx_channel = DMA_USART1_RX_CHANNEL;
    SD3.dma_tx_channel = DMA_USART1_TX_CHANNEL;

    SD4.dma_rx_channel = DMA_USART2_RX_CHANNEL;
    SD4.dma_tx_channel = DMA_USART2_TX_CHANNEL;

    SD5.dma_rx_channel = DMA_USART3_RX_CHANNEL;
    SD5.dma_tx_channel = DMA_USART3_TX_CHANNEL;
#endif /* UART_USE_DMA */
}

void uart_start(uart_t* drv, uart_config_t* config) {
    uint32_t fck;

    drv->rx_threshold = config->rx_threshold > UART_BUFFER_SIZE - 1 ?
	UART_BUFFER_SIZE - 1 : config->rx_threshold;
    drv->rx_complete_cb = config->rx_complete_cb;
    drv->tx_complete_cb = config->tx_complete_cb;
    drv->error_cb = config->error_cb;

    buffer_reset(drv->tx_buf);
    buffer_reset(drv->rx_buf);

#if UART_USE_DMA == 1
    dma_start(&DMAD1);
#endif /* UART_USE_DMA */

    gpio_set_pin_mode(drv->pins.port, drv->pins.tx_pin, drv->pins.mode);
    gpio_set_pin_mode(drv->pins.port, drv->pins.rx_pin, drv->pins.mode);

    if (drv == &SD1) {
	NVIC_EnableIRQ(UART_IRQn);
	NVIC_SetPriority(UART_IRQn, 7); /* Middle Range priority */
	PMC_UART_CLK_ENABLE();
    } else if (drv == &SD2) {
	NVIC_EnableIRQ(USART0_IRQn);
	NVIC_SetPriority(USART0_IRQn, 7); /* Middle Range priority */
	PMC_USART0_CLK_ENABLE();
    } else if (drv == &SD3) {
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn, 7); /* Middle Range priority */
	PMC_USART1_CLK_ENABLE();
    } else if (drv == &SD4) {
	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_SetPriority(USART2_IRQn, 7); /* Middle Range priority */
	PMC_USART2_CLK_ENABLE();
    } else if (drv == &SD5) {
	NVIC_EnableIRQ(USART3_IRQn);
	NVIC_SetPriority(USART3_IRQn, 7); /* Middle Range priority */
	PMC_USART3_CLK_ENABLE();
    }

    /* Compute the BRR value based on an MCK clock speed of 84 MHz */
    /* TODO: write the logic for the other UARTs and other clock
       speeds */
    fck = (84000000 / config->baudrate) >> 4;

    /* TODO: Make configuration flexible for parity, word length, and
       error detection */
    /* TODO: Support for Synchronous mode, half duplex mode and CTS
       and HW flow control */
    /* TODO: Support for LIN, IrDA and smartcard */
    /* Enable usart module, receiver and receive interrupt, with 8N1
       communication */
    drv->dev->CR  = UART_CR_RSTSTA | UART_CR_RSTRX | UART_CR_RSTTX;
    drv->dev->CR  = UART_CR_RXEN;
    drv->dev->MR  = UART_MR_NO_PAR | UART_MR_CHMODE_NORMAL;
    drv->dev->IER = UART_IMR_RXRDY | UART_IMR_PARE |
        UART_IMR_FRAME | UART_IMR_OVRE;
        
    drv->dev->BRGR = fck;
}

void uart_stop(uart_t* drv) {
    drv->dev->CR = UART_CR_RXDIS | UART_CR_TXDIS;
    while (!(drv->dev->SR & UART_SR_TXEMPTY))
        ;

    if (drv == &SD1) {
	PMC_UART_CLK_DISABLE();
	NVIC_DisableIRQ(UART_IRQn);
    } else if (drv == &SD2) {
	PMC_USART0_CLK_DISABLE();
	NVIC_DisableIRQ(USART0_IRQn);
    } else if (drv == &SD3) {
	PMC_USART1_CLK_DISABLE();
	NVIC_DisableIRQ(USART1_IRQn);
    } else if (drv == &SD4) {
	PMC_USART2_CLK_DISABLE();
	NVIC_DisableIRQ(USART2_IRQn);
    } else if (drv == &SD5) {
	PMC_USART3_CLK_DISABLE();
	NVIC_DisableIRQ(USART3_IRQn);
    }

    drv->dev->IDR = UART_IMR_RXRDY;
}

#define uart_pos_push_action(buf, c, ret_val) {}
#define uart_buffer_push(buf, c, ret_val)                               \
    buffer_generic_push(buf, c, ret_val,                                \
                        BUFFER_PUSH_FULL_ACTION, uart_pos_push_action)
uint8_t uart_putc(uart_t* drv, uint8_t c) {
    uint8_t rv;

#if UART_USE_DMA == 1
    if (dma_is_busy(&DMAD1, drv->dma_tx_channel))
	return -2;
#endif

    uart_buffer_push(drv->tx_buf, c, rv);
    drv->dev->IER = UART_IMR_TXRDY;
    drv->dev->CR = UART_CR_TXEN;
    return rv;
}

#define uart_pos_pop_action(buf, c) {}
#define uart_buffer_pop(buf, c)                                         \
    buffer_generic_pop(buf, c, BUFFER_POP_EMPTY_ACTION,                 \
                       uart_pos_pop_action)
uint16_t uart_getc(uart_t* drv) {
    uint16_t c = 0;
    uart_buffer_pop(drv->rx_buf, c);
    return c;
}

int uart_write(uart_t* drv, const uint8_t *msg, int n) {
    int ctr = 0;
    uint8_t rv = 0;

#if UART_USE_DMA == 1
    if (dma_is_busy(&DMAD1, drv->dma_tx_channel))
	return 0;
#endif

    /* Write characters until either the end of the message or the
       buffer is full */
    while (ctr++ < n && rv != -1) {
	uart_buffer_push(drv->tx_buf, *msg, rv);
	msg++;
    }
    drv->dev->IER = UART_IMR_TXRDY;
    drv->dev->CR = UART_CR_TXEN;
    return --ctr;
}

int uart_read(uart_t* drv, uint8_t *buf, int n) {
    int i = 0;
    uint16_t c;
    while (i < n && (c = uart_getc(drv)) != (uint16_t) -1) {
	*buf++ = (uint8_t) c;
	i++;
    }
    return i;
}

#if UART_USE_DMA == 1
void uart_write_dma_cb(hcos_word_t arg) {
    uart_t *drv = (uart_t *) arg;

    drv->dev->CR3 &= ~USART_CR3_DMAT;
}

int uart_write_dma(uart_t* drv, const uint8_t *buf, int n, reactor_cb_t write_end_cb) {
    /* First test if we are already transmitting, in which case we
       return an error */
    dma_bind_config_t cfg = {.peripheral_address = (uint32_t) &drv->dev->DR,
			     .memory_address  = (uint32_t) buf,
			     .nbr_transfers    = n,
			     .mem2mem_flag    = 0,
			     .priority        = UART_DMA_PRIO,
			     .peripheral_size = DMA_PER_SIZE_8BITS,
			     .memory_size     = DMA_MEM_SIZE_8BITS,
			     .peripheral_increment = DMA_NO_PER_INCREMENT_MODE,
			     .memory_increment = DMA_MEM_INCREMENT_MODE,
			     .direction = DMA_FROM_MEM_MODE,
			     .circular_mode = DMA_NO_CIRCULAR_MODE,
			     .half_transfer_cb = 0,
			     .full_transfer_cb = write_end_cb,
			     .error_cb = 0,
			     .half_transfer_args = 0,
			     .full_transfer_args = (hcos_word_t) drv,
			     .error_args = 0,
			     .half_transfer_rt_cb = 0,
			     .full_transfer_rt_cb = uart_write_dma_cb,
			     .error_rt_cb = 0,
			     .half_transfer_rt_args = 0,
			     .full_transfer_rt_args = (hcos_word_t) drv,
			     .error_rt_args = 0,
    };

    if (uart_is_busy_tx(drv) || dma_is_busy(&DMAD1, drv->dma_tx_channel))
	return 1;

    dma_bind(&DMAD1, drv->dma_tx_channel, cfg);
    drv->dev->CR3 |= USART_CR3_DMAT;
    drv->dev->SR &= ~USART_SR_TC;
    dma_enable(&DMAD1, drv->dma_tx_channel);

    return 0;
}

void uart_read_dma_cb(hcos_word_t arg) {
    uart_t *drv = (uart_t *) arg;

    drv->dev->CR3 &= ~USART_CR3_DMAT;
    drv->dev->CR1 |= USART_CR1_RXNEIE;
}

int uart_read_dma(uart_t* drv, uint8_t *buf, int n, reactor_cb_t read_end_cb) {
    dma_bind_config_t cfg = {.peripheral_address = (uint32_t) &drv->dev->DR,
			     .memory_address  = (uint32_t) buf,
			     .nbr_transfers   = n,
			     .mem2mem_flag    = 0,
			     .priority        = UART_DMA_PRIO,
			     .peripheral_size = DMA_PER_SIZE_8BITS,
			     .memory_size     = DMA_MEM_SIZE_8BITS,
			     .peripheral_increment = DMA_NO_PER_INCREMENT_MODE,
			     .memory_increment = DMA_MEM_INCREMENT_MODE,
			     .direction = DMA_FROM_PER_MODE,
			     .circular_mode = DMA_NO_CIRCULAR_MODE,
			     .half_transfer_cb = 0,
			     .full_transfer_cb = read_end_cb,
			     .error_cb = 0,
			     .half_transfer_args = 0,
			     .full_transfer_args = (hcos_word_t) drv,
			     .error_args = 0,
			     .half_transfer_rt_cb = 0,
			     .full_transfer_rt_cb = uart_read_dma_cb,
			     .error_rt_cb = 0,
			     .half_transfer_rt_args = 0,
			     .full_transfer_rt_args = (hcos_word_t) drv,
			     .error_rt_args = 0,
    };

    if (dma_is_busy(&DMAD1, drv->dma_rx_channel))
	return 1;

    drv->dev->CR1 &= ~USART_CR1_RXNEIE;
    dma_bind(&DMAD1, drv->dma_rx_channel, cfg);
    drv->dev->CR3 |= USART_CR3_DMAT;
    dma_enable(&DMAD1, drv->dma_rx_channel);

    return 0;
}
#endif /* UART_USE_DMA */


/*
 * IRQ handler definitions 
 * TODO: Implement the USART handlers (only the UART is implemented)
 */
#define uart_irq_pos_pop_action(buf, c) do {	\
    } while (0)
#define uart_irq_pop_empty_action(buf, c) do {         \
	UART->IDR = UART_IMR_TXRDY;                    \
	if (SD1.tx_complete_cb)                        \
	    reactor_add_handler(SD1.tx_complete_cb,    \
                                (hcos_word_t) &SD1);   \
    } while(0)
#define uart_irq_buffer_pop(buf, c)                        \
    buffer_generic_pop(buf, c, uart_irq_pop_empty_action,  \
                       uart_irq_pos_pop_action)
void UART_Handler() {
    uint16_t sr = UART->SR;
    uint32_t imr = UART->IMR;

    if (((sr & UART_SR_TXRDY) != 0) && ((imr & UART_IMR_TXRDY) != 0))
	uart_irq_buffer_pop(SD1.tx_buf, UART->THR);

    /* If there is no error,  */
    if (!(sr & (UART_SR_PARE | UART_SR_FRAME | UART_SR_OVRE))) {
	/* TODO: Decide whether we only handle a received byte if the
	   interrupt is enabled or not */
	if (((sr & UART_SR_RXRDY) != 0) &&
            ((imr & UART_IMR_RXRDY) != 0)) {
	    uint8_t rv;
	    uint8_t c = UART->THR;
	    uart_buffer_push(SD1.rx_buf, c, rv);
	    if (rv != -1 && SD1.rx_complete_cb &&
                buffer_occupancy(SD1.rx_buf) >= SD1.rx_threshold)
		reactor_add_handler(SD1.rx_complete_cb,
                                    (hcos_word_t) &SD1);
	}
    } else
        /* TODO: Be more flexible on error handling. For now, just
           reset the flags */
        UART->CR = UART_CR_RSTSTA;
}

#if 0
void USART0_Handler() {
    uint16_t sr = USART0->SR;
    uint32_t imr = USART0->IMR;

    /* gpio_toggle_pin(GPIOB, 27); */

    if (((sr & UART_SR_TXRDY) != 0) && ((imr & UART_IMR_TXRDY) != 0))
	uart_irq_buffer_pop(SD2.tx_buf, USART0->THR);

    /* If there is no error,  */
    if (!(sr & (UART_SR_PARE | UART_SR_FRAME | UART_SR_OVRE))) {
	/* TODO: Decide whether we only handle a received byte if the
	   interrupt is enabled or not */
	if (((sr & UART_SR_RXRDY) != 0) &&
            ((imr & UART_IMR_RXRDY) != 0)) {
	    uint8_t rv;
	    uint8_t c = USART0->THR;
	    uart_buffer_push(SD2.rx_buf, c, rv);
	    if (rv != -1 && SD2.rx_complete_cb &&
                buffer_occupancy(SD2.rx_buf) >= SD2.rx_threshold)
		reactor_add_handler(SD2.rx_complete_cb,
                                    (hcos_word_t) &SD2);
	}
    }
}

void USART1_Handler() {
    uint16_t sr = USART1->SR;
    uint32_t imr = USART1->IMR;

    /* gpio_toggle_pin(GPIOB, 27); */

    if (((sr & UART_SR_TXRDY) != 0) && ((imr & UART_IMR_TXRDY) != 0))
	uart_irq_buffer_pop(SD3.tx_buf, USART1->THR);

    /* If there is no error,  */
    if (!(sr & (UART_SR_PARE | UART_SR_FRAME | UART_SR_OVRE))) {
	/* TODO: Decide whether we only handle a received byte if the
	   interrupt is enabled or not */
	if (((sr & UART_SR_RXRDY) != 0) &&
            ((imr & UART_IMR_RXRDY) != 0)) {
	    uint8_t rv;
	    uint8_t c = USART1->THR;
	    uart_buffer_push(SD3.rx_buf, c, rv);
	    if (rv != -1 && SD3.rx_complete_cb &&
                buffer_occupancy(SD3.rx_buf) >= SD3.rx_threshold)
		reactor_add_handler(SD3.rx_complete_cb,
                                    (hcos_word_t) &SD3);
	}
    }
}

void USART2_Handler() {
    uint16_t sr = USART2->SR;
    uint32_t imr = USART2->IMR;

    /* gpio_toggle_pin(GPIOB, 27); */

    if (((sr & UART_SR_TXRDY) != 0) && ((imr & UART_IMR_TXRDY) != 0))
	uart_irq_buffer_pop(SD4.tx_buf, USART2->THR);

    /* If there is no error,  */
    if (!(sr & (UART_SR_PARE | UART_SR_FRAME | UART_SR_OVRE))) {
	/* TODO: Decide whether we only handle a received byte if the
	   interrupt is enabled or not */
	if (((sr & UART_SR_RXRDY) != 0) &&
            ((imr & UART_IMR_RXRDY) != 0)) {
	    uint8_t rv;
	    uint8_t c = USART2->THR;
	    uart_buffer_push(SD4.rx_buf, c, rv);
	    if (rv != -1 && SD4.rx_complete_cb &&
                buffer_occupancy(SD4.rx_buf) >= SD4.rx_threshold)
		reactor_add_handler(SD4.rx_complete_cb,
                                    (hcos_word_t) &SD4);
	}
    }
}

void USART3_Handler() {
    uint16_t sr = USART3->SR;
    uint32_t imr = USART3->IMR;

    /* gpio_toggle_pin(GPIOB, 27); */

    if (((sr & UART_SR_TXRDY) != 0) && ((imr & UART_IMR_TXRDY) != 0))
	uart_irq_buffer_pop(SD5.tx_buf, USART3->THR);

    /* If there is no error,  */
    if (!(sr & (UART_SR_PARE | UART_SR_FRAME | UART_SR_OVRE))) {
	/* TODO: Decide whether we only handle a received byte if the
	   interrupt is enabled or not */
	if (((sr & UART_SR_RXRDY) != 0) &&
            ((imr & UART_IMR_RXRDY) != 0)) {
	    uint8_t rv;
	    uint8_t c = USART3->THR;
	    uart_buffer_push(SD5.rx_buf, c, rv);
	    if (rv != -1 && SD5.rx_complete_cb &&
                buffer_occupancy(SD5.rx_buf) >= SD5.rx_threshold)
		reactor_add_handler(SD5.rx_complete_cb,
                                    (hcos_word_t) &SD5);
	}
    }
}
#endif
