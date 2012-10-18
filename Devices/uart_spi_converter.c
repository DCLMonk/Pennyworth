/**
 * Pennyworth - A new smarthome protocol.
 * Copyright (C) 2012  Dream-Crusher Labs LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL

#include <util/delay.h>
#include <string.h>

#define LIGHT_PORT	PORTD
#define LIGHT		PD7

#define MISO		PB4
#define MOSI		PB3
#define SCK		PB5
#define SS0		PD6
#define SS1		PD5

#define SS_DELAY_COUNT	25

#define LIGHT_OFF()	LIGHT_PORT |= (1<<LIGHT)
#define LIGHT_ON()	LIGHT_PORT &= ~(1<<LIGHT)

#define RELAY_ON()	RELAY_PORT |= (1<<RELAY)
#define RELAY_OFF()	RELAY_PORT &= ~(1<<RELAY)

#define SS0_HIGH()	PORTD |= (1<<SS0)
#define SS0_LOW()	PORTD &= ~(1<<SS0)

#define SS1_HIGH()	PORTD |= (1<<SS1)
#define SS1_LOW()	PORTD &= ~(1<<SS1)

#define SS_DELAY()	_delay_ms(SS_DELAY_COUNT)

#define MAX_BUFF_LEN 256

void spi_master_init(void);
void spi_master_transmit_char(char c);
char spi_master_receive_char(char c);
void serial_init(void);
void send_char_serial (char data);
char receive_char_serial (void);

volatile char received;
volatile char packet_len;
volatile char received_char[MAX_BUFF_LEN];
volatile char received_len;

int main(int argc, char* argv[]) {

	char c, r;
	unsigned char ret;

	int i;

	received = 0;
	received_len = 0;
	packet_len = 0;

	// define direction of inputs and outputs
	// 1 for output, 0 for input
	// | for output, & for input
	DDRD |= (1<<LIGHT);
	DDRD |= (1<<SS0);
	DDRD |= (1<<SS1);

	LIGHT_OFF();

	spi_master_init();

	serial_init();

	sei();
	
	SS0_HIGH();
	SS1_HIGH();
	SS_DELAY();

	while (1) {
		// put poll devices stuff here
		SS0_LOW();
		spi_master_transmit_char('\0');
		SS0_HIGH();
		SS_DELAY();
		SS0_LOW();
		c = spi_master_receive_char('\0');
		SS0_HIGH();
		SS_DELAY();
		if (c != '\0') {
			char len = c;
			send_char_serial(c);
			for (i = 0; i < len; i++) {
				SS0_LOW();
				c = spi_master_receive_char('\0');
				SS0_HIGH();
				SS_DELAY();
				send_char_serial(c);	
			}
		}
	
		SS1_LOW();
		spi_master_transmit_char('\0');
		SS1_HIGH();
		SS_DELAY();
		SS1_LOW();
		c = spi_master_receive_char('\0');
		SS1_HIGH();
		SS_DELAY();
		if (c != '\0') {
			char len = c;
			send_char_serial(c);
			for (i = 0; i < len; i++) {
				SS1_LOW();
				c = spi_master_receive_char('\0');
				SS1_HIGH();
				SS_DELAY();
				send_char_serial(c);	
			}
		}

		if (received) {
			for (i = 0; i < received_len; i++) {
				SS0_LOW();
				SS1_LOW();
				spi_master_transmit_char(received_char[i]);
				SS0_HIGH();
				SS1_HIGH();
				SS_DELAY();
				// on long lines, might want delay here
			}
			received = 0;
			received_len = 0;
		}
	}

	return 0;
}

void spi_master_init(void) {
	DDRB |= (1<<MOSI) | (1<<SCK);	// outputs
	DDRB &= ~(1<<MISO);				// inputs
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1) | (1<<SPR0); 	// enable SPI, Master, set clock rate fck/16
}

// function to transmit character from master over SPI
// parameters:	char to send
// returns:
void spi_master_transmit_char(char data) {
	SPDR = data;				// start transmission
	while (!(SPSR & (1<<SPIF)));		// wait for transmition to complete
}

// function to receive character from slave over SPI
// parameters:	
// returns:	char received
char spi_master_receive_char(char c) { 		//data is junk to send
	SPDR = c;
	while (!(SPSR & (1<<SPIF)));		// wait for transmission to complete
	return SPDR;
}

void spi_master_transmit_string(char* s) {
	int i;

	for (i = 0; i < strlen(s); i++) {
		spi_master_transmit_char(s[i]);
	}
}

void serial_init(void) {
	UBRRH=0;
	UBRRL=12; // 9600 BAUD FOR 1MHZ SYSTEM CLOCK
	UCSRC= (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);	// 8 BIT NO PARITY 2 STOP
	UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);	// ENABLE TX, RX, and RX receive interrupt 
	UCSRA |= (1<<U2X);	// double baud rate for less error
	char c = UDR; // to clear the RXC flag
}

void send_char_serial (char data) {
	/* Wait for empty transmit buffer */
	while (!(UCSRA & (1<<UDRE)));
	/* Put data into buffer, sends the data */
	UDR = data;
}

char receive_char_serial (void) {
	/* Wait for data to be received */
	while (!(UCSRA & (1<<RXC)));
	/* Get and return received data from buffer */
	return UDR;
}

void send_string_serial(char* s) {
	int i;
	for (i = 0; i < strlen(s); i++) {
		send_char_serial(s[i]);
		if (s[i] == '\n') {
			send_char_serial('\r');
		}
	}
}

ISR(USART_RXC_vect) {
	received_char[received_len] = UDR;
	if (received_len == 0) {
		packet_len = received_char[0];
	} else {
		packet_len--;
	}
	
	if (received_len == 3) {
		if (received_char[received_len] == 0) LIGHT_ON();
	}

	received_len++;
	if (packet_len == 0) {
		if (received_len > 1) {
			received = 1;
		} else {
			received_len = 0;
		}
	}
}
