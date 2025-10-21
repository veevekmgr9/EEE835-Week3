#include "uart_driver.h"
#include "systick_config.h"
uint8_t uart1_success = 0; // for debugging
UART_Status_t UART1_TX;

int main(void){

	SysTick_Init();

	UART_Config_t uart1_config = {
			.baudrate = 115200,
			.parity = UART_PARITY_NONE,
			.stop_bits = UART_STOPBITS_1,
			.word_length = UART_WORDLENGTH_8B
	};

	UART_Config_t uart2_config = {
			.baudrate = 115200,
			.word_length = UART_WORDLENGTH_8B,
			.stop_bits = UART_STOPBITS_1,
			.parity = UART_PARITY_NONE,
	};

	if (UART1_Init(&uart1_config) == UART_OK){
		uart1_success = 1;
	}

	// Initialise UART2
	if (UART2_Init(&uart2_config) == UART_OK) {
		// Send a test message
		uint8_t msg[] = "Hello, UART2!\r\n";
		UART2_Transmit(msg, sizeof(msg) - 1, 1000);

		// Echo received data
		uint8_t received_byte;
		while (1) {
			if (UART2_IsDataAvailable()) {
				received_byte = UART2_ReceiveByte();
				UART1_TX = UART1_TransmitByte(received_byte); // Echo back
				UART2_TransmitByte((uint8_t)UART1_TX); // Echo UART1 TX result
			}
		}
	}

}
