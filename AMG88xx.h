#ifndef AMGXX_H
#define	AMGXX_H

#include "stdint.h"

#define AMG88xx_ADDR    0x69 //the I2C address by default
//Some AMG Registers
#define AMG88xx_PCTL    0x00
#define AMG88xx_RST     0x01
#define AMG88xx_FPSC    0x02
#define AMG88xx_TTHL    0x0E //Thermistor
//Some AMG commands
#define AMG88xx_MODE    0x00 //Normal operating mode
#define AMG88xx_REFRESH 0x00 //10Hz refresh rate
#define AMG88xx_RESET   0x3F //Software reset

void amg88xx_begin(void);
void amg88xx_getIRGrid(int16_t* temp_grid);
float amg88xx_getChipTemp(void);

void amg88xx_on(void);
void amg88xx_sleep(void);

#endif
