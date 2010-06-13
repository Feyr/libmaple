
#include "wirish.h"

/*
D5     PB6         -      TIM4_CH1       I2C1_SCL   -           -           Y
D6     PA8         -      TIM1_CH1       -          USART1_CK   -           Y
D7     PA9         -      TIM1_CH2       -          USART1_TX   -           Y
D8     PA10        -      TIM1_CH3       -          USART1_RX   -           Y
D9     PB7         -      TIM4_CH2       I2C1_SDA   -           -           Y
*/

//gpio_write_bit(GPIOB_BASE, 6, 1); // VGA_R
//gpio_write_bit(GPIOB_BASE, 6, 0); 

//(GPIOA_BASE)->BSRR = BIT(8);
//asm volatile("nop");
//(GPIOA_BASE)->BRR = BIT(8);
/*
    gpio_write_bit(GPIOB_BASE, 6, 1); // VGA_R
    gpio_write_bit(GPIOB_BASE, 6, 0); 
    gpio_write_bit(GPIOA_BASE, 8, 1); // VGA_G
    gpio_write_bit(GPIOA_BASE, 8, 0); 
    gpio_write_bit(GPIOA_BASE, 9, 1); // VGA_B
    gpio_write_bit(GPIOA_BASE, 9, 0); 
    gpio_write_bit(GPIOA_BASE, 10, 1); // VGA_V
    gpio_write_bit(GPIOA_BASE, 10, 0); 
    gpio_write_bit(GPIOB_BASE, 7, 1); // VGA_H
    gpio_write_bit(GPIOB_BASE, 7, 0); 
*/

#define LED_PIN 13
#define VGA_R 5 // B6
#define VGA_G 6 // A8
#define VGA_B 7 // A9
#define VGA_V 11 // A6
#define VGA_H 12 // A7
#define VGA_R_HIGH (GPIOB_BASE)->BSRR = BIT(6)
#define VGA_R_LOW  (GPIOB_BASE)->BRR  = BIT(6)
#define VGA_G_HIGH (GPIOA_BASE)->BSRR = BIT(8)
#define VGA_G_LOW  (GPIOA_BASE)->BRR  = BIT(8)
#define VGA_B_HIGH (GPIOA_BASE)->BSRR = BIT(9)
#define VGA_B_LOW  (GPIOA_BASE)->BRR  = BIT(9)
#define VGA_V_HIGH (GPIOA_BASE)->BSRR = BIT(6)
#define VGA_V_LOW  (GPIOA_BASE)->BRR  = BIT(6)
#define VGA_H_HIGH (GPIOA_BASE)->BSRR = BIT(7)
#define VGA_H_LOW  (GPIOA_BASE)->BRR  = BIT(7)

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 1);
    pinMode(VGA_R, OUTPUT);
    pinMode(VGA_G, OUTPUT);
    pinMode(VGA_B, OUTPUT);
    pinMode(VGA_V, OUTPUT);
    pinMode(VGA_H, OUTPUT);

    /* Send a message out USART2  */
    Serial2.begin(9600);
    Serial2.println("Video time...");

    
    
    digitalWrite(VGA_R, 0);
    digitalWrite(VGA_G, 0);
    digitalWrite(VGA_B, 0);
    digitalWrite(VGA_H,1);
    digitalWrite(VGA_V,1);

    //timers_set_reload(1,8);
    ////timers_set_prescaler(1,4);
    //pinMode(VGA_G, PWM);
    //pwmWrite(VGA_G, 0x0001);

}

int toggle = 0;
uint16  x = 0;
uint16 y = 0;
GPIO_Port *portb = GPIOB_BASE;

void loop() {
    /* 
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(100);
    Serial2.println("HIHIHI!");
    */ 
    //for(y=0; y<480; y++) {
    for(y=0; y<160; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_H_HIGH;
        VGA_R_HIGH;
        delayMicroseconds(8);
        VGA_G_HIGH;
        delayMicroseconds(10);
        VGA_B_HIGH;
        delayMicroseconds(10);
        VGA_R_LOW;
        VGA_B_LOW;
        VGA_G_LOW;
        //VGA_G_HIGH;
    }
    for(y=0; y<160; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_H_HIGH;
        VGA_G_HIGH;
        delayMicroseconds(8);
        VGA_R_HIGH;
        delayMicroseconds(10);
        VGA_B_HIGH;
        delayMicroseconds(10);
        VGA_R_LOW;
        VGA_B_LOW;
        VGA_G_LOW;
        //VGA_G_HIGH;
    }
    for(y=0; y<160; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_H_HIGH;
        VGA_B_HIGH;
        delayMicroseconds(8);
        VGA_G_HIGH;
        delayMicroseconds(10);
        VGA_R_HIGH;
        delayMicroseconds(10);
        VGA_R_LOW;
        VGA_B_LOW;
        VGA_G_LOW;
        //VGA_G_HIGH;
    }
    for(y=0; y<11; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_R_LOW;
        VGA_H_HIGH;
        delayMicroseconds(28);
    }
    VGA_V_LOW;
    for(y=0; y<2; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_R_LOW;
        VGA_H_HIGH;
        delayMicroseconds(28);
    }
    VGA_V_HIGH;
    for(y=0; y<30; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_R_LOW;
        VGA_H_HIGH;
        delayMicroseconds(28);
    }

}


int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}
