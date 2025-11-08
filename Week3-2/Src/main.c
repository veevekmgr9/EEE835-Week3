#include "uart_driver.h"     // Include custom UART driver header
#include "systick_config.h"  // Include SysTick timer configuration header

// Debug flag to indicate successful UART1 initialization
uint8_t uart1_success = 0;  
// Variable to store UART1 transmission status
UART_Status_t UART1_TX;

int main(void){
    // Initialize SysTick timer for delay
    SysTick_Init();
    // UART1 configuration structure
    UART_Config_t uart1_config = {
        .baudrate = 115200,             // Set baud rate to 115200 bps
        .parity = UART_PARITY_NONE,     // No parity bit
        .stop_bits = UART_STOPBITS_1,   // One stop bit
        .word_length = UART_WORDLENGTH_8B // 8-bit data frame
    };

    // UART2 configuration structure
    UART_Config_t uart2_config = {
        .baudrate = 115200,             // 115200 bps baud rate
        .word_length = UART_WORDLENGTH_8B, // 8-bit word length
        .stop_bits = UART_STOPBITS_1,   // 1 stop bit
        .parity = UART_PARITY_NONE,     // No parity bit
    };

    // Initialize UART1 with defined configuration
    if (UART1_Init(&uart1_config) == UART_OK) {
        uart1_success = 1;  // Set flag to indicate UART1 initialized successfully
    }

    // Initialize UART2 with defined configuration
    if (UART2_Init(&uart2_config) == UART_OK) {

        // Transmit a test message via UART2 to confirm initialization
        uint8_t msg[] = "Hello, UART2!\r\n";
        UART2_Transmit(msg, sizeof(msg) - 1, 1000); // Send message with 1s timeout

        // Buffer to store received byte
        uint8_t received_byte;

        // Infinite loop to handle UART data exchange
        while (1) {
            // Check if data is available on UART2 RX line
            if (UART2_IsDataAvailable()) {
                // Read one received byte from UART2
                received_byte = UART2_ReceiveByte();

                // Transmit received byte via UART1
                UART1_TX = UART1_TransmitByte(received_byte); 

                // Send the transmission result/status back to UART2
                UART2_TransmitByte((uint8_t)UART1_TX); 
            }
        }
    }
}
