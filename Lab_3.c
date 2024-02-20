#include <avr/io.h>
#include <util/delay.h>

// Define the trigger pin and port for PORTD
#define TRIGGER_PIN_PD PD2
#define TRIGGER_PIN_PB PB1
#define TRIGGER_PIN_PC PC1

void initialize_ports() {
    // Set all PORTD, PORTB, and PORTC pins as outputs
    DDRD = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
}

void toggle_pin(volatile uint8_t* port, uint8_t pin) {
    // Set pin high
    *port |= (1 << pin); 
    _delay_ms(100); 

    // Set pin low
    *port &= ~(1 << pin);
    _delay_ms(100); 
}

int main(void) {
    initialize_ports();

    while(1) {
        // Signal before each looping circle
        PORTD |= (1 << TRIGGER_PIN_PD); // Trigger pin high
        _delay_ms(100);
        PORTD &= ~(1 << TRIGGER_PIN_PD); // Trigger pin low
        _delay_ms(100);

        // Sequentially toggle each I/O pin on PORTD, skipping the trigger pin
        for (int pin = 0; pin < 8; pin++) {
            if(pin == TRIGGER_PIN_PD) continue;
            toggle_pin(&PORTD, pin);
        }

        // Same for PORTD:
        for (int pin = 0; pin < 8; pin++) {
            if(pin == TRIGGER_PIN_PB) continue;
            toggle_pin(&PORTB, pin);
        }

        // Same for PORTC:
        for (int pin = 0; pin < 8; pin++) {
            if(pin == TRIGGER_PIN_PC) continue;
            toggle_pin(&PORTC, pin);
        }
    }
}
