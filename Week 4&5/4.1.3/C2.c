#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define BIT(x) ( 1<<x )
#define DDR_SPI DDRB // spi Data direction register
#define PORT_SPI PORTB // spi Output register
#define SPI_SCK 1 // PB1: spi Pin System Clock
#define SPI_MOSI 2 // PB2: spi Pin MOSI
#define SPI_MISO 3 // PB3: spi Pin MISO
#define SPI_SS 0 // PB0: spi Pin Slave Select
// wait(): busy waiting for 'ms' millisecond - used library: util/delay.h
void wait(int ms)
{
	for (int i=0; i<ms; i++)
	_delay_ms(1);
}


void spi_masterInit(void)
{
	DDR_SPI = 0xff; // All pins output: MOSI, SCK, SS, SS_display
	DDR_SPI &= ~BIT(SPI_MISO); // except: MISO input
	PORT_SPI |= BIT(SPI_SS); // SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1); // or: SPCR = 0b11010010;
	// Enable spi, MasterMode, Clock rate fck/64
	// bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0
}
// Write a byte from master to slave
void spi_write( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
}
// Write a byte from master to slave and read a byte from slave - not used here
char spi_writeRead( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
	data = SPDR; // New received data (eventually, MISO) in SPDR
	return data; // Return received byte
}
// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}
// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

void spi_writeWord ( unsigned char address, unsigned char data ){
	spi_slaveSelect(0); // Select display chip (MAX7219)
	spi_write(address); // Select register
	spi_write(data); // Write data to register
	spi_slaveDeSelect(0); // Deselect display chip
}

// Set display on ('normal operation')
void displayOn()
{
	spi_writeWord(0x0C, 0x01); // Set shutdown register to normal operation (On)
}
// Set display off ('shut down')
void displayOff()
{
	spi_writeWord(0x0C, 0x00); // Set shutdown register to shutdown mode (Off)
}

// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_writeWord(0x09, 0xFF); //Set BCD mode for all digits
	spi_writeWord(0x0A, 0x0F); //Set display intensity to max (F)
	spi_writeWord(0x0B, 0x03); //Set scan limit to 3 (display 0-3)
	displayOn();
}

void writeLedDisplay(int value){
	if (value >= 0){
		spi_writeWord(0x01, value % 10);
		spi_writeWord(0x02, value / 10 % 10);
		spi_writeWord(0x03, value / 100 % 10);
		spi_writeWord(0x04, value / 1000 % 10);
	} else {
		int absoluteVal = abs(value);
		spi_writeWord(0x01, absoluteVal % 10);
		spi_writeWord(0x02, absoluteVal / 10 % 10);
		spi_writeWord(0x03, absoluteVal / 100 % 10);
		spi_writeWord(0x04, 10);
	}
}

int main()
{
	DDRB=0x01; // Set PB0 pin as output for display select
	spi_masterInit(); // Initialize spi module
	displayDriverInit(); // Initialize display chip
	for (char i =1; i<=4; i++) // clear display (all zero's)
	{
		spi_writeWord(i, 0); // Set display to 0
	}
	writeLedDisplay(1234);
	wait(2000);
	writeLedDisplay(-123);
	return (1);
}