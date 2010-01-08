#include "wiring.h"
#include "HardwareSerial.h"
#include "HardwareUsb.h"
#include "math.h"
#include "usb.h"

int ledPin = 13;
uint8_t bytes_in;

HardwareUsb Usb;

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial2.begin(9600);
    Serial2.println("setup start");

    pinMode(6, PWM);
    pwmWrite(6, 0x8000);
    pinMode(7, OUTPUT);

    Serial2.println("setup end");

    Usb.begin();
    Usb.flush();
}

int toggle = 0;

const char* testMsg = "hello world!\n";
const char x = 'a';
static inline void loop() {
    toggle ^= 1;
    digitalWrite(ledPin, toggle);
    delay(50);

    uint8_t numBytes=Usb.available();
    
    if (numBytes > 0) {
      while (numBytes-->0) {
	Usb.print(Usb.read());
      }
    }

    Usb.flush();
}


int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}

/* Required for C++ hackery */
/* TODO: This really shouldn't go here... move it later
 * */
extern "C" void __cxa_pure_virtual(void) {
    while(1)
        ;
}