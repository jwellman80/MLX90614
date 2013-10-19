#include "MLX90614.h"
#include <i2cmaster.h>
#include <Arduino.h>

MLX90614::MLX90614()
{
	i2c_init(); //Initialise the i2c bus
#ifdef __AVR_ATmega32U4__
	// Yun, Leonardo, other 32u4 Based Arduinos
	PORTD = (1 << PORTD1) | (1 << PORTD0);//enable pullups
#else
	// Uno, Fio
	PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
#endif
}

float MLX90614::GetTempIR(char t)
{
	float val = GetTemp(0);

	if( t == 'C' || t == 'c')
		return val;
	else
		return (1.8 * val + 32.0);
}

float MLX90614::GetTempAmbient(char t)
{
	float val = GetTemp(1);

	if( t == 'C' || t == 'c')
		return val;
	else
		return (1.8 * val + 32.0);
}

float MLX90614::GetTemp( int type )
{
    int dev = 0x5A<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;

    i2c_start_wait(dev+I2C_WRITE);
    if( type == 0 ) // IR
      i2c_write(0x07);
    else            // Ambient
      i2c_write(0x06);

    // read
    i2c_rep_start(dev+I2C_READ);
    data_low = i2c_readAck(); //Read 1 byte and then send ack
    data_high = i2c_readAck(); //Read 1 byte and then send ack
    pec = i2c_readNak();
    i2c_stop();

    //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
    double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
    double tempData = 0x0000; // zero out the data
    int frac; // data past the decimal point

    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;

    return tempData - 273.15;
}
