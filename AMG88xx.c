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
    
    //Set recv addr
    command[0] = 0x80;
    iic_send(AMG88xx_ADDR, command, 1, true);
    
    iic_read(AMG88xx_ADDR, recv_buf, 128);
    for(int i=0; i < 64; i++)
    {
        uint16_t recast = (((uint16_t)recv_buf[i*2+1]) << 8) | (((uint16_t)recv_buf[i*2]));
        int16_t conved = recast << 4;
        temp_grid[i] = conved >> 4;
//        uint16_t absVal = (recast & 0x7FF);
//        temp_grid[i] = (recast & 0x800) ? (0-absVal):absVal;
    }

}

float amg88xx_getChipTemp(void) {
		
    uint8_t command[1];
    uint8_t recv_buf[2];
    
    //Set recv addr
    command[0] = AMG88xx_TTHL;
    iic_send(AMG88xx_ADDR, command, 1, true);
    
    iic_read(AMG88xx_ADDR, recv_buf, 2);
    
    uint16_t recast = (((uint16_t)recv_buf[1]) << 8) | (((uint16_t)recv_buf[0]));
    uint16_t absVal = (recast & 0x7FF);
    
    return (recast & 0x800) ? (0.0f - absVal) * 0.0625f : 0.0625f * absVal;

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
