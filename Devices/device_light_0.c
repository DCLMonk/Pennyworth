#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL

#include <util/delay.h>
#include <string.h>

#define BUFFER_LENGTH 64

#include "DeviceServer/ClientLib/DeviceClient.h"

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

#define MAX_LEN 64 

enum {IDLE = 0, RECEIVE, TRANSMIT, BURN};

void spi_slave_init(void);
//void spi_slave_transmit_char(char c);
//char spi_slave_receive_char(void);
void serial_init(void);
void send_char_serial (char data);
char receive_char_serial (void);
void buffered_spi_send_char(char c);

volatile char transmit_flag;
volatile char buf[MAX_LEN];
volatile char buf_index;
volatile char r_buf[MAX_LEN];
volatile char r_len;
volatile char r_front;
volatile char r_back, state, t_index, t_len;

int main(int argc, char* argv[]) {

	unsigned char ret;

	// define direction of inputs and outputs
	// 1 for output, 0 for input
	// | for output, & for input
	DDRD = (1<<LIGHT);
//	DDRD |= (1<<RELAY);

	LIGHT_OFF();

//	r_len = 0;
	r_front = MAX_LEN - 1;
	r_back = 0;
	state = 0;

	spi_slave_init();

	serial_init();

	buf_index = 0;	
	transmit_flag = 0;	

//	FILE s=FDEV_SETUP_STREAM(send_char_serial,NULL,_FDEV_SETUP_WRITE);
//	stdout=&s;

	sei();

	Device* device = createDevice("test_device_0", 1, buffered_spi_send_char);
	
	setDeviceCName("Light", device);
	setDeviceLocation(0, 0, 0, 0, device);
	
	addField(BOOL, "Light Status", 0, 1, 0, device);

	while (1) {
/*
		c = spi_slave_receive_char();
		if (c == '\0') {
			if (transmit_flag) {
				len = buf[0] + 1;
//				printf("sending packet %d\n", buf[3]);
				for (i = 0; i < len; i++) {
					spi_slave_transmit_char(buf[i]);
				}
//				printf("bi:%d %d %d\n", buf_index, len, buf[3]);
				for (i = len; i < buf_index; i++) {
					buf[i-len] = buf[i];
				}
				buf_index -= len;
				if (buf_index == 0) {
					transmit_flag = 0;
				}
			} else {
				spi_slave_transmit_char('\0');
			}
		} else {
			len = c;
			recvChar(len, device);
			for (i = 0; i < len; i++) {
				c = spi_slave_receive_char();
				recvChar(c, device);
			}
		}
*/
		if (((r_front + 1) % MAX_LEN) != r_back) {
			r_front++;
			if (r_front == MAX_LEN) {
				r_front = 0;
			}
			recvChar(r_buf[r_front], device);
		}

		if (hasChanged(0, device)) {
			ret = getBoolVal(0, device);
			if (ret) {
			//	RELAY_ON();
				LIGHT_ON();
			} else {
			//	RELAY_OFF();
				LIGHT_OFF();
			}
		}
	}

	return 0;
}

void spi_slave_init(void) {
	DDRB |= (1<<MISO);	// outputs
	SPCR = (1<<SPE)|(1<<SPIE); 	// enable SPI
	char c = SPSR;
	c = SPDR;
}
/*
// function to transmit character from slave over SPI
// parameters:	char to send
// returns:
void spi_slave_transmit_char(char data) {
	SPDR = data;				// start transmission
	while (!(SPSR & (1<<SPIF)));		// wait for transmition to complete
}

// function to receive character from slave over SPI
// parameters:	
// returns:	char received
char spi_slave_receive_char(void) { 		//data is junk to send
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
*/
void buffered_spi_send_char(char c) {
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

void serial_init(void) {
	UBRRH=0;
	UBRRL=103; // 9600 BAUD FOR 8MHZ SYSTEM CLOCK
	UCSRC= (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);	// 8 BIT NO PARITY 2 STOP
	UCSRB=(1<<RXEN)|(1<<TXEN);	// ENABLE TX, RX
	UCSRA |= (1<<U2X);	// double baud rate for less error
	char c = UDR; // to clear the RXC flag
}

void send_char_serial (char data) {
	/* Wait for empty transmit buffer */
	while (!(UCSRA & (1<<UDRE)));
	/* Put data into buffer, sends the data */
	UDR = data;
	if (data == '\n') send_char_serial('\r');
}
/*
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
*/
ISR(SPI_STC_vect) {
	unsigned char c = SPDR;
	unsigned char len;
	unsigned char i;
	switch (state) {
	case IDLE:
		if (c != '\0') {
			r_len = c;
			state = RECEIVE;
			r_buf[r_back++] = c;
			if (r_back == MAX_LEN) {
				r_back = 0;
			}
		} else {
			if (transmit_flag) {
				LIGHT_ON();
				SPDR = buf[0];
				t_index = 1;
				t_len = buf[0];
				state = TRANSMIT;
			} else {
				SPDR = '\0';
				state = BURN;
			}
		}
		break;
	case RECEIVE:
		r_len--;
		r_buf[r_back++] = c;
		if (r_back == MAX_LEN) {
			r_back = 0;
		}
		if (r_len == 0) {
			state = IDLE;
		}
		break;
	case TRANSMIT:
		SPDR = buf[t_index++];
		t_len--;
		if (t_len == 0) {
			state = BURN;
			len = buf[0] + 1;
			for (i = len; i < buf_index; i++) {
				buf[i-len] = buf[i];
			}
			buf_index -= len;
			if ((buf_index == 0) || (buf_index <= buf[0])) {
				transmit_flag = 0;
			}
		}
		break;
	case BURN:
		SPDR = '\0';
		state = IDLE;
		break;
	}
}
