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

#define F_CPU 8000000UL

#include <util/delay.h>
#include <string.h>

#define BUFFER_LENGTH 64

#include "../ClientLib/DeviceClient.h"

#define LIGHT_PORT	PORTD
#define LIGHT		PD7

#define RELAY_PORT	PORTD
#define RELAY		PD5

#define MISO		PB4
#define MOSI		PB3
#define SCK		PB5
#define SS		PD6

#define LIGHT_OFF()	LIGHT_PORT |= (1<<LIGHT)
#define LIGHT_ON()	LIGHT_PORT &= ~(1<<LIGHT)

#define RELAY_ON()	RELAY_PORT |= (1<<RELAY)
#define RELAY_OFF()	RELAY_PORT &= ~(1<<RELAY)

#define MAX_LEN 128 

enum {IDLE = 0, RECEIVE, TRANSMIT, BURN};

void serial_init(void);
void send_char_serial (char data);
char receive_char_serial (void);
void buffered_send_char(char c);
void serial_tx_enable();
void serial_tx_disable();

volatile char transmit_flag;
volatile char buf[MAX_LEN];
volatile char buf_index;

int main(int argc, char* argv[]) {

	unsigned char ret;
	char c;
	char len;
	char i;
	char name[8];
	char* bname = "Light_0";

	for (c = 0; bname[c] != '\0'; c++) {
		name[c] = bname[c];
	}
	name[c] = '\0';

	unsigned char did = 1;

	// define direction of inputs and outputs
	// 1 for output, 0 for input
	// | for output, & for input
	DDRD = (1<<LIGHT);
	DDRD |= (1<<RELAY);

	DDRC = 0;

	did = PINC & 0x7;
	name[c - 1] += did;

	LIGHT_OFF();

	serial_init();

	buf_index = 0;	
	transmit_flag = 0;	

//	FILE s=FDEV_SETUP_STREAM(send_char_serial,NULL,_FDEV_SETUP_WRITE);
//	stdout=&s;

//	sei();

	Device* device = createDevice(name, 1, buffered_send_char);
	
	setDeviceCName("Light", device);
	setDeviceLocation(0, 0, 0, 0, device);
	
	addField(BOOL, "Light Status", 0, 1, 0, device);

	while (1) {
		c = receive_char_serial();
		if (c == '\0') {
			if (receive_char_serial() == did) {
				serial_tx_enable();
				if (transmit_flag) {
					len = buf[0] + 1;
//					printf("sending packet %d\n", buf[3]);
					for (i = 0; i < len; i++) {
						send_char_serial(buf[i]);
					}
//					printf("bi:%d %d %d\n", buf_index, len, buf[3]);
					for (i = len; i < buf_index; i++) {
						buf[i-len] = buf[i];
					}
					buf_index -= len;
					if (buf_index == 0) {
						transmit_flag = 0;
					}
				} else {
					send_char_serial('\0');
				}
				serial_tx_disable();
			}
		} else {
			len = c;
			recvChar(len, device);
			for (i = 0; i < len; i++) {
				c = receive_char_serial();
				recvChar(c, device);
			}
		}
/*
		if (((r_front + 1) % MAX_LEN) != r_back) {
			r_front++;
			if (r_front == MAX_LEN) {
				r_front = 0;
			}
			recvChar(r_buf[r_front], device);
		}
*/

		if (hasChanged(0, device)) {
			ret = getBoolVal(0, device);
			if (ret) {
				RELAY_ON();
				LIGHT_ON();
			} else {
				RELAY_OFF();
				LIGHT_OFF();
			}
		}
	}

	return 0;
}

void buffered_send_char(char c) {
	static char len = 0;
	if (len == 0) len = c+1;
	if (buf_index < MAX_LEN) {
		buf[buf_index++] = c;
		len--;
		if (len == 0) {
			transmit_flag = 1;
		}
	} else {
		// TODO: figure out what to do
		LIGHT_ON();
	}
}

void serial_tx_enable() {
	UCSRB |= (1 << TXEN);
}

void serial_tx_disable() {
	UCSRB &= ~(1 << TXEN);
}

void serial_init(void) {
	UBRRH=0;
	UBRRL=103; // 9600 BAUD FOR 8MHZ SYSTEM CLOCK
	UCSRC= (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);	// 8 BIT NO PARITY 2 STOP
	UCSRB=(1<<RXEN);	// ENABLE TX, RX
	UCSRA |= (1<<U2X);	// double baud rate for less error
	char c = UDR; // to clear the RXC flag
}

void send_char_serial (char data) {
	/* Wait for empty transmit buffer */
	while (!(UCSRA & (1<<UDRE)));
	/* Put data into buffer, sends the data */
	UDR = data;
	if (data == '\n') send_char_serial('\r');
	/* Wait for empty transmit buffer */
	while (!(UCSRA & (1<<UDRE)));
}

char receive_char_serial (void) {
	// Wait for data to be received 
	while (!(UCSRA & (1<<RXC)));
	// Get and return received data from buffer 
	return UDR;
}

void send_string_serial(char* s) {
	int i;
	for (i = 0; i < strlen(s); i++) {
		send_char_serial(s[i]);
	}
	send_char_serial('\n');
	send_char_serial('\r');
}
