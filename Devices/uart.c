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

void serial_init(void);
void send_char_serial (char data);
char receive_char_serial (void);

int main(int argc, char* argv[]) {

	DDRD |= (1 << LIGHT);
	LIGHT_OFF();
	serial_init();

	FILE s=FDEV_SETUP_STREAM(send_char_serial,NULL,_FDEV_SETUP_WRITE);
	stdout=&s;

	printf("Test String\n");

	while (1) {
		send_char_serial(receive_char_serial());
		LIGHT_ON();
	}

	return 0;
}

void serial_init(void) {
	UBRRH=0;
	UBRRL=103; // 9600 BAUD FOR 1MHZ SYSTEM CLOCK
	UCSRC= (1<<URSEL)|(1 << USBS)|(3<<UCSZ0);	// 8 BIT NO PARITY 2 STOP
	UCSRB=(1<<RXEN);//|(1<<TXEN);	// ENABLE TX, RX, and RX receive interrupt 
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
