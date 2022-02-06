#include "AMG88xx.h"

#include "transfer_handler.h"

void amg88xx_begin(void) {
    
    pinMode(AMG88_POWER, OUTPUT);

    iic_init();

    amg88xx_on();
}

void amg88xx_getIRGrid(int16_t* temp_grid) {
		
    uint8_t command[2];
    uint8_t recv_buf[128];
    
    //Set normal mode
    command[0] = 0x80;
    iic_send(AMG88xx_ADDR, command, 1, true);
    
    iic_read(AMG88xx_ADDR, recv_buf, 128);
    for(int i=0; i < 64; i++)
    {
        temp_grid[i] = (((int16_t)recv_buf[i*2+1]) << 4) | (((int16_t)recv_buf[i*2]) << 4);
    }

}

void amg88xx_on(void) {

    digitalWrite(AMG88_POWER, 1);
    
    uint8_t command[2];
    //Set normal mode
    command[0] = AMG88xx_PCTL;
    command[1] = AMG88xx_MODE;
    iic_send(AMG88xx_ADDR, command, 2, false);
    //Power on reset
    command[0] = AMG88xx_RST;
    command[1] = AMG88xx_RESET;
    iic_send(AMG88xx_ADDR, command, 2, false);
    //Set 10hz refresh
    command[0] = AMG88xx_FPSC;
    command[1] = AMG88xx_REFRESH;
    iic_send(AMG88xx_ADDR, command, 2, false);

}

void amg88xx_sleep(void) {

    digitalWrite(AMG88_POWER, 0);
    
}
